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

#define BASE_ID 66600000

using namespace std;
using namespace RC;
using namespace RC::Unreal;

ReceivedItems receivedItems;
TArray<int64_t> pendingItemIDs;


/**
*   @param command: The input command to compare and parse
*   @param expectedCmd: The expected command name to compare with the input command
*   @param outOptions: An out array copying the parsed options separated with '\0'
*   @param outOptionPositions: An out array with the positions of all options in outOptions (-1 for positions without option)
*   @note If an option exceeds OPTION_MAX_LENGTH char or if more options than NB_MAX_OPTIONS are found, -1 is returned
*   @note Get an option with getOptionAtindex()
* 
*   @return The number of parsed options, in error case:
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
*   @param options: An array with the options separated with '\0'
*   @param optionPositions: An array with the positions of all options in outOptions
*   @param index: The index of the option (should not exceed NB_MAX_OPTIONS)
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
*   @param itemID: The ID of the received item
*   @param notifyPlayer: Id true, notify the player about the received item, false otherwise
*/
static void ItemReceivedCallback(int64_t itemID, bool notifyPlayer)
{
    // Add 1 item from the received itemID to the inventory
    int cappedAmount = 1; // Consider by default 1 item must be added (to set to 0 if the cap is reached)
    int amountToAdd = 0; // Used for "Remote Explosives" packs (can be greatter than 1)
    int index = (int)(itemID - BASE_ID);

    switch (index)
    {
    case 1: // Scraps
        receivedItems.items[0].amount += 1; // No cap for scraps
        break;
    case 2: // Scraps (reward 30)
        receivedItems.items[0].amount += 30; // No cap for scraps
        break;
    case 3: // Scraps (reward 25)
        receivedItems.items[0].amount += 25; // No cap for scraps
        break;
    case 4: // Scraps (reward 35)
        receivedItems.items[0].amount += 35; // No cap for scraps
        break;
    case 5: // Scraps (reward 40)
        receivedItems.items[0].amount += 40; // No cap for scraps
        break;
    case 6: // South mine key
        receivedItems.items[1].amount < 1 ? receivedItems.items[1].amount += 1 : cappedAmount = 0;
        break;
    case 7: // North mine key
        receivedItems.items[2].amount < 1 ? receivedItems.items[2].amount += 1 : cappedAmount = 0;
        break;
    case 8: // Mountain ruin key
        receivedItems.items[3].amount < 1 ? receivedItems.items[3].amount += 1 : cappedAmount = 0;
        break;
    case 9: // Barn key
        receivedItems.items[4].amount < 1 ? receivedItems.items[4].amount += 1 : cappedAmount = 0;
        break;
    case 10: // Candice key
        receivedItems.items[5].amount < 1 ? receivedItems.items[5].amount += 1 : cappedAmount = 0;
        break;
    case 11: // Dead fish
        receivedItems.items[6].amount < 1 ? receivedItems.items[6].amount += 1 : cappedAmount = 0;
        break;
    case 12: // Lockpicks
        receivedItems.items[7].amount < 1 ? receivedItems.items[7].amount += 1 : cappedAmount = 0;
        break;
    case 13: // Ancient tablet
        receivedItems.items[8].amount < 1 ? receivedItems.items[8].amount += 1 : cappedAmount = 0;
        break;
    case 14: // Blue box
        receivedItems.items[9].amount < 1 ? receivedItems.items[9].amount += 1 : cappedAmount = 0;
        break;
    case 15: // Page Drawing
        receivedItems.items[10].amount < 8 ? receivedItems.items[10].amount += 1 : cappedAmount = 0;
        break;
    case 16: // Journal
        receivedItems.items[11].amount < 1 ? receivedItems.items[11].amount += 1 : cappedAmount = 0;
        break;
    case 17: // Dynamite
        receivedItems.items[12].amount < 1 ? receivedItems.items[12].amount += 1 : cappedAmount = 0;
        break;
    case 18: // Boomer rockets
        receivedItems.items[13].amount < 1 ? receivedItems.items[13].amount += 1 : cappedAmount = 0;
        break;
    case 19: // Breaker
        receivedItems.items[14].amount < 4 ? receivedItems.items[14].amount += 1 : cappedAmount = 0;
        break;
    case 20: // Broken Bob
        receivedItems.items[15].amount < 1 ? receivedItems.items[15].amount += 1 : cappedAmount = 0;
        break;
    case 21: // Employment contracts
        receivedItems.items[16].amount < 1 ? receivedItems.items[16].amount += 1 : cappedAmount = 0;
        break;
    case 22: // Mob camp key
        receivedItems.items[17].amount < 1 ? receivedItems.items[17].amount += 1 : cappedAmount = 0;
        break;
    case 23: // Pickles jar
        receivedItems.items[18].amount < 1 ? receivedItems.items[18].amount += 1 : cappedAmount = 0;
        break;
    case 24: // Orange Paint Can
        receivedItems.paintCans[0].unlocked == false ? receivedItems.paintCans[0].unlocked = true : cappedAmount = 0;
        break;
    case 25: // Green Paint Can
        receivedItems.paintCans[1].unlocked == false ? receivedItems.paintCans[1].unlocked = true : cappedAmount = 0;
        break;
    case 26: // White Paint Can
        receivedItems.paintCans[2].unlocked == false ? receivedItems.paintCans[2].unlocked = true : cappedAmount = 0;
        break;
    case 27: // Pink Paint Can
        receivedItems.paintCans[3].unlocked == false ? receivedItems.paintCans[3].unlocked = true : cappedAmount = 0;
        break;
    case 28: // Gray Paint Can
        receivedItems.paintCans[4].unlocked == false ? receivedItems.paintCans[4].unlocked = true : cappedAmount = 0;
        break;
    case 29: // Blue Paint Can
        receivedItems.paintCans[5].unlocked == false ? receivedItems.paintCans[5].unlocked = true : cappedAmount = 0;
        break;
    case 30: // Black Paint Can
        receivedItems.paintCans[6].unlocked == false ? receivedItems.paintCans[6].unlocked = true : cappedAmount = 0;
        break;
    case 31: // Lime Paint Can
        receivedItems.paintCans[7].unlocked == false ? receivedItems.paintCans[7].unlocked = true : cappedAmount = 0;
        break;
    case 32: // Teal Paint Can
        receivedItems.paintCans[8].unlocked == false ? receivedItems.paintCans[8].unlocked = true : cappedAmount = 0;
        break;
    case 33: // Red Paint Can
        receivedItems.paintCans[9].unlocked == false ? receivedItems.paintCans[9].unlocked = true : cappedAmount = 0;
        break;
    case 34: // Purple Paint Can
        receivedItems.paintCans[10].unlocked == false ? receivedItems.paintCans[10].unlocked = true : cappedAmount = 0;
        break;
    case 35: // The Boomer
        receivedItems.weapons[0].unlocked == false ? receivedItems.weapons[0].unlocked = true : cappedAmount = 0;
        break;
    case 36: // Bob
        receivedItems.weapons[1].unlocked == false ? receivedItems.weapons[1].unlocked = true : cappedAmount = 0;
        break;
    case 37: // Green egg
        receivedItems.items[19].amount < 1 ? receivedItems.items[19].amount += 1 : cappedAmount = 0;
        break;
    case 38: // Blue egg
        receivedItems.items[20].amount < 1 ? receivedItems.items[20].amount += 1 : cappedAmount = 0;
        break;
    case 39: // Red egg
        receivedItems.items[21].amount < 1 ? receivedItems.items[21].amount += 1 : cappedAmount = 0;
        break;
    case 40: // Remote explosives
        receivedItems.items[22].amount < 8 ? receivedItems.items[22].amount += 1 : cappedAmount = 0;
        break;
    case 41: // Remote explosives (x8)
        amountToAdd = 8;
        itemID = BASE_ID + 40; // Change id to "Remote explosives" to add it cappedAmount times
        cappedAmount = (receivedItems.items[22].amount + amountToAdd <= 8) ? amountToAdd : 8 - receivedItems.items[22].amount;
        receivedItems.items[22].amount += cappedAmount;
        break;
    case 42: // Temple key
        receivedItems.items[23].amount < 1 ? receivedItems.items[23].amount += 1 : cappedAmount = 0;
        break;
    case 43: // Bug Spray
        receivedItems.weapons[2].unlocked == false ? receivedItems.weapons[2].unlocked = true : cappedAmount = 0;
        break;
    case 44 : // Track Switch Pack
        // The pack contrains 7 track switches
        for (int i = 0; i < 7; i++)
        {
            receivedItems.objects[i].amount < 1 ? receivedItems.objects[i].amount += 1 : cappedAmount = 0;
        }
        break;
    case 45: // Track Switch - Barn or Tutorial
        receivedItems.objects[0].amount < 1 ? receivedItems.objects[0].amount += 1 : cappedAmount = 0;
        break;
    case 46: // Track Switch - Middle or Port
        receivedItems.objects[1].amount < 1 ? receivedItems.objects[1].amount += 1 : cappedAmount = 0;
        break;
    case 47: // Track Switch - Haunted or East
        receivedItems.objects[2].amount < 1 ? receivedItems.objects[2].amount += 1 : cappedAmount = 0;
        break;
    case 48: // Track Switch - North or Temple
        receivedItems.objects[3].amount < 1 ? receivedItems.objects[3].amount += 1 : cappedAmount = 0;
        break;
    case 49: // Track Switch - Caravan or Cultists
        receivedItems.objects[4].amount < 1 ? receivedItems.objects[4].amount += 1 : cappedAmount = 0;
        break;
    case 50: // Track Switch - Camp or Elevator
        receivedItems.objects[5].amount < 1 ? receivedItems.objects[5].amount += 1 : cappedAmount = 0;
        break;
    case 51: // Track Switch - Ruin or Temple
        receivedItems.objects[6].amount < 1 ? receivedItems.objects[6].amount += 1 : cappedAmount = 0;
        break;
    default:
        Output::send<LogLevel::Error>(STR("Unrecognized item ID skipped.\n"));
        return;
    }

    // If notifyPlayer is true, this ID is received for the first time, add it in pendingItemIDs
    if (notifyPlayer)
    {
        for (int i = 0; i < cappedAmount; i++)
        {
            pendingItemIDs.Emplace(itemID);
        }
    }
}


