#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/Hooks.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/UFunctionStructs.hpp>
#include <Unreal/FProperty.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/BPMacros.hpp>
#include <Unreal/NameTypes.hpp>

#include "ModConsole.hpp"
#include "Archipelago.h"
#include "Helpers/String.hpp"


#define OPTION_MAX_LENGTH 50
#define NB_MAX_OPTIONS 5
#define ALL_OPTIONS_MAX_LENGTH (NB_MAX_OPTIONS * (OPTION_MAX_LENGTH + 1)) // Addition of all options, +1 by option for '\0'

using namespace std;
using namespace RC;
using namespace RC::Unreal;

static UObject* ItemManager = NULL;
static UFunction* GetGameSeedEvent = NULL;
static UFunction* ItemReceivedEvent = NULL;

/**
*   @param command : The input command to compare and parse
*   @param expectedCmd : The expected command name to compare with the input command
*   @param outOptions : An out array copying the parsed options separated with '\0'
*   @param outOptionPositions : An out array with the positions of all options in outOptions (-1 for positions without option)
*   @note If an option exceeds OPTION_MAX_LENGTH char or if more options than NB_MAX_OPTIONS are found, -1 is returned
*   @note Get an option with getOptionAtindex()
* 
*   @return The number of parsed options, in error case :
*               -1 if the command is not recognized
*               -2 if the number of input options exceeds NB_MAX_OPTIONS
*               -3 if an option exceeds OPTION_MAX_LENGTH char ('\0 included')
*/
static int CompareAndParseCmd(const char* command, const char* expectedCmd, char outOptions[ALL_OPTIONS_MAX_LENGTH], int outOptionPositions[NB_MAX_OPTIONS])
{
    const char separator = ' ';
    int i = 0, j = 0;
    int numberOfParsedOptions = 0;

    // Check if the first word of the command is known (correctly written)
    while (expectedCmd[i] != '\0')
    {
        // If a char is different, the command is not recognized
        if (command[i] != expectedCmd[i])
        {
            return -1;
        }
        i++;
    }

    // While the end of the command is not reached, parse the options
    while (command[i] != '\n' && command[i] != '\0')
    {
        outOptionPositions[numberOfParsedOptions] = j;
        int optionLength = 1; // Count the number of char in an option to not exceed OPTION_MAX_LENGTH

        // Ignore trailing separators after comparision, the command name is recognized
        while (command[i] == separator)
        {
            i++;
        }

        // Error if the maximum number of expected options is reached and the command line is not ended
        if (numberOfParsedOptions >= NB_MAX_OPTIONS && command[i] != '\n' && command[i] != '\0')
        {
            return -2;
        }

        // Copy the found option until the next separator or the end of the command 
        while (command[i] != separator && command[i] != '\n' && command[i] != '\0')
        {
            if (optionLength >= OPTION_MAX_LENGTH)
            {
                return -3;
            }

            outOptions[j] = command[i];
            i++;
            j++;
            optionLength++;
        }

        outOptions[j] = '\0'; // End an option by '\0'
        j++;
        numberOfParsedOptions++;
    }

    for (int k = numberOfParsedOptions; k < NB_MAX_OPTIONS; k++)
    {
        outOptionPositions[numberOfParsedOptions] = -1;
    }

    return numberOfParsedOptions;
}


/**
*   @param options : An array with the options separated with '\0'
*   @param optionPositions : An array with the positions of all options in outOptions
*   @param index : The index of the option (should not exceed NB_MAX_OPTIONS)
*   @note CompareAndParseCmd() should be called once before using this function
*
*   @return The option at the provided index, NULL otherwise (incorrect index or no option at this index)
*/
static char* GetOptionAtindex(char options[ALL_OPTIONS_MAX_LENGTH], const int optionPositions[NB_MAX_OPTIONS], const unsigned int index)
{
    if (index >= NB_MAX_OPTIONS || optionPositions[index] == -1)
    {
        return NULL;
    }

    return options + optionPositions[index];
}


/**
*   @brief Clear all the collected items from the player's inventory
*   @notimplemented Used by AP_SetItemClearCallback but is not necessary
*/
static void ClearInventoryCallback()
{

}


typedef struct
{
    FString seed;
    int64_t itemID;
}ItemSeedParameter;


/**
*   @brief Receive an item from any world
*   @param itemID : The ID of the received item
*   @param notifyPlayer : Pass true to notify the player about the received item, false otherwise
*/
static void ItemReceivedCallback(int64_t itemID, bool notifyPlayer)
{
    // If notifyPlayer is false, the item has already be received once => don't receive that again
    if (!notifyPlayer)
    {
        return;
    }
    
    // Get ItemManager reference if not done, leave the function if it cannot be found
    if (!ItemManager) {
        ItemManager = UObjectGlobals::FindFirstOf(STR("ItemManager_C"));
        if (!ItemManager) {
            Output::send<LogLevel::Error>(STR("ItemManager not found\n"));
            return;
        }
    }

    // Get ItemReceived event reference (to add itemID to inventory) if not done, leave the function if it cannot be found
    static auto ItemReceived = FName(STR("ItemReceived"), FNAME_Add);
    if (!ItemReceivedEvent)
    {
        ItemReceivedEvent = ItemManager->GetFunctionByName(ItemReceived);
        if (!ItemReceivedEvent)
        {
            Output::send<LogLevel::Error>(STR("ItemReceived not found\n"));
            return;
        }
    }

    AP_RoomInfo roomInfo;
    AP_GetRoomInfo(&roomInfo);
    ItemSeedParameter itemReceivedParameter;
    itemReceivedParameter.seed = FString(to_wstring(roomInfo.seed_name).c_str());
    itemReceivedParameter.itemID = itemID;
    Output::send<LogLevel::Verbose>(STR("Seed : {}\n"), itemReceivedParameter.seed.GetCharArray());

    ItemManager->ProcessEvent(ItemReceivedEvent, &itemReceivedParameter);
}


