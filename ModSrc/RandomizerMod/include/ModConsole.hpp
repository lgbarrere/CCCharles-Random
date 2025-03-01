#pragma once

using namespace RC;
using namespace RC::Unreal;

extern bool gameReload;
extern UObject* ItemManager;
extern UFunction* ItemReceivedEvent;

namespace ModConsole {
    using RC::Unreal::FOutputDevice;
	using RC::Unreal::TCHAR;

    int CheckCommand(FOutputDevice& Ar, const TCHAR* command);
}
