
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
    bool authenticated;
    FString statusMessage;
    FString pendingMessage;
    TArray<int64_t> pendingItemIDs;
    ReceivedItems receivedItems;
    bool pendingDeathLink;
}APInformation;


typedef enum
{
    TRACK_SWITCHES_OPTION = 0,
    CURSED_FOGS_OPTION = 1,
    NB_AP_OPTIONS = 2,
}APOptions; // Death link is not to consider here


extern APInformation information;
extern std::string latestWorldVersion;
extern TArray<bool> isAPOptionEnabled;

const std::string CURRENT_WORLD_VERSION = "1.0.0"; // To update when the version of the AP logic changes
std::string latestWorldVersion;

void LogFromAPCpp(std::string message);

namespace APManager {
    void APManager::setup_AP(const char* ipAddress, const char* playerName, const char* password);
    void APManager::ResetItemAmounts();
    void APManager::Disconnect()
    void APManager::GetConnectionStatus();
    void APManager::CheckDeathLink();
    void APManager::CleanAPInformation();
    void APManager::SendAPLocation(int64_t locationID);
}