/**
*   @brief Mark a given location as checked
*   @param locationID : The ID of the checked location
*   @notimplemented Used by AP_SetItemClearCallback but is not necessary
*/
static void LocationCheckedCallback(int64_t locationID)
{
    
}


/**
*   @brief Convert the passed char* to TCHAR*
*   @param charStr : The char* to convert
*/
static const TCHAR* CharStrToConstTcharStr(char* charStr)
{
    string str(charStr);
    return RC::to_wstring(str).c_str();
}


namespace ModConsole {
    int ModConsole::CheckCommand(FOutputDevice& Ar, const TCHAR* command)
    {
        char outOptions[ALL_OPTIONS_MAX_LENGTH];
        int outOptionPositions[NB_MAX_OPTIONS];

        const char* commandCharStr = RC::to_string(command).c_str();
        int numberOfOptions = CompareAndParseCmd(commandCharStr, "help", outOptions, outOptionPositions);
        if (numberOfOptions != -1)
        {
            // Print in console
            Ar.Log(STR("/help\n"));
            Ar.Log(STR("        Shows all available commands\n"));
            Ar.Log(STR("/connect <IP> <PlayerName> [Password]\n"));
            Ar.Log(STR("        Connect to the room at the given <IP>\n"));
            Ar.Log(STR("/disconnect\n"));
            Ar.Log(STR("        Disconnect from the current room.\n"));
            Ar.Log(STR("/release\n"));
            Ar.Log(STR("        Send all your items to the players as completed game.\n"));
            Ar.Log(STR("/collect\n"));
            Ar.Log(STR("        Get all your items from each player.\n"));
            Ar.Log(STR("/hint <item>\n"));
            Ar.Log(STR("        Get a hint on the given <item>.\n"));
            Ar.Log(STR("/hint_location\n"));
            Ar.Log(STR("        Get a hint on the given <location>.\n"));
            Ar.Log(STR("/get <item>\n"));
            Ar.Log(STR("        Get the given <item> and add it to inventory.\n"));
        }
        // Check if the use input is "/connect [...]"
        // Example : /connect archipelago.gg:59157 YaranCCC
        numberOfOptions = CompareAndParseCmd(commandCharStr, "connect", outOptions, outOptionPositions);
        if (numberOfOptions >= 2) // At least 2 options are required for the "connect" command
        {
            Ar.Log(STR("Command recognized\n"));
            char* ipAddress = GetOptionAtindex(outOptions, outOptionPositions, 0);
            char* playerName = GetOptionAtindex(outOptions, outOptionPositions, 1);
            char* password = GetOptionAtindex(outOptions, outOptionPositions, 2);
            
            // TODO : Remove this once the debug is finished
            Ar.Log(STR("Option1 :\n"));
            Ar.Log(CharStrToConstTcharStr(ipAddress));
            Ar.Log(STR("Option2 :\n"));
            Ar.Log(CharStrToConstTcharStr(playerName));
            Ar.Log(STR("Option3 :\n"));
            Ar.Log(CharStrToConstTcharStr(password));
            
            AP_Init(ipAddress, "Choo-Choo Charles", playerName, password);
            AP_SetItemClearCallback(ClearInventoryCallback);
            AP_SetItemRecvCallback(ItemReceivedCallback);
            AP_SetLocationCheckedCallback(LocationCheckedCallback);
            AP_SetDeathLinkSupported(false);
            AP_Start();

            return 1;
        }
        else if (CompareAndParseCmd(commandCharStr, "disconnect", outOptions, outOptionPositions))
        {
            AP_Shutdown();
        }
        else if (CompareAndParseCmd(commandCharStr, "release", outOptions, outOptionPositions))
        {
            /* code */
        }
        else if (CompareAndParseCmd(commandCharStr, "collect", outOptions, outOptionPositions))
        {
            /* code */
        }
        else if (CompareAndParseCmd(commandCharStr, "hint", outOptions, outOptionPositions))
        {
            /* code */
        }
        else if (CompareAndParseCmd(commandCharStr, "hint_location", outOptions, outOptionPositions))
        {
            /* code */
        }
        else if (CompareAndParseCmd(commandCharStr, "remaining", outOptions, outOptionPositions))
        {
            /* code */
        }
		else if (CompareAndParseCmd(commandCharStr, "get", outOptions, outOptionPositions)) // get an item as done check
        {
            /* code */
        }
        
        return 0;
    }
}
