#include "ModConsole.hpp"


#define OPTION_MAX_LENGTH 50
#define NB_MAX_OPTIONS 5
#define ALL_OPTIONS_MAX_LENGTH NB_MAX_OPTIONS * (OPTION_MAX_LENGTH + 1) // Addition of all options +1 by option for '\0'


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
static int CompareAndParseCmd(const TCHAR* command, const char* expectedCmd, TCHAR outOptions[ALL_OPTIONS_MAX_LENGTH], int outOptionPositions[NB_MAX_OPTIONS])
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
static TCHAR* getOptionAtindex(TCHAR options[ALL_OPTIONS_MAX_LENGTH], const int optionPositions[NB_MAX_OPTIONS], const unsigned int index)
{
    if (index >= NB_MAX_OPTIONS || optionPositions[index] == -1)
    {
        return NULL;
    }

    return options + optionPositions[index];
}


namespace ModConsole {
    int ModConsole::CheckCommand(FOutputDevice& Ar, const TCHAR* command)
    {
        TCHAR outOptions[ALL_OPTIONS_MAX_LENGTH];
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
            TCHAR *optionIP = getOptionAtindex(outOptions, outOptionPositions, 0);
            TCHAR *optionPlayerName = getOptionAtindex(outOptions, outOptionPositions, 1);
            TCHAR *optionPassword = getOptionAtindex(outOptions, outOptionPositions, 2);
            
            // TODO : Remove this once the debug is finished
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
