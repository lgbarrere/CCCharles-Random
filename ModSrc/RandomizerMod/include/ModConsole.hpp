#pragma once

using namespace RC;
using namespace RC::Unreal;

extern UObject* ItemManager;
extern UFunction* ItemReceivedEvent;

typedef struct
{
    FString name;
    int32_t amount;
}MWItem;

typedef struct
{
    FString name;
    bool unlocked;
}MWTrainComponent;

typedef struct
{
    TArray<MWItem> items;
    TArray<MWTrainComponent> paintCans;
    TArray<MWTrainComponent> weapons;
}ReceivedItems;


extern ReceivedItems receivedItems;
extern TArray<int64_t> pendingItemIDs;

void LogFromAPCpp(std::string message);

namespace ModConsole {
    using RC::Unreal::FOutputDevice;
	using RC::Unreal::TCHAR;

    bool CheckCommand(FOutputDevice& Ar, const TCHAR* command);
    void ResetItemAmounts();
}
