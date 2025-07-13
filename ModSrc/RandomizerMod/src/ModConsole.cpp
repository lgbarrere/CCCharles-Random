#include <Unreal/UObject.hpp>
#include <cstring>
#include <Windows.h>

#include "ModConsole.hpp"
#include "Archipelago.h"
#include "Helpers/String.hpp"


#define OPTION_MAX_LENGTH 50
#define NB_MAX_OPTIONS 5
#define ALL_OPTIONS_MAX_LENGTH (NB_MAX_OPTIONS * (OPTION_MAX_LENGTH + 1)) // Addition of all options, +1 by option for '\0'

#define UNDEFINED_COMMAND -1
#define MAX_OPTIONS_REACHED -2
#define OPTION_LENGTH_REACHED -3

#define BASE_ID 6660000000
#define MINIMUM_ID_INDEX (BASE_ID + 1)

using namespace std;
using namespace RC;
using namespace RC::Unreal;

bool gameReload = false;
ReceivedItems receivedItems;
UObject* ItemManager = NULL;
UFunction* ItemReceivedEvent = NULL;



/**
*   @param command : The input command to compare and parse
*   @param expectedCmd : The expected command name to compare with the input command
*   @param outOptions : An out array copying the parsed options separated with '\0'
*   @param outOptionPositions : An out array with the positions of all options in outOptions (-1 for positions without option)
*   @note If an option exceeds OPTION_MAX_LENGTH char or if more options than NB_MAX_OPTIONS are found, -1 is returned
*   @note Get an option with getOptionAtindex()
* 
*   @return The number of parsed options, in error case :
*               UNDEFINED_COMMAND if the command is not recognized
*               MAX_OPTIONS_REACHED if the number of input options exceeds NB_MAX_OPTIONS
*               OPTION_LENGTH_REACHED if an option exceeds OPTION_MAX_LENGTH char ('\0 included')
*/
static int CompareAndParseCmd(const char* command, const char* expectedCmd, char outOptions[ALL_OPTIONS_MAX_LENGTH], int outOptionPositions[NB_MAX_OPTIONS])
{
    const char separator = ' ';
    int i = 0, j = 0;
    int numberOfParsedOptions = 0;

    // Reset the outOptions and outOptionPositions arrays for security purpose
    memset(outOptions, '\0', ALL_OPTIONS_MAX_LENGTH * sizeof(char));
    memset(outOptionPositions, 0, NB_MAX_OPTIONS * sizeof(int));

    // Check if the first word of the command is known (correctly written)
    while (expectedCmd[i] != '\0')
    {
        // If a char is different, the command is not recognized
        if (command[i] != expectedCmd[i])
        {
            return UNDEFINED_COMMAND;
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
            return MAX_OPTIONS_REACHED;
        }

        // Copy the found option until the next separator or the end of the command 
        while (command[i] != separator && command[i] != '\n' && command[i] != '\0')
        {
            if (optionLength >= OPTION_MAX_LENGTH)
            {
                return OPTION_LENGTH_REACHED;
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


/**
*   @brief Receive an item from any world
*   @param itemID : The ID of the received item
*   @param notifyPlayer : Id true, notify the player about the received item, false otherwise
*/
static void ItemReceivedCallback(int64_t itemID, bool notifyPlayer)
{
    // Add 1 item from the received itemID to the inventory
    int tmpIndex = (int)(itemID - MINIMUM_ID_INDEX);
    switch (tmpIndex)
    {
    case 0: // Scraps
        receivedItems.ItemAmounts[0] += 1;
        break;
    case 1: // Scraps (reward 30)
        receivedItems.ItemAmounts[0] += 30;
        break;
    case 2: // Scraps (reward 25)
        receivedItems.ItemAmounts[0] += 25;
        break;
    case 3: // Scraps (reward 35)
        receivedItems.ItemAmounts[0] += 35;
        break;
    case 4: // Scraps (reward 40)
        receivedItems.ItemAmounts[0] += 40;
        break;
    case 5: // South mine key
        receivedItems.ItemAmounts[1] += 1;
        break;
    case 6: // North mine key
        receivedItems.ItemAmounts[2] += 1;
        break;
    case 7: // Mountain ruin key
        receivedItems.ItemAmounts[3] += 1;
        break;
    case 8: // Barn key
        receivedItems.ItemAmounts[4] += 1;
        break;
    case 9: // Candice key
        receivedItems.ItemAmounts[5] += 1;
        break;
    case 10: // Dead fish
        receivedItems.ItemAmounts[6] += 1;
        break;
    case 11: // Lockpicks
        receivedItems.ItemAmounts[7] += 1;
        break;
    case 12: // Ancient tablet
        receivedItems.ItemAmounts[8] += 1;
        break;
    case 13: // Blue box
        receivedItems.ItemAmounts[9] += 1;
        break;
    case 14: // Page Drawing
        receivedItems.ItemAmounts[10] += 1;
        break;
    case 15: // Journal
        receivedItems.ItemAmounts[11] += 1;
        break;
    case 16: // Dynamite
        receivedItems.ItemAmounts[12] += 1;
        break;
    case 17: // Boomer rockets
        receivedItems.ItemAmounts[13] += 1;
        break;
    case 18: // Breaker
        receivedItems.ItemAmounts[14] += 1;
        break;
    case 19: // Broken Bob
        receivedItems.ItemAmounts[15] += 1;
        break;
    case 20: // Employment contracts
        receivedItems.ItemAmounts[16] += 1;
        break;
    case 21: // Mob camp key
        receivedItems.ItemAmounts[17] += 1;
        break;
    case 22: // Pickles jar
        receivedItems.ItemAmounts[18] += 1;
        break;
    case 23: // Orange Paint Can
        receivedItems.UnlockedPaintCans[0] = true;
        break;
    case 24: // Green Paint Can
        receivedItems.UnlockedPaintCans[1] = true;
        break;
    case 25: // White Paint Can
        receivedItems.UnlockedPaintCans[2] = true;
        break;
    case 26: // Pink Paint Can
        receivedItems.UnlockedPaintCans[3] = true;
        break;
    case 27: // Gray Paint Can
        receivedItems.UnlockedPaintCans[4] = true;
        break;
    case 28: // Blue Paint Can
        receivedItems.UnlockedPaintCans[5] = true;
        break;
    case 29: // Black Paint Can
        receivedItems.UnlockedPaintCans[6] = true;
        break;
    case 30: // Lime Paint Can
        receivedItems.UnlockedPaintCans[7] = true;
        break;
    case 31: // Light Blue Paint Can
        receivedItems.UnlockedPaintCans[8] = true;
        break;
    case 32: // Red Paint Can
        receivedItems.UnlockedPaintCans[9] = true;
        break;
    case 33: // Purple Paint Can
        receivedItems.UnlockedPaintCans[10] = true;
        break;
    case 34: // The Boomer
        receivedItems.UnlockedWeapons[0] = true;
        break;
    case 35: // Bob
        receivedItems.UnlockedWeapons[1] = true;
        break;
    case 36: // Green egg
        receivedItems.ItemAmounts[19] += 1;
        break;
    case 37: // Blue egg
        receivedItems.ItemAmounts[20] += 1;
        break;
    case 38: // Red egg
        receivedItems.ItemAmounts[21] += 1;
        break;
    case 39: // Remote explosives
        receivedItems.ItemAmounts[22] += 1;
        break;
    case 40: // Remote explosives (x8)
        receivedItems.ItemAmounts[22] += 8;
        break;
    case 41: // Temple key
        receivedItems.ItemAmounts[23] += 1;
        break;
    case 42: // Bug spray
        receivedItems.UnlockedWeapons[2] = true;
        break;
    }

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

    Output::send<LogLevel::Verbose>(STR("Calling ProcessEvent...\n"));
    ItemManager->ProcessEvent(ItemReceivedEvent, &itemID);
    Output::send<LogLevel::Verbose>(STR("ProcessEvent finished.\n"));
}


/**
*   @brief Mark a given location as checked
*   @param locationID : The ID of the checked location
*   @notimplemented Used by AP_SetItemClearCallback but is not necessary
*/
static void LocationCheckedCallback(int64_t locationID)
{
    
}


void LogFromAPCpp(std::string message) {
    Output::send<LogLevel::Verbose>(TEXT("LogFromAPCpp: {}\n"), RC::to_wstring(message).c_str());
}


namespace ModConsole {
    void ModConsole::ResetItemAmounts()
    {
        for (int32_t Index = 0; Index != receivedItems.ItemAmounts.Num(); Index++)
        {
            receivedItems.ItemAmounts[Index] = 0;
        }
    }


    bool ModConsole::CheckCommand(FOutputDevice& Ar, const TCHAR* command)
    {
        // Conversion from const TCHAR* to const char*
        // Must first be converted to string : while the exists, the const char* will be valid
        string commandStr = to_string(command);
        const char* commandCharStr = commandStr.c_str();

        // If no '/' and '!' starts the entry, do not consider it as a command and exit early
        if (commandCharStr[0] != '/' && commandCharStr[0] != '!')
        {
            Output::send<LogLevel::Verbose>(STR("Entry with no command found : {}\n"), command);
            Output::send<LogLevel::Verbose>(STR("Put \'/\' or \'!\' at the start of your command to detect it\n"));
            Output::send<LogLevel::Verbose>(STR("Try /help for details\n"));

            return false;
        }
        commandCharStr++; // Command detected, exclude the first character from the array

        char outOptions[ALL_OPTIONS_MAX_LENGTH];
        int outOptionPositions[NB_MAX_OPTIONS];
        int numberOfOptions = 0;

        numberOfOptions = CompareAndParseCmd(commandCharStr, "help", outOptions, outOptionPositions);
        if (numberOfOptions != UNDEFINED_COMMAND)
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
            Ar.Log(STR("/hint_location <location>\n"));
            Ar.Log(STR("        Get a hint on the given <location>.\n"));
            Ar.Log(STR("/remaining\n"));
            Ar.Log(STR("        Show all remaining locations (still not checked).\n"));
            Ar.Log(STR("/send <location>\n"));
            Ar.Log(STR("        Send the given <location>, considering it as checked.\n"));

            return true;
        }

        // Check if the used command is "/connect [...]"
        // Example : /connect archipelago.gg:59157 YaranCCC
        numberOfOptions = CompareAndParseCmd(commandCharStr, "connect", outOptions, outOptionPositions);
        if (numberOfOptions >= 2) // At least 2 options are required for the "connect" command
        {
            Ar.Log(STR("Connect\n"));
            const char* ipAddress = GetOptionAtindex(outOptions, outOptionPositions, 0);
            const char* playerName = GetOptionAtindex(outOptions, outOptionPositions, 1);
            const char* password = numberOfOptions == 2 ? "" : GetOptionAtindex(outOptions, outOptionPositions, 2);

            AP_Init(ipAddress, "Choo-Choo Charles", playerName, password);
            AP_SetItemClearCallback(ClearInventoryCallback);
            AP_SetItemRecvCallback(ItemReceivedCallback);
            AP_SetLocationCheckedCallback(LocationCheckedCallback);
            AP_SetDeathLinkSupported(false);
            AP_Start();

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "disconnect", outOptions, outOptionPositions);
        if (numberOfOptions >= 0)
        {
            Ar.Log(STR("Disconnect\n"));
            ModConsole::ResetItemAmounts();
            AP_Shutdown();

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "release", outOptions, outOptionPositions);
        if (numberOfOptions >= 0)
        {
            /* code */
            Ar.Log(STR("Release\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "collect", outOptions, outOptionPositions);
        if (numberOfOptions >= 0)
        {
            /* code */
            Ar.Log(STR("Collect\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "hint", outOptions, outOptionPositions);
        if (numberOfOptions >= 1)
        {
            /* code */
            Ar.Log(STR("Hint\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "hint_location", outOptions, outOptionPositions);
        if (numberOfOptions >= 1)
        {
            /* code */
            Ar.Log(STR("Hint location\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "remaining", outOptions, outOptionPositions);
        if (numberOfOptions >= 0)
        {
            /* code */
            Ar.Log(STR("Remaining\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "send", outOptions, outOptionPositions);
        if (numberOfOptions >= 1) // send a location as done check
        {
            /* code */
            Ar.Log(STR("Send\n"));

            return true;
        }

        return false;
    }
}
