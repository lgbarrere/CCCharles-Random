#pragma once

#include "Unreal/UnrealCoreStructs.hpp"
#include "Unreal/FOutputDevice.hpp"

namespace ModConsole {
    using RC::Unreal::FOutputDevice;
	using RC::Unreal::TCHAR;

    int CheckCommand(FOutputDevice& Ar, const TCHAR* command);
}
