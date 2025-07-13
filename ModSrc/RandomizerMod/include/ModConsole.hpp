#pragma once

using namespace RC;
using namespace RC::Unreal;

extern bool gameReload;
extern UObject* ItemManager;
extern UFunction* ItemReceivedEvent;

typedef struct
{
    TArray<int32_t> ItemAmounts;
    TArray<bool> UnlockedPaintCans;
    TArray<bool> UnlockedWeapons;
}ReceivedItems;

extern ReceivedItems receivedItems;

void LogFromAPCpp(std::string message);

namespace ModConsole {
    using RC::Unreal::FOutputDevice;
	using RC::Unreal::TCHAR;

    bool CheckCommand(FOutputDevice& Ar, const TCHAR* command);
    void ResetItemAmounts();
}
