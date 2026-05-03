
#pragma once

using namespace RC;
using namespace RC::Unreal;


namespace ModConsole {
    using RC::Unreal::FOutputDevice;
	using RC::Unreal::TCHAR;

    bool CheckCommand(FOutputDevice& Ar, const TCHAR* command);
}
