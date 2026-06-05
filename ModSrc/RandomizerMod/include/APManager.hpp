/**
 * @author Yaranorgoth
 * @brief Manage all interactions between the AP server and the mod
 */

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

/**
 * @brief Log used to check APCpp messages
 * @note Prints functions in APCpp code must be manually replaced by calls of this function
 * @param message: The message to log
 */
void LogFromAPCpp(std::string message);

namespace APManager {
    /**
     * @brief Initialize AP data
     */
    void initializeAPData();

    /**
     * @brief Link the AP server to the mod, using its ipAddress a playerName and an optional password
     * @param ipAddress: The address to the AP room
     * @param playerName: The name of the player (slot)
     * @param password: Optional password (provided by the host)
     */
    void Setup_AP(const char* ipAddress, const char* playerName, const char* password);

    /**
     * @brief Reset all received items amounts and all unlocked train components to 0
     */
    void ResetItemAmounts();

    /**
     * @brief Disconnect from the AP server
     */
    void Disconnect();

    /**
     * @brief Check if the player is authenticated or not
     */
    void UpdateConnectionStatus();

    /**
     * @brief Check a Deathlink was received
     */
    void CheckDeathLink();

    /**
     * @brief Clean old AP data
     */
    void CleanAPData();

    /**
     * @brief The the given locationID the to AP server
     * @param locationID: The ID of the checked location
     */
    void SendAPLocation(int64_t locationID);

    /**
     * @brief Send to the AP server the victory event, meaning the goal has been reached
     */
    void Victory();
}
