#include "ModConsole.hpp"


static const TCHAR* CompareAndParseCmd(const TCHAR* command, const char* expectedCmd, const char separator)
{
    int i = 0;

    while (expectedCmd[i] != '\0')
    {
        // If a char is different, the command is not recognized
        if (command[i] != expectedCmd[i])
        {
            return NULL;
        }
        i++;
    }

    if (command[i] == separator) // Command recognized, check if the separator is found
    {
        return command+i+1;
    }
    else if (command[i] == '\n' || command[i] == '\0') // The end of command is reached
    {
        return command+i;
    }
    return NULL;
}


namespace ModConsole {
    int ModConsole::CheckCommand(FOutputDevice& Ar, const TCHAR* command)
    {
        const TCHAR* parsedCmd = CompareAndParseCmd(command, "help", ' ');
        if (parsedCmd != NULL)
        {
            // Print in console
            Ar.Log(STR("/help\n"));
            Ar.Log(STR("        Shows all available commands\n"));
            Ar.Log(STR("/connect <IP>\n"));
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
        // Example : /connect archipelago.gg:59157
        parsedCmd = CompareAndParseCmd(command, "connect", ' ');
        if (parsedCmd != NULL)
        {
            if (*parsedCmd == '\0') // Check the end of command is reached
                Ar.Log(STR("OK\n"));
            else // Otherwise, the command has an option
                Ar.Log(STR("KO\n"));
            
            // To use after being connected
            // AP_SetItemClearCallback(void (*f_itemclr)());
            // AP_SetItemRecvCallback(void (*f_itemrecv)(int,bool));
            // AP_SetLocationCheckedCallback(void (*f_locrecv)(int));
            // AP_Start();

            return 1;
        }
        else if (CompareAndParseCmd(command, "disconnect", ' '))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "release", ' '))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "collect", ' '))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "hint", ' '))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "hint_location", ' '))
        {
            /* code */
        }
        else if (CompareAndParseCmd(command, "remaining", ' '))
        {
            /* code */
        }
		else if (CompareAndParseCmd(command, "get", ' ')) // get an item as done check
        {
            /* code */
        }
        
        return 0;
    }
}
