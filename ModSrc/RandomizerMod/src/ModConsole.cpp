#include "ModConsole.hpp"


#define MAX_OPTION_LENGTH 50
#define NB_MAX_OPTIONS 5


/**
*   @param command : The input command to compare and parse
*   @param expectedCmd : The expected command name to compare with the input command
*   @param outOptions : An out array copying the parsed options separated with '\0'
*   @param outOptionPositions : An out array with the positions of all options in outOptions (-1 if no option at the position)
*   @note If an option exceeds MAX_OPTION_LENGTH char or if more options than NB_MAX_OPTIONS are found, -1 is returned
*   @note Get an option with outOptions[outOptionPositions[i]]) with i from 0 to the returned number of parsed options
* 
*   @todo This function should be optimized by comparing the input command wuth all known command names at once
* 
*   @return The number of parsed options, -1 if the command is not correct
*/
static int CompareAndParseCmd(const TCHAR* command, const char* expectedCmd, TCHAR outOptions[NB_MAX_OPTIONS * MAX_OPTION_LENGTH], int outOptionPositions[NB_MAX_OPTIONS])
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

        // Ignore trailing separators after comparision, the command name is recognized
        while (command[i] == separator)
        {
            i++;
        }

        // Copy the found option until the next separator or the end of the command 
        while (command[i] != separator && command[i] != '\n' && command[i] != '\0')
        {
            outOptions[j] = command[i];
            i++;
            j++;
        }

        outOptions[j] = '\0';
        j++;
        numberOfParsedOptions++;
    }

    return numberOfParsedOptions;
}


namespace ModConsole {
    int ModConsole::CheckCommand(FOutputDevice& Ar, const TCHAR* command)
    {
        TCHAR outOptions[NB_MAX_OPTIONS * MAX_OPTION_LENGTH];
        int outOptionPositions[NB_MAX_OPTIONS];

        int numberOfOptions = CompareAndParseCmd(command, "help", outOptions, outOptionPositions);
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
        numberOfOptions = CompareAndParseCmd(command, "connect", outOptions, outOptionPositions);
        if (numberOfOptions >= 2) // At least 2 options are required for the "connect" command
        {
            Ar.Log(STR("Command recognized\n"));
            TCHAR *optionIP = outOptions + outOptionPositions[0];
            TCHAR *optionPlayerName = outOptions + outOptionPositions[1];
            TCHAR *optionPassword = outOptions + outOptionPositions[2];
            
            // TODO : Remove this once the debug is finised
            Ar.Log(STR("Option1 :\n"));
            Ar.Log(optionIP);
            Ar.Log(STR("Option2 :\n"));
            Ar.Log(optionPlayerName);
            Ar.Log(STR("Option3 :\n"));
            Ar.Log(optionPassword);
            
            // To use after being connected
            // AP_SetItemClearCallback(void (*f_itemclr)());
            // AP_SetItemRecvCallback(void (*f_itemrecv)(int,bool));
            // AP_SetLocationCheckedCallback(void (*f_locrecv)(int));
            // AP_Start();

            return 1;
        }
        else if (CompareAndParseCmd(command, "disconnect", outOptions, outOptionPositions))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "release", outOptions, outOptionPositions))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "collect", outOptions, outOptionPositions))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "hint", outOptions, outOptionPositions))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "hint_location", outOptions, outOptionPositions))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "remaining", outOptions, outOptionPositions))
        {
            /* code */
        }
		else if (CompareAndParseCmd(command, "get", outOptions, outOptionPositions)) // get an item as done check
        {
            /* code */
        }
        
        return 0;
    }
}