/**
*   @brief Mark a given location as checked
*   @param locationID: The ID of the checked location
*   @notimplemented Used by AP_SetItemClearCallback but is not necessary
*/
static void LocationCheckedCallback(int64_t locationID)
{
    
}


/**
 * @brief Retains only digits ('0'–'9') and the dot ('.') character from an version string
 * @note Intended to extract version-like strings
 * @param version The string to filter
 * @return The filtered string
 */
static std::string filterVersion(std::string version)
{
    std::string result;
    result.reserve(version.size());

    for (unsigned char c : version)
    {
        if (std::isdigit(c) || c == '.')
            result.push_back(c);
    }

    return result;
}


/**
*   @brief Get the version of the apworld from the slot_data
*   @param version: The version
*/
static void WorldVersionCallback(std::string version)
{
    latestWorldVersion = filterVersion(version);
}


/**
*   @brief Log used to check APCpp messages, replace prints in APCpp code by call of this function
*   @param message: The message to log
*/
void LogFromAPCpp(std::string message) {
    Output::send<LogLevel::Verbose>(TEXT("LogFromAPCpp: {}\n"), RC::to_wstring(message).c_str());
}


namespace ModConsole {
    /**
    *   @brief Reset all received items amounts and all unlocked train components to 0
    */
    void ModConsole::ResetItemAmounts()
    {
        for (int32_t index = 0; index != receivedItems.items.Num(); index++)
        {
            receivedItems.items[index].amount = 0;
        }
        for (int32_t index = 0; index != receivedItems.paintCans.Num(); index++)
        {
            receivedItems.paintCans[index].unlocked = false;
        }
        for (int32_t index = 0; index != receivedItems.weapons.Num(); index++)
        {
            receivedItems.weapons[index].unlocked = false;
        }

        pendingItemIDs.Empty();
    }


