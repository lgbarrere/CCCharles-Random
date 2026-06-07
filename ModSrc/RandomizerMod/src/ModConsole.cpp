#include <Unreal/UObject.hpp>

#include "ModConsole.hpp"
#include "APManager.hpp"
#include "Helpers/String.hpp"

#define OPTION_MAX_LENGTH 50
#define NB_MAX_OPTIONS 5
#define ALL_OPTIONS_MAX_LENGTH (NB_MAX_OPTIONS * (OPTION_MAX_LENGTH + 1)) // Addition of all options, +1 by option for '\0'

#define UNDEFINED_COMMAND -1
#define MAX_OPTIONS_REACHED -2
#define OPTION_LENGTH_REACHED -3

using namespace std;
using namespace RC;
using namespace RC::Unreal;


/**
 * @brief Check command and expectedCmd are equal, then parse options found after each whitespace
 * @note If an option exceeds OPTION_MAX_LENGTH char or if more options than NB_MAX_OPTIONS are found, -1 is returned
 * @note Get an option with getOptionAtindex()
 * @param command: The input command to compare and parse
 * @param expectedCmd: The expected command name to compare with the input command
 * @param outOptions: An out array copying the parsed options separated with '\0'
 * @param outOptionPositions: An out array with the positions of all options in outOptions (-1 for positions without option)
 * 
 * @return The number of parsed options, in error case:
 * -> UNDEFINED_COMMAND if the command is not recognized
 * -> MAX_OPTIONS_REACHED if the number of input options exceeds NB_MAX_OPTIONS
 * -> OPTION_LENGTH_REACHED if an option exceeds OPTION_MAX_LENGTH char ('\0 included')
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
 * @brief Get the address of an option at a given index
 * @note CompareAndParseCmd() should be called once before using this function
 * @param options: An array with the options separated with '\0'
 * @param optionPositions: An array with the positions of all options in outOptions
 * @param index: The index of the option (should not exceed NB_MAX_OPTIONS)
 *
 * @return The option at the provided index, NULL otherwise (incorrect index or no option at this index)
 */
static char* GetOptionAtindex(char options[ALL_OPTIONS_MAX_LENGTH], const int optionPositions[NB_MAX_OPTIONS], const unsigned int index)
{
    if (index >= NB_MAX_OPTIONS || optionPositions[index] == -1)
    {
        return NULL;
    }

    return options + optionPositions[index];
}


namespace ModConsole {
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
            // TODO: Uncomment the the following commands once implemented
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
            
            APManager::Setup_AP(ipAddress, playerName, password);

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "disconnect", outOptions, outOptionPositions);
        if (numberOfOptions >= 0)
        {
            Ar.Log(STR("Disconnect\n"));
            APManager::Disconnect();

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "release", outOptions, outOptionPositions);
        if (numberOfOptions >= 0)
        {
            /* code */
            Ar.Log(STR("Release\n"));
            Ar.Log(STR("Not implemented yet.\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "collect", outOptions, outOptionPositions);
        if (numberOfOptions >= 0)
        {
            /* code */
            Ar.Log(STR("Collect\n"));
            Ar.Log(STR("Not implemented yet.\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "hint", outOptions, outOptionPositions);
        if (numberOfOptions >= 1)
        {
            /* code */
            Ar.Log(STR("Hint\n"));
            Ar.Log(STR("Not implemented yet.\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "hint_location", outOptions, outOptionPositions);
        if (numberOfOptions >= 1)
        {
            /* code */
            Ar.Log(STR("Hint location\n"));
            Ar.Log(STR("Not implemented yet.\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "remaining", outOptions, outOptionPositions);
        if (numberOfOptions >= 0)
        {
            /* code */
            Ar.Log(STR("Remaining\n"));
            Ar.Log(STR("Not implemented yet.\n"));

            return true;
        }

        numberOfOptions = CompareAndParseCmd(commandCharStr, "send", outOptions, outOptionPositions);
        if (numberOfOptions >= 1) // send a location as done check
        {
            /* code */
            Ar.Log(STR("Send\n"));
            Ar.Log(STR("Not implemented yet.\n"));

            return true;
        }

        return false;
    }
}
