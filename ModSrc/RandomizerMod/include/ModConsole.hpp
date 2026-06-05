/**
 * @author Yaranorgoth
 * @brief Manage all commands typed in the console of the game
 */

#pragma once

using namespace RC;
using namespace RC::Unreal;


namespace ModConsole {
    using RC::Unreal::FOutputDevice;
	using RC::Unreal::TCHAR;

    /**
     * @brief Manage user commands written in the UE console to interact with Archipelago using APCpp
     * @param Ar: The used device (expecting UE console here)
     * @param command: The typed command by the user
     * 
     * @return true if the command is recognized, false otherwise
     */
    bool CheckCommand(FOutputDevice& Ar, const TCHAR* command);
}