    /**
    *   @brief Manage user commands written in the UE console to interact with Archipelago using APCpp
    *   @param Ar: The used device (expecting UE console here)
    *   @param command: The typed command by the user
    */
    bool ModConsole::CheckCommand(FOutputDevice& Ar, const TCHAR* command)
    {
        // Conversion from const TCHAR* to const char*
        // Must first be converted to string: while the exists, the const char* will be valid
        string commandStr = to_string(command);
        const char* commandCharStr = commandStr.c_str();

        // If no '/' and '!' starts the entry, do not consider it as a command and exit early
        if (commandCharStr[0] != '/' && commandCharStr[0] != '!')
        {
            Output::send<LogLevel::Verbose>(STR("Entry with no command found: {}\n"), command);
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
            Ar.Log(STR("        Shows all available commands and their description\n"));
            Ar.Log(STR("/connect <IP> <PlayerName> [Password]\n"));
            Ar.Log(STR("        Connect to the AP room using an <IP>, a <PlayerName> (in the forms \"archipelago.gg:XXXXX\" and \"CCCharles\") and an optional [Password]\n"));
            Ar.Log(STR("/disconnect\n"));
            Ar.Log(STR("        Disconnect from the current room\n"));
            /*
            Ar.Log(STR("/release\n"));
            Ar.Log(STR("        Send all your items to the players as completed game\n"));
            Ar.Log(STR("/collect\n"));
            Ar.Log(STR("        Get all your items from each player\n"));
            Ar.Log(STR("/hint <item>\n"));
            Ar.Log(STR("        Get a hint on the given <item>\n"));
            Ar.Log(STR("/hint_location <location>\n"));
            Ar.Log(STR("        Get a hint on the given <location>\n"));
            Ar.Log(STR("/remaining\n"));
            Ar.Log(STR("        Show all remaining locations (still not checked)\n"));
            Ar.Log(STR("/send <location>\n"));
            Ar.Log(STR("        Send the given <location>, considering it as checked\n"));
            */

            return true;
        }

        // Check if the used command is "/connect [...]"
        // Example: /connect archipelago.gg:<Port> CCC_Player
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
            AP_RegisterSlotDataRawCallback("world_version", &WorldVersionCallback);
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
