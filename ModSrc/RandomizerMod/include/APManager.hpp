
#pragma once

using namespace RC;
using namespace RC::Unreal;


#define OPTION_MAX_LENGTH 50
#define NB_MAX_OPTIONS 5
#define ALL_OPTIONS_MAX_LENGTH (NB_MAX_OPTIONS * (OPTION_MAX_LENGTH + 1)) // Addition of all options, +1 by option for '\0'

#define UNDEFINED_COMMAND -1
#define MAX_OPTIONS_REACHED -2
#define OPTION_LENGTH_REACHED -3

#define BASE_ID 66600000


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


typedef struct {
    bool authenticated; // It is true if the player is connected to the AP room, false otherwise
    FString statusMessage; // Connection status to render in UI: connected, offline, depreciated version, ...
    TArray<int64_t> pendingItemIDs; // Pending item received from the AP room
    ReceivedItems allReceivedItems; // All received items from the AP room since its start
    bool pendingDeathLink; // It is true if the player must die because another player died, false otherwise
}APData;


typedef enum
{
    TRACK_SWITCHES_OPTION = 0,
    CURSED_FOGS_OPTION = 1,
    NB_AP_OPTIONS = 2
}APOptions; // Death link is not to consider here


extern APData apData;
extern TArray<bool> isAPOptionEnabled;
extern std::string latestWorldVersion;

void LogFromAPCpp(std::string message);

namespace APManager {
    void initializeAPData();
    void Setup_AP(const char* ipAddress, const char* playerName, const char* password);
    void ResetItemAmounts();
    void Disconnect();
    void UpdateConnectionStatus();
    void CheckDeathLink();
    void CleanAPData();
    void SendAPLocation(int64_t locationID);
    void Victory();
    bool CheckEggByIndex(int32_t index);
}
