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
    TArray<MWItem> objects;
    TArray<MWTrainComponent> paintCans;
    TArray<MWTrainComponent> weapons;
}ReceivedItems;


typedef enum
{
    TRACK_SWITCHES_OPTION = 0,
    CURSED_FOGS_OPTION = 1,
    NB_AP_OPTIONS = 2,
}APOptions;


extern std::string latestWorldVersion;
extern ReceivedItems receivedItems;
extern TArray<int64_t> pendingItemIDs;
extern TArray<bool> isAPOptionEnabled;

void LogFromAPCpp(std::string message);

namespace ModConsole {
    using RC::Unreal::FOutputDevice;
	using RC::Unreal::TCHAR;

    bool CheckCommand(FOutputDevice& Ar, const TCHAR* command);
    void ResetItemAmounts();
}
