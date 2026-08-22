/**
 * @author Yaranorgoth
 * @brief Manage all interactions between the AP server and the mod
 */

#pragma once

#include "Archipelago.h"

using namespace RC;
using namespace RC::Unreal;


#define OPTION_MAX_LENGTH 50
#define NB_MAX_OPTIONS 5
#define ALL_OPTIONS_MAX_LENGTH (NB_MAX_OPTIONS * (OPTION_MAX_LENGTH + 1)) // Addition of all options, +1 by option for '\0'

#define UNDEFINED_COMMAND -1
#define MAX_OPTIONS_REACHED -2
#define OPTION_LENGTH_REACHED -3

#define BASE_ID 66600000
#define LOCATION_OFFSET_ID 1000
#define MAX_LOCATIONS 692
#define START_LOCATION_ID (BASE_ID + LOCATION_OFFSET_ID)
#define LAST_LOCATION_ID (START_LOCATION_ID + MAX_LOCATIONS - 1)

typedef enum
{
    LOCATION_ID_START_CAMP = 0,
    LOCATION_ID_BARN = 1,
    LOCATION_ID_TUTORIAL_HOUSE = 2,
    LOCATION_ID_SWAMP = 3,
    LOCATION_ID_SWAMP_SHACK = 4,
    LOCATION_ID_SWAMP_ISLET = 5,
    LOCATION_ID_JUNKYARD_AREA = 6,
    LOCATION_ID_SOUTH_HOUSE = 7,
    LOCATION_ID_JUNKYARD_SHED = 8,
    LOCATION_ID_MILIRARY_BASE = 9,
    LOCATION_ID_SOUTH_MINE_OUTSIDE = 10,
    LOCATION_ID_SOUTH_MINE_INSIDE = 11,
    LOCATION_ID_MIDDLE_STATION = 12,
    LOCATION_ID_CANYON = 13,
    LOCATION_ID_WATCHTOWER = 14,
    LOCATION_ID_BOULER_FIELD = 15,
    LOCATION_ID_HAUNTED_HOUSE = 16,
    LOCATION_ID_SANTIAGO_HOUSE = 17,
    LOCATION_ID_PORT = 18,
    LOCATION_ID_TRENCH_HOUSE = 19,
    LOCATION_ID_DOLL_WOODS = 20,
    LOCATION_ID_LOST_STAIRS = 21,
    LOCATION_ID_EAST_HOUSE = 22,
    LOCATION_ID_ROCKET_GROUNDS = 23,
    LOCATION_ID_ROCKET_BUNKER = 24,
    LOCATION_ID_WORKSHOP = 25,
    LOCATION_ID_EAST_TOWER = 26,
    LOCATION_ID_LIGHTHOUSE = 27,
    LOCATION_ID_NORTH_MINE_OUTSIDE = 28,
    LOCATION_ID_NORTH_MINE_INSIDE = 29,
    LOCATION_ID_WOOD_BRIDGE = 30,
    LOCATION_ID_MUSEUM = 31,
    LOCATION_ID_BARBED_SHELTER = 32,
    LOCATION_ID_WEST_BEACH = 33,
    LOCATION_ID_CHURCH = 34,
    LOCATION_ID_WEST_COTTAGE = 35,
    LOCATION_ID_CARAVAN = 36,
    LOCATION_ID_TRAILER_CABIN = 37,
    LOCATION_ID_TOWERS = 38,
    LOCATION_ID_NORTH_BEACH = 39,
    LOCATION_ID_MINE_SHAFT = 40,
    LOCATION_ID_MOB_CAMP = 41,
    LOCATION_ID_MOB_CAMP_LOCKED_ROOM = 42,
    LOCATION_ID_MINE_ELEVATOR_EXIT = 43,
    LOCATION_ID_MOUNTAIN_RUIN_OUTSIDE = 44,
    LOCATION_ID_MOUNTAIN_RUIN_INSIDE = 45,
    LOCATION_ID_PICKLE_VAL = 46,
    LOCATION_ID_SHRINE_NEAR_TEMPLE = 47,
    LOCATION_ID_MORSE_BUNKER = 48,
    LOCATION_ID_TEMPLE = 49,
    NB_LOCATIONS_WITH_SCRAPS = 50
};


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
    TArray<MWTrainComponent> guns;
}ReceivedItems;


typedef struct {
    AP_ConnectionStatus connectionStatus; // Status of the connection to the AP server
    FString statusMessage; // Connection status to render in UI: connected, offline, depreciated version, ...
    TArray<int64_t> pendingItemIDs; // Pending item received from the AP room
    ReceivedItems allReceivedItems; // All received items from the AP room since its start
    bool pendingDeathLink; // It is true if the player must die because another player died, false otherwise
    TArray<int32_t> nbCheckedScrapsByLocation;
}APData;


typedef enum
{
    TRACK_SWITCHES_OPTION = 0,
    CURSED_FOGS_OPTION = 1,
    SPEED_UPGRADE_OPTION = 2,
    DAMAGE_UPGRADE_OPTION = 3,
    ARMOR_UPGRADE_OPTION = 4,
    STARTING_GUN_OPTION = 5,
    NB_AP_OPTIONS = 6
}APOptions; // Death link is not to consider here


extern APData apData;
extern TArray<int32_t> isAPOptionEnabled;
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
