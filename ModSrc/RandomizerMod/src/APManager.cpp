#include <Unreal/UObject.hpp>

#include "APManager.hpp"
#include "Archipelago.h"
#include "Helpers/String.hpp"

using namespace std;
using namespace RC;
using namespace RC::Unreal;


APData apData;
TArray<int32_t> isAPOptionEnabled;
std::string latestWorldVersion;
const std::string CURRENT_WORLD_VERSION = "1.0.1"; // To update when the version of the AP logic changes


/**
 * @brief Clear all the collected items from the player's inventory
 * @notimplemented Used by AP_SetItemClearCallback but is not necessary
 */
static void ClearInventoryCallback()
{

}


/**
 * @brief Receive an item from any world
 * @param itemID: The ID of the received item
 * @param notifyPlayer: Id true, notify the player about the received item, false otherwise
 */
static void ItemReceivedCallback(int64_t itemID, bool notifyPlayer)
{
    // Add 1 item from the received itemID to the inventory
    int cappedAmount = 1; // Consider by default 1 item must be added (to set to 0 if the cap is reached)
    int amountToAdd = 0; // Used for "Remote Explosives" packs (can be greatter than 1)
    int index = (int)(itemID - BASE_ID);

    switch (index)
    {
    case 1: // Scraps
        apData.allReceivedItems.items[0].amount += 1; // No cap for scraps
        break;
    case 2: // Scraps (reward 30)
        apData.allReceivedItems.items[0].amount += 30; // No cap for scraps
        break;
    case 3: // Scraps (reward 25)
        apData.allReceivedItems.items[0].amount += 25; // No cap for scraps
        break;
    case 4: // Scraps (reward 35)
        apData.allReceivedItems.items[0].amount += 35; // No cap for scraps
        break;
    case 5: // Scraps (reward 40)
        apData.allReceivedItems.items[0].amount += 40; // No cap for scraps
        break;
    case 6: // South mine key
        apData.allReceivedItems.items[1].amount < 1 ? apData.allReceivedItems.items[1].amount += 1 : cappedAmount = 0;
        break;
    case 7: // North mine key
        apData.allReceivedItems.items[2].amount < 1 ? apData.allReceivedItems.items[2].amount += 1 : cappedAmount = 0;
        break;
    case 8: // Mountain ruin key
        apData.allReceivedItems.items[3].amount < 1 ? apData.allReceivedItems.items[3].amount += 1 : cappedAmount = 0;
        break;
    case 9: // Barn key
        apData.allReceivedItems.items[4].amount < 1 ? apData.allReceivedItems.items[4].amount += 1 : cappedAmount = 0;
        break;
    case 10: // Candice key
        apData.allReceivedItems.items[5].amount < 1 ? apData.allReceivedItems.items[5].amount += 1 : cappedAmount = 0;
        break;
    case 11: // Dead fish
        apData.allReceivedItems.items[6].amount < 1 ? apData.allReceivedItems.items[6].amount += 1 : cappedAmount = 0;
        break;
    case 12: // Lockpicks
        apData.allReceivedItems.items[7].amount < 1 ? apData.allReceivedItems.items[7].amount += 1 : cappedAmount = 0;
        break;
    case 13: // Ancient tablet
        apData.allReceivedItems.items[8].amount < 1 ? apData.allReceivedItems.items[8].amount += 1 : cappedAmount = 0;
        break;
    case 14: // Blue box
        apData.allReceivedItems.items[9].amount < 1 ? apData.allReceivedItems.items[9].amount += 1 : cappedAmount = 0;
        break;
    case 15: // Page Drawing
        apData.allReceivedItems.items[10].amount < 8 ? apData.allReceivedItems.items[10].amount += 1 : cappedAmount = 0;
        break;
    case 16: // Journal
        apData.allReceivedItems.items[11].amount < 1 ? apData.allReceivedItems.items[11].amount += 1 : cappedAmount = 0;
        break;
    case 17: // Dynamite
        apData.allReceivedItems.items[12].amount < 1 ? apData.allReceivedItems.items[12].amount += 1 : cappedAmount = 0;
        break;
    case 18: // Boomer rockets
        apData.allReceivedItems.items[13].amount < 1 ? apData.allReceivedItems.items[13].amount += 1 : cappedAmount = 0;
        break;
    case 19: // Breaker
        apData.allReceivedItems.items[14].amount < 4 ? apData.allReceivedItems.items[14].amount += 1 : cappedAmount = 0;
        break;
    case 20: // Broken Bob
        apData.allReceivedItems.items[15].amount < 1 ? apData.allReceivedItems.items[15].amount += 1 : cappedAmount = 0;
        break;
    case 21: // Employment contracts
        apData.allReceivedItems.items[16].amount < 1 ? apData.allReceivedItems.items[16].amount += 1 : cappedAmount = 0;
        break;
    case 22: // Mob camp key
        apData.allReceivedItems.items[17].amount < 1 ? apData.allReceivedItems.items[17].amount += 1 : cappedAmount = 0;
        break;
    case 23: // Pickles jar
        apData.allReceivedItems.items[18].amount < 1 ? apData.allReceivedItems.items[18].amount += 1 : cappedAmount = 0;
        break;
    case 24: // Orange Paint Can
        apData.allReceivedItems.paintCans[0].unlocked == false ? apData.allReceivedItems.paintCans[0].unlocked = true : cappedAmount = 0;
        break;
    case 25: // Green Paint Can
        apData.allReceivedItems.paintCans[1].unlocked == false ? apData.allReceivedItems.paintCans[1].unlocked = true : cappedAmount = 0;
        break;
    case 26: // White Paint Can
        apData.allReceivedItems.paintCans[2].unlocked == false ? apData.allReceivedItems.paintCans[2].unlocked = true : cappedAmount = 0;
        break;
    case 27: // Pink Paint Can
        apData.allReceivedItems.paintCans[3].unlocked == false ? apData.allReceivedItems.paintCans[3].unlocked = true : cappedAmount = 0;
        break;
    case 28: // Gray Paint Can
        apData.allReceivedItems.paintCans[4].unlocked == false ? apData.allReceivedItems.paintCans[4].unlocked = true : cappedAmount = 0;
        break;
    case 29: // Blue Paint Can
        apData.allReceivedItems.paintCans[5].unlocked == false ? apData.allReceivedItems.paintCans[5].unlocked = true : cappedAmount = 0;
        break;
    case 30: // Black Paint Can
        apData.allReceivedItems.paintCans[6].unlocked == false ? apData.allReceivedItems.paintCans[6].unlocked = true : cappedAmount = 0;
        break;
    case 31: // Lime Paint Can
        apData.allReceivedItems.paintCans[7].unlocked == false ? apData.allReceivedItems.paintCans[7].unlocked = true : cappedAmount = 0;
        break;
    case 32: // Teal Paint Can
        apData.allReceivedItems.paintCans[8].unlocked == false ? apData.allReceivedItems.paintCans[8].unlocked = true : cappedAmount = 0;
        break;
    case 33: // Red Paint Can
        apData.allReceivedItems.paintCans[9].unlocked == false ? apData.allReceivedItems.paintCans[9].unlocked = true : cappedAmount = 0;
        break;
    case 34: // Purple Paint Can
        apData.allReceivedItems.paintCans[10].unlocked == false ? apData.allReceivedItems.paintCans[10].unlocked = true : cappedAmount = 0;
        break;
    case 35: // The Boomer
        apData.allReceivedItems.guns[0].unlocked == false ? apData.allReceivedItems.guns[0].unlocked = true : cappedAmount = 0;
        break;
    case 36: // Bob
        apData.allReceivedItems.guns[1].unlocked == false ? apData.allReceivedItems.guns[1].unlocked = true : cappedAmount = 0;
        break;
    case 37: // Green egg
        apData.allReceivedItems.items[19].amount < 1 ? apData.allReceivedItems.items[19].amount += 1 : cappedAmount = 0;
        break;
    case 38: // Blue egg
        apData.allReceivedItems.items[20].amount < 1 ? apData.allReceivedItems.items[20].amount += 1 : cappedAmount = 0;
        break;
    case 39: // Red egg
        apData.allReceivedItems.items[21].amount < 1 ? apData.allReceivedItems.items[21].amount += 1 : cappedAmount = 0;
        break;
    case 40: // Remote explosives
        apData.allReceivedItems.items[22].amount < 8 ? apData.allReceivedItems.items[22].amount += 1 : cappedAmount = 0;
        break;
    case 41: // Remote explosives (x8)
        amountToAdd = 8;
        itemID = BASE_ID + 40; // Change id to "Remote explosives" to add it cappedAmount times
        cappedAmount = (apData.allReceivedItems.items[22].amount + amountToAdd <= 8) ? amountToAdd : 8 - apData.allReceivedItems.items[22].amount;
        apData.allReceivedItems.items[22].amount += cappedAmount;
        break;
    case 42: // Temple key
        apData.allReceivedItems.items[23].amount < 1 ? apData.allReceivedItems.items[23].amount += 1 : cappedAmount = 0;
        break;
    case 43: // Bug Spray
        apData.allReceivedItems.guns[2].unlocked == false ? apData.allReceivedItems.guns[2].unlocked = true : cappedAmount = 0;
        break;
    case 44 : // Track Switch Pack
        apData.allReceivedItems.objects[0].amount < 1 ? apData.allReceivedItems.objects[0].amount += 1 : cappedAmount = 0;
        break;
    case 45: // Track Switch - Barn or Tutorial
        apData.allReceivedItems.objects[1].amount < 1 ? apData.allReceivedItems.objects[1].amount += 1 : cappedAmount = 0;
        break;
    case 46: // Track Switch - Middle or Port
        apData.allReceivedItems.objects[2].amount < 1 ? apData.allReceivedItems.objects[2].amount += 1 : cappedAmount = 0;
        break;
    case 47: // Track Switch - Haunted or East
        apData.allReceivedItems.objects[3].amount < 1 ? apData.allReceivedItems.objects[3].amount += 1 : cappedAmount = 0;
        break;
    case 48: // Track Switch - North or Temple
        apData.allReceivedItems.objects[4].amount < 1 ? apData.allReceivedItems.objects[4].amount += 1 : cappedAmount = 0;
        break;
    case 49: // Track Switch - Caravan or Cultists
        apData.allReceivedItems.objects[5].amount < 1 ? apData.allReceivedItems.objects[5].amount += 1 : cappedAmount = 0;
        break;
    case 50: // Track Switch - Camp or Elevator
        apData.allReceivedItems.objects[6].amount < 1 ? apData.allReceivedItems.objects[6].amount += 1 : cappedAmount = 0;
        break;
    case 51: // Track Switch - Ruin or Temple
        apData.allReceivedItems.objects[7].amount < 1 ? apData.allReceivedItems.objects[7].amount += 1 : cappedAmount = 0;
        break;
    case 52: // Fogbane Relic Pack
        apData.allReceivedItems.objects[8].amount < 1 ? apData.allReceivedItems.objects[8].amount += 1 : cappedAmount = 0;
        break;
    case 53: // Fogbane Relic - Mine Shaft
        apData.allReceivedItems.objects[9].amount < 1 ? apData.allReceivedItems.objects[9].amount += 1 : cappedAmount = 0;
        break;
    case 54: // Fogbane Relic - Junkyard Area
        apData.allReceivedItems.objects[10].amount < 1 ? apData.allReceivedItems.objects[10].amount += 1 : cappedAmount = 0;
        break;
    case 55: // Fogbane Relic - Junkyard Shed
        apData.allReceivedItems.objects[11].amount < 1 ? apData.allReceivedItems.objects[11].amount += 1 : cappedAmount = 0;
        break;
    case 56: // Fogbane Relic - South House
        apData.allReceivedItems.objects[12].amount < 1 ? apData.allReceivedItems.objects[12].amount += 1 : cappedAmount = 0;
        break;
    case 57: // Fogbane Relic - Military Base
        apData.allReceivedItems.objects[13].amount < 1 ? apData.allReceivedItems.objects[13].amount += 1 : cappedAmount = 0;
        break;
    case 58: // Fogbane Relic - South Mine Outside
        apData.allReceivedItems.objects[14].amount < 1 ? apData.allReceivedItems.objects[14].amount += 1 : cappedAmount = 0;
        break;
    case 59: // Fogbane Relic - Middle Station
        apData.allReceivedItems.objects[15].amount < 1 ? apData.allReceivedItems.objects[15].amount += 1 : cappedAmount = 0;
        break;
    case 60: // Fogbane Relic - Canyon
        apData.allReceivedItems.objects[16].amount < 1 ? apData.allReceivedItems.objects[16].amount += 1 : cappedAmount = 0;
        break;
    case 61: // Fogbane Relic - Watchtower
        apData.allReceivedItems.objects[17].amount < 1 ? apData.allReceivedItems.objects[17].amount += 1 : cappedAmount = 0;
        break;
    case 62: // Fogbane Relic - Haunted House
        apData.allReceivedItems.objects[18].amount < 1 ? apData.allReceivedItems.objects[18].amount += 1 : cappedAmount = 0;
        break;
    case 63: // Fogbane Relic - Santiago House
        apData.allReceivedItems.objects[19].amount < 1 ? apData.allReceivedItems.objects[19].amount += 1 : cappedAmount = 0;
        break;
    case 64: // Fogbane Relic - Port
        apData.allReceivedItems.objects[20].amount < 1 ? apData.allReceivedItems.objects[20].amount += 1 : cappedAmount = 0;
        break;
    case 65: // Fogbane Relic - Doll Woods
        apData.allReceivedItems.objects[21].amount < 1 ? apData.allReceivedItems.objects[21].amount += 1 : cappedAmount = 0;
        break;
    case 66: // Fogbane Relic - East House
        apData.allReceivedItems.objects[22].amount < 1 ? apData.allReceivedItems.objects[22].amount += 1 : cappedAmount = 0;
        break;
    case 67: // Fogbane Relic - Rocket Grounds
        apData.allReceivedItems.objects[23].amount < 1 ? apData.allReceivedItems.objects[23].amount += 1 : cappedAmount = 0;
        break;
    case 68: // Fogbane Relic - Workshop
        apData.allReceivedItems.objects[24].amount < 1 ? apData.allReceivedItems.objects[24].amount += 1 : cappedAmount = 0;
        break;
    case 69: // Fogbane Relic - East Tower
        apData.allReceivedItems.objects[25].amount < 1 ? apData.allReceivedItems.objects[25].amount += 1 : cappedAmount = 0;
        break;
    case 70: // Fogbane Relic - Lighthouse
        apData.allReceivedItems.objects[26].amount < 1 ? apData.allReceivedItems.objects[26].amount += 1 : cappedAmount = 0;
        break;
    case 71: // Fogbane Relic - North Mine Outside
        apData.allReceivedItems.objects[27].amount < 1 ? apData.allReceivedItems.objects[27].amount += 1 : cappedAmount = 0;
        break;
    case 72: // Fogbane Relic - Wood Bridge
        apData.allReceivedItems.objects[28].amount < 1 ? apData.allReceivedItems.objects[28].amount += 1 : cappedAmount = 0;
        break;
    case 73: // Fogbane Relic - Museum
        apData.allReceivedItems.objects[29].amount < 1 ? apData.allReceivedItems.objects[29].amount += 1 : cappedAmount = 0;
        break;
    case 74: // Fogbane Relic - Barbed Shelter
        apData.allReceivedItems.objects[30].amount < 1 ? apData.allReceivedItems.objects[30].amount += 1 : cappedAmount = 0;
        break;
    case 75: // Fogbane Relic - West Beach
        apData.allReceivedItems.objects[31].amount < 1 ? apData.allReceivedItems.objects[31].amount += 1 : cappedAmount = 0;
        break;
    case 76: // Fogbane Relic - Church
        apData.allReceivedItems.objects[32].amount < 1 ? apData.allReceivedItems.objects[32].amount += 1 : cappedAmount = 0;
        break;
    case 77: // Fogbane Relic - West Cottage
        apData.allReceivedItems.objects[33].amount < 1 ? apData.allReceivedItems.objects[33].amount += 1 : cappedAmount = 0;
        break;
    case 78: // Fogbane Relic - Trailer Cabin
        apData.allReceivedItems.objects[34].amount < 1 ? apData.allReceivedItems.objects[34].amount += 1 : cappedAmount = 0;
        break;
    case 79: // Fogbane Relic - Towers
        apData.allReceivedItems.objects[35].amount < 1 ? apData.allReceivedItems.objects[35].amount += 1 : cappedAmount = 0;
        break;
    case 80: // Fogbane Relic - North Beach
        apData.allReceivedItems.objects[36].amount < 1 ? apData.allReceivedItems.objects[36].amount += 1 : cappedAmount = 0;
        break;
    case 81: // Fogbane Relic - Mob Camp
        apData.allReceivedItems.objects[37].amount < 1 ? apData.allReceivedItems.objects[37].amount += 1 : cappedAmount = 0;
        break;
    case 82: // Fogbane Relic - Mine Elevator Exit
        apData.allReceivedItems.objects[38].amount < 1 ? apData.allReceivedItems.objects[38].amount += 1 : cappedAmount = 0;
        break;
    case 83: // Fogbane Relic - Mountain Ruin Outside
        apData.allReceivedItems.objects[39].amount < 1 ? apData.allReceivedItems.objects[39].amount += 1 : cappedAmount = 0;
        break;
    case 84: // Fogbane Relic - Temple
        apData.allReceivedItems.objects[40].amount < 1 ? apData.allReceivedItems.objects[40].amount += 1 : cappedAmount = 0;
        break;
    case 85: // Fogbane Relic - Pickle Val
        apData.allReceivedItems.objects[41].amount < 1 ? apData.allReceivedItems.objects[41].amount += 1 : cappedAmount = 0;
        break;
    case 86: // Fogbane Relic - Morse Bunker
        apData.allReceivedItems.objects[42].amount < 1 ? apData.allReceivedItems.objects[42].amount += 1 : cappedAmount = 0;
        break;
    case 87: // Speed Unlock
        apData.allReceivedItems.objects[43].amount < 1 ? apData.allReceivedItems.objects[43].amount += 1 : cappedAmount = 0;
        break;
    case 88: // Damage Unlock
        apData.allReceivedItems.objects[44].amount < 1 ? apData.allReceivedItems.objects[44].amount += 1 : cappedAmount = 0;
        break;
    case 89: // Armor Unlock
        apData.allReceivedItems.objects[45].amount < 1 ? apData.allReceivedItems.objects[45].amount += 1 : cappedAmount = 0;
        break;
    case 90: // Speed Level
        apData.allReceivedItems.items[24].amount < 9 ? apData.allReceivedItems.items[24].amount += 1 : cappedAmount = 0;
        break;
    case 91: // Damage Level
        apData.allReceivedItems.items[25].amount < 9 ? apData.allReceivedItems.items[25].amount += 1 : cappedAmount = 0;
        break;
    case 92: // Armor Level
        apData.allReceivedItems.items[26].amount < 9 ? apData.allReceivedItems.items[26].amount += 1 : cappedAmount = 0;
        break;
    case 93: // Derailer
        apData.allReceivedItems.guns[3].unlocked == false ? apData.allReceivedItems.guns[3].unlocked = true : cappedAmount = 0;
        break;
    default:
        Output::send<LogLevel::Error>(STR("Unrecognized item ID skipped.\n"));
        return;
    }

    // If notifyPlayer is true, this ID is received for the first time, add it in pendingItemIDs
    if (notifyPlayer
        || (index >= 24 && index <= 34) // Special case for Paint Cans
        || (index >= 44 && index <= 86)) // Special case for Objects
    {
        for (int i = 0; i < cappedAmount; i++)
        {
            apData.pendingItemIDs.Emplace(itemID);
        }
    }
}


/**
 * @brief Convert a locationID to a scraps location index
 * @param locationID: The ID of the location
 * @note The returned index is usefull to access a value from nbCheckedScrapsByLocation[]
 * 
 * @return The scraps location index or -1 if the locationID is not a scraps location
 */
static int getIndexOfLocationID(int64_t locationID)
{
    int index = -1;
    if (locationID >= BASE_ID + 1000 && locationID <= BASE_ID + 1001)
    {
        index = LOCATION_ID_START_CAMP;
    }
    else if (locationID >= BASE_ID + 1003 && locationID <= BASE_ID + 1011)
    {
        index = LOCATION_ID_BARN;
    }
    else if (locationID >= BASE_ID + 1013 && locationID <= BASE_ID + 1021)
    {
        index = LOCATION_ID_TUTORIAL_HOUSE;
    }
    else if (locationID >= BASE_ID + 1022 && locationID <= BASE_ID + 1053)
    {
        index = LOCATION_ID_SWAMP;
    }
    else if (locationID >= BASE_ID + 1054 && locationID <= BASE_ID + 1055)
    {
        index = LOCATION_ID_SWAMP_SHACK;
    }
    else if (locationID >= BASE_ID + 1056 && locationID <= BASE_ID + 1058)
    {
        index = LOCATION_ID_SWAMP_ISLET;
    }
    else if (locationID >= BASE_ID + 1061 && locationID <= BASE_ID + 1070)
    {
        index = LOCATION_ID_JUNKYARD_AREA;
    }
    else if (locationID >= BASE_ID + 1074 && locationID <= BASE_ID + 1091)
    {
        index = LOCATION_ID_SOUTH_HOUSE;
    }
    else if (locationID >= BASE_ID + 1093 && locationID <= BASE_ID + 1100)
    {
        index = LOCATION_ID_JUNKYARD_SHED;
    }
    else if (locationID >= BASE_ID + 1102 && locationID <= BASE_ID + 1113)
    {
        index = LOCATION_ID_MILIRARY_BASE;
    }
    else if (locationID >= BASE_ID + 1115 && locationID <= BASE_ID + 1121)
    {
        index = LOCATION_ID_SOUTH_MINE_OUTSIDE;
    }
    else if (locationID >= BASE_ID + 1122 && locationID <= BASE_ID + 1130)
    {
        index = LOCATION_ID_SOUTH_MINE_INSIDE;
    }
    else if (locationID >= BASE_ID + 1134 && locationID <= BASE_ID + 1153)
    {
        index = LOCATION_ID_MIDDLE_STATION;
    }
    else if (locationID >= BASE_ID + 1155 && locationID <= BASE_ID + 1171)
    {
        index = LOCATION_ID_CANYON;
    }
    else if (locationID >= BASE_ID + 1173 && locationID <= BASE_ID + 1182)
    {
        index = LOCATION_ID_WATCHTOWER;
    }
    else if (locationID >= BASE_ID + 1192 && locationID <= BASE_ID + 1209)
    {
        index = LOCATION_ID_BOULER_FIELD;
    }
    else if (locationID >= BASE_ID + 1211 && locationID <= BASE_ID + 1216)
    {
        index = LOCATION_ID_HAUNTED_HOUSE;
    }
    else if (locationID >= BASE_ID + 1217 && locationID <= BASE_ID + 1226)
    {
        index = LOCATION_ID_SANTIAGO_HOUSE;
    }
    else if (locationID >= BASE_ID + 1229 && locationID <= BASE_ID + 1247)
    {
        index = LOCATION_ID_PORT;
    }
    else if (locationID >= BASE_ID + 1249 && locationID <= BASE_ID + 1272)
    {
        index = LOCATION_ID_TRENCH_HOUSE;
    }
    else if (locationID >= BASE_ID + 1273 && locationID <= BASE_ID + 1282)
    {
        index = LOCATION_ID_DOLL_WOODS;
    }
    else if (locationID >= BASE_ID + 1283 && locationID <= BASE_ID + 1284)
    {
        index = LOCATION_ID_LOST_STAIRS;
    }
    else if (locationID >= BASE_ID + 1285 && locationID <= BASE_ID + 1303)
    {
        index = LOCATION_ID_EAST_HOUSE;
    }
    else if (locationID >= BASE_ID + 1305 && locationID <= BASE_ID + 1314)
    {
        index = LOCATION_ID_ROCKET_GROUNDS;
    }
    else if (locationID >= BASE_ID + 1315 && locationID <= BASE_ID + 1316)
    {
        index = LOCATION_ID_ROCKET_BUNKER;
    }
    else if (locationID >= BASE_ID + 1318 && locationID <= BASE_ID + 1323)
    {
        index = LOCATION_ID_WORKSHOP;
    }
    else if (locationID >= BASE_ID + 1326 && locationID <= BASE_ID + 1331)
    {
        index = LOCATION_ID_EAST_TOWER;
    }
    else if (locationID >= BASE_ID + 1332 && locationID <= BASE_ID + 1349)
    {
        index = LOCATION_ID_LIGHTHOUSE;
    }
    else if (locationID >= BASE_ID + 1355 && locationID <= BASE_ID + 1369)
    {
        index = LOCATION_ID_NORTH_MINE_OUTSIDE;
    }
    else if (locationID >= BASE_ID + 1370 && locationID <= BASE_ID + 1383)
    {
        index = LOCATION_ID_NORTH_MINE_INSIDE;
    }
    else if (locationID >= BASE_ID + 1386 && locationID <= BASE_ID + 1398)
    {
        index = LOCATION_ID_WOOD_BRIDGE;
    }
    else if (locationID >= BASE_ID + 1399 && locationID <= BASE_ID + 1410)
    {
        index = LOCATION_ID_MUSEUM;
    }
    else if (locationID >= BASE_ID + 1414 && locationID <= BASE_ID + 1418)
    {
        index = LOCATION_ID_BARBED_SHELTER;
    }
    else if (locationID >= BASE_ID + 1419 && locationID <= BASE_ID + 1432)
    {
        index = LOCATION_ID_WEST_BEACH;
    }
    else if (locationID >= BASE_ID + 1434 && locationID <= BASE_ID + 1445)
    {
        index = LOCATION_ID_CHURCH;
    }
    else if (locationID >= BASE_ID + 1447 && locationID <= BASE_ID + 1451)
    {
        index = LOCATION_ID_WEST_COTTAGE;
    }
    else if (locationID >= BASE_ID + 1452 && locationID <= BASE_ID + 1465)
    {
        index = LOCATION_ID_CARAVAN;
    }
    else if (locationID >= BASE_ID + 1466 && locationID <= BASE_ID + 1471)
    {
        index = LOCATION_ID_TRAILER_CABIN;
    }
    else if (locationID >= BASE_ID + 1472 && locationID <= BASE_ID + 1498)
    {
        index = LOCATION_ID_TOWERS;
    }
    else if (locationID >= BASE_ID + 1502 && locationID <= BASE_ID + 1520)
    {
        index = LOCATION_ID_NORTH_BEACH;
    }
    else if (locationID >= BASE_ID + 1522 && locationID <= BASE_ID + 1542)
    {
        index = LOCATION_ID_MINE_SHAFT;
    }
    else if (locationID >= BASE_ID + 1544 && locationID <= BASE_ID + 1559)
    {
        index = LOCATION_ID_MOB_CAMP;
    }
    else if (locationID >= BASE_ID + 1560 && locationID <= BASE_ID + 1561)
    {
        index = LOCATION_ID_MOB_CAMP_LOCKED_ROOM;
    }
    else if (locationID >= BASE_ID + 1563 && locationID <= BASE_ID + 1571)
    {
        index = LOCATION_ID_MINE_ELEVATOR_EXIT;
    }
    else if (locationID >= BASE_ID + 1572 && locationID <= BASE_ID + 1588)
    {
        index = LOCATION_ID_MOUNTAIN_RUIN_OUTSIDE;
    }
    else if (locationID >= BASE_ID + 1589 && locationID <= BASE_ID + 1605)
    {
        index = LOCATION_ID_MOUNTAIN_RUIN_INSIDE;
    }
    else if (locationID >= BASE_ID + 1608 && locationID <= BASE_ID + 1630)
    {
        index = LOCATION_ID_PICKLE_VAL;
    }
    else if (locationID >= BASE_ID + 1634 && locationID <= BASE_ID + 1636)
    {
        index = LOCATION_ID_SHRINE_NEAR_TEMPLE;
    }
    else if (locationID >= BASE_ID + 1637 && locationID <= BASE_ID + 1654)
    {
        index = LOCATION_ID_MORSE_BUNKER;
    }
    else if (locationID >= BASE_ID + 1655 && locationID <= BASE_ID + 1691)
    {
        index = LOCATION_ID_TEMPLE;
    }
    return index;
}


/**
 * @brief Mark a given location as checked
 * @param locationID: The ID of the checked location
 */
static void LocationCheckedCallback(int64_t locationID)
{
    Output::send<LogLevel::Verbose>(TEXT("Checked locationID: {}\n"), locationID);
    int scrapsIndex = getIndexOfLocationID(locationID);
    if (scrapsIndex != -1)
    {
        apData.nbCheckedScrapsByLocation[scrapsIndex] += 1;
    }
}


/**
 * @brief Retains only digits ('0'-'9') and the dot ('.') character from a version string
 * @note Intended to extract version-like strings
 * @param version The string to filter
 *
 * @return The filtered string
 */
static std::string filterVersion(std::string version)
{
    std::string result;
    result.reserve(version.size());

    for (unsigned char c : version)
    {
        if (std::isdigit(c) || c == '.')
            result.push_back(c);
    }

    return result;
}


/**
 * @brief Get the version of the apworld from the slot_data
 * @param version: The version
 */
static void WorldVersionCallback(std::string version)
{
    latestWorldVersion = filterVersion(version);
}


/**
 * @brief Get the TrackSwitches option value from the slot_data
 * @param trackSwitchesValue: The option value
 */
static void TrackSwitchesCallback(int trackSwitchesValue)
{
    Output::send<LogLevel::Verbose>(TEXT("trackSwitchesValue: {}\n"), trackSwitchesValue);
    isAPOptionEnabled[TRACK_SWITCHES_OPTION] = trackSwitchesValue != 0;
}


/**
 * @brief Get the CursedFogs option value from the slot_data
 * @param cursedFogsValue: The option value
 */
static void CursedFogsCallback(int cursedFogsValue)
{
    Output::send<LogLevel::Verbose>(TEXT("cursedFogsValue: {}\n"), cursedFogsValue);
    isAPOptionEnabled[CURSED_FOGS_OPTION] = cursedFogsValue != 0;
}


/**
 * @brief Get the SpeedUpgrade option value from the slot_data
 * @param SpeedUpgradeValue: The option value
 */
static void SpeedUpgradeCallback(int SpeedUpgradeValue)
{
    Output::send<LogLevel::Verbose>(TEXT("SpeedUpgradeValue: {}\n"), SpeedUpgradeValue);
    isAPOptionEnabled[SPEED_UPGRADE_OPTION] = SpeedUpgradeValue != 0;
}


/**
 * @brief Get the DamageUpgrade option value from the slot_data
 * @param DamgeUpgradeValue: The option value
 */
static void DamageUpgradeCallback(int DamgeUpgradeValue)
{
    Output::send<LogLevel::Verbose>(TEXT("DamgeUpgradeValue: {}\n"), DamgeUpgradeValue);
    isAPOptionEnabled[DAMAGE_UPGRADE_OPTION] = DamgeUpgradeValue != 0;
}


/**
 * @brief Get the ArmorUpgrade option value from the slot_data
 * @param ArmorUpgradeValue: The option value
 */
static void ArmorUpgradeCallback(int ArmorUpgradeValue)
{
    Output::send<LogLevel::Verbose>(TEXT("ArmorUpgradeValue: {}\n"), ArmorUpgradeValue);
    isAPOptionEnabled[ARMOR_UPGRADE_OPTION] = ArmorUpgradeValue != 0;
}


/**
 * @brief Get the StartingGun option value from the slot_data
 * @param StartingGunValue: The option value
 */
static void StartingGunCallback(int StartingGunValue)
{
    Output::send<LogLevel::Verbose>(TEXT("StartingGunValue: {}\n"), StartingGunValue);
    isAPOptionEnabled[STARTING_GUN_OPTION] = StartingGunValue;
}


/**
 * @brief Get the information of a scouted location
 * @param NWItem: The information
 */
static void LocationInfoCallback(std::vector<AP_NetworkItem> NWItem)
{
    for (int i = 0; i < MAX_LOCATIONS; i++)
    {
        Output::send<LogLevel::Verbose>(TEXT("NWItem: {} => {}\n"), RC::to_wstring(NWItem[i].locationName).c_str(), RC::to_wstring(NWItem[i].itemName).c_str());
    }
}


void LogFromAPCpp(std::string message) {
    Output::send<LogLevel::Verbose>(TEXT("LogFromAPCpp: {}\n"), RC::to_wstring(message).c_str());
}


namespace APManager {
    void APManager::initializeAPData()
    {
        isAPOptionEnabled.SetNum(NB_AP_OPTIONS);
        for (int i = 0; i < isAPOptionEnabled.Num(); i++)
        {
            isAPOptionEnabled[i] = false;
        }

        apData.allReceivedItems.items.SetNum(27);
        apData.allReceivedItems.items[0].name = FString(to_wstring("05_Scraps").c_str());
        apData.allReceivedItems.items[1].name = FString(to_wstring("Mine1_Key").c_str());
        apData.allReceivedItems.items[2].name = FString(to_wstring("Mine2_Key").c_str());
        apData.allReceivedItems.items[3].name = FString(to_wstring("Mine3_Key").c_str());
        apData.allReceivedItems.items[4].name = FString(to_wstring("01_KeyTony").c_str());
        apData.allReceivedItems.items[5].name = FString(to_wstring("Tutorial2_Key").c_str());
        apData.allReceivedItems.items[6].name = FString(to_wstring("Swamp_Fish").c_str());
        apData.allReceivedItems.items[7].name = FString(to_wstring("Junkyard_LockPicks").c_str());
        apData.allReceivedItems.items[8].name = FString(to_wstring("Junkyard_Tablet").c_str());
        apData.allReceivedItems.items[9].name = FString(to_wstring("Canyon_BlueBox").c_str());
        apData.allReceivedItems.items[10].name = FString(to_wstring("Pages_Drawing").c_str());
        apData.allReceivedItems.items[11].name = FString(to_wstring("Port_Journal").c_str());
        apData.allReceivedItems.items[12].name = FString(to_wstring("Boomer_Dynamite").c_str());
        apData.allReceivedItems.items[13].name = FString(to_wstring("Boomer_Rockets").c_str());
        apData.allReceivedItems.items[14].name = FString(to_wstring("Lighthouse_Breaker").c_str());
        apData.allReceivedItems.items[15].name = FString(to_wstring("Bob_BobPiece").c_str());
        apData.allReceivedItems.items[16].name = FString(to_wstring("Towers_Files").c_str());
        apData.allReceivedItems.items[17].name = FString(to_wstring("Bob_Key").c_str());
        apData.allReceivedItems.items[18].name = FString(to_wstring("Pickles_Jar").c_str());
        apData.allReceivedItems.items[19].name = FString(to_wstring("Mine1_Egg").c_str());
        apData.allReceivedItems.items[20].name = FString(to_wstring("Mine2_Egg").c_str());
        apData.allReceivedItems.items[21].name = FString(to_wstring("Mine3_Egg").c_str());
        apData.allReceivedItems.items[22].name = FString(to_wstring("Bridge_Dynamite").c_str());
        apData.allReceivedItems.items[23].name = FString(to_wstring("Boss_ShrineKey").c_str());
        apData.allReceivedItems.items[24].name = FString(to_wstring("Speed Level").c_str());
        apData.allReceivedItems.items[25].name = FString(to_wstring("Damage Level").c_str());
        apData.allReceivedItems.items[26].name = FString(to_wstring("Armor Level").c_str());
        for (int i = 0; i < apData.allReceivedItems.items.Num(); i++)
        {
            apData.allReceivedItems.items[i].amount = 0;
        }

        const unsigned int MaxTrackSwitch = 8;
        const unsigned int MaxFogbaneRelic = 35;
        const unsigned int MaxUpgradeUnlock = 3;
        apData.allReceivedItems.objects.SetNum(MaxTrackSwitch + MaxFogbaneRelic + MaxUpgradeUnlock);
        apData.allReceivedItems.objects[0].name = FString(to_wstring("Track Switch Pack").c_str());
        apData.allReceivedItems.objects[1].name = FString(to_wstring("Track Switch - Barn or Tutorial").c_str());
        apData.allReceivedItems.objects[2].name = FString(to_wstring("Track Switch - Middle or Port").c_str());
        apData.allReceivedItems.objects[3].name = FString(to_wstring("Track Switch - Haunted or East").c_str());
        apData.allReceivedItems.objects[4].name = FString(to_wstring("Track Switch - North or Temple").c_str());
        apData.allReceivedItems.objects[5].name = FString(to_wstring("Track Switch - Caravan or Cultists").c_str());
        apData.allReceivedItems.objects[6].name = FString(to_wstring("Track Switch - Camp or Elevator").c_str());
        apData.allReceivedItems.objects[7].name = FString(to_wstring("Track Switch - Ruin or Temple").c_str());
        apData.allReceivedItems.objects[8].name = FString(to_wstring("Fogbane Relic Pack").c_str());
        apData.allReceivedItems.objects[9].name = FString(to_wstring("Fogbane Relic - Mine Shaft").c_str());
        apData.allReceivedItems.objects[10].name = FString(to_wstring("Fogbane Relic - Junkyard Area").c_str());
        apData.allReceivedItems.objects[11].name = FString(to_wstring("Fogbane Relic - Junkyard Shed").c_str());
        apData.allReceivedItems.objects[12].name = FString(to_wstring("Fogbane Relic - South House").c_str());
        apData.allReceivedItems.objects[13].name = FString(to_wstring("Fogbane Relic - Military Base").c_str());
        apData.allReceivedItems.objects[14].name = FString(to_wstring("Fogbane Relic - South Mine Outside").c_str());
        apData.allReceivedItems.objects[15].name = FString(to_wstring("Fogbane Relic - Middle Station").c_str());
        apData.allReceivedItems.objects[16].name = FString(to_wstring("Fogbane Relic - Canyon").c_str());
        apData.allReceivedItems.objects[17].name = FString(to_wstring("Fogbane Relic - Watchtower").c_str());
        apData.allReceivedItems.objects[18].name = FString(to_wstring("Fogbane Relic - Haunted House").c_str());
        apData.allReceivedItems.objects[19].name = FString(to_wstring("Fogbane Relic - Santiago House").c_str());
        apData.allReceivedItems.objects[20].name = FString(to_wstring("Fogbane Relic - Port").c_str());
        apData.allReceivedItems.objects[21].name = FString(to_wstring("Fogbane Relic - Doll Woods").c_str());
        apData.allReceivedItems.objects[22].name = FString(to_wstring("Fogbane Relic - East House").c_str());
        apData.allReceivedItems.objects[23].name = FString(to_wstring("Fogbane Relic - Rocket Grounds").c_str());
        apData.allReceivedItems.objects[24].name = FString(to_wstring("Fogbane Relic - Workshop").c_str());
        apData.allReceivedItems.objects[25].name = FString(to_wstring("Fogbane Relic - East Tower").c_str());
        apData.allReceivedItems.objects[26].name = FString(to_wstring("Fogbane Relic - Lighthouse").c_str());
        apData.allReceivedItems.objects[27].name = FString(to_wstring("Fogbane Relic - North Mine Outside").c_str());
        apData.allReceivedItems.objects[28].name = FString(to_wstring("Fogbane Relic - Wood Bridge").c_str());
        apData.allReceivedItems.objects[29].name = FString(to_wstring("Fogbane Relic - Museum").c_str());
        apData.allReceivedItems.objects[30].name = FString(to_wstring("Fogbane Relic - Barbed Shelter").c_str());
        apData.allReceivedItems.objects[31].name = FString(to_wstring("Fogbane Relic - West Beach").c_str());
        apData.allReceivedItems.objects[32].name = FString(to_wstring("Fogbane Relic - Church").c_str());
        apData.allReceivedItems.objects[33].name = FString(to_wstring("Fogbane Relic - West Cottage").c_str());
        apData.allReceivedItems.objects[34].name = FString(to_wstring("Fogbane Relic - Trailer Cabin").c_str());
        apData.allReceivedItems.objects[35].name = FString(to_wstring("Fogbane Relic - Towers").c_str());
        apData.allReceivedItems.objects[36].name = FString(to_wstring("Fogbane Relic - North Beach").c_str());
        apData.allReceivedItems.objects[37].name = FString(to_wstring("Fogbane Relic - Mob Camp").c_str());
        apData.allReceivedItems.objects[38].name = FString(to_wstring("Fogbane Relic - Mine Elevator Exit").c_str());
        apData.allReceivedItems.objects[39].name = FString(to_wstring("Fogbane Relic - Mountain Ruin Outside").c_str());
        apData.allReceivedItems.objects[40].name = FString(to_wstring("Fogbane Relic - Temple").c_str());
        apData.allReceivedItems.objects[41].name = FString(to_wstring("Fogbane Relic - Pickle Val").c_str());
        apData.allReceivedItems.objects[42].name = FString(to_wstring("Fogbane Relic - Morse Bunker").c_str());
        apData.allReceivedItems.objects[43].name = FString(to_wstring("Speed Unlock").c_str());
        apData.allReceivedItems.objects[44].name = FString(to_wstring("Damage Unlock").c_str());
        apData.allReceivedItems.objects[45].name = FString(to_wstring("Armor Unlock").c_str());
        for (int i = 0; i < apData.allReceivedItems.objects.Num(); i++)
        {
            apData.allReceivedItems.objects[i].amount = 0;
        }

        apData.allReceivedItems.paintCans.SetNum(11);
        apData.allReceivedItems.paintCans[0].name = FString(to_wstring("Orange Paint Can").c_str());
        apData.allReceivedItems.paintCans[1].name = FString(to_wstring("Green Paint Can").c_str());
        apData.allReceivedItems.paintCans[2].name = FString(to_wstring("White Paint Can").c_str());
        apData.allReceivedItems.paintCans[3].name = FString(to_wstring("Pink Paint Can").c_str());
        apData.allReceivedItems.paintCans[4].name = FString(to_wstring("Gray Paint Can").c_str());
        apData.allReceivedItems.paintCans[5].name = FString(to_wstring("Blue Paint Can").c_str());
        apData.allReceivedItems.paintCans[6].name = FString(to_wstring("Black Paint Can").c_str());
        apData.allReceivedItems.paintCans[7].name = FString(to_wstring("Lime Paint Can").c_str());
        apData.allReceivedItems.paintCans[8].name = FString(to_wstring("Teal Paint Can").c_str());
        apData.allReceivedItems.paintCans[9].name = FString(to_wstring("Red Paint Can").c_str());
        apData.allReceivedItems.paintCans[10].name = FString(to_wstring("Purple Paint Can").c_str());
        for (int i = 0; i < apData.allReceivedItems.paintCans.Num(); i++)
        {
            apData.allReceivedItems.paintCans[i].unlocked = false;
        }

        apData.allReceivedItems.guns.SetNum(4);
        apData.allReceivedItems.guns[0].name = FString(to_wstring("Rocket Launcher").c_str()); // The Boomer
        apData.allReceivedItems.guns[1].name = FString(to_wstring("Range Gun").c_str()); // Bob
        apData.allReceivedItems.guns[2].name = FString(to_wstring("Flamethrower").c_str()); // Bug Spray
        apData.allReceivedItems.guns[3].name = FString(to_wstring("Machine Gun").c_str()); // Derailer
        for (int i = 0; i < apData.allReceivedItems.guns.Num(); i++)
        {
            apData.allReceivedItems.guns[i].unlocked = 0;
        }

        // Set the number of checked scraps locations to 0, it will increment by LocationCheckedCallback()
        apData.nbCheckedScrapsByLocation.SetNum(NB_LOCATIONS_WITH_SCRAPS);
        for (int i = 0; i < NB_LOCATIONS_WITH_SCRAPS; i++)
        {
            apData.nbCheckedScrapsByLocation[i] = 0;
        }
    }

    void APManager::Setup_AP(const char* ipAddress, const char* playerName, const char* password)
    {
        AP_Init(ipAddress, "Choo-Choo Charles", playerName, password);
        AP_SetItemClearCallback(ClearInventoryCallback);
        AP_SetItemRecvCallback(ItemReceivedCallback);
        AP_SetLocationCheckedCallback(LocationCheckedCallback);
        AP_RegisterSlotDataRawCallback("world_version", &WorldVersionCallback);
        AP_RegisterSlotDataIntCallback("TrackSwitches", &TrackSwitchesCallback);
        AP_RegisterSlotDataIntCallback("CursedFogs", &CursedFogsCallback);
        AP_RegisterSlotDataIntCallback("SpeedUpgrade", &SpeedUpgradeCallback);
        AP_RegisterSlotDataIntCallback("DamageUpgrade", &DamageUpgradeCallback);
        AP_RegisterSlotDataIntCallback("ArmorUpgrade", &ArmorUpgradeCallback);
        AP_RegisterSlotDataIntCallback("StartingGun", &StartingGunCallback);
        AP_SetLocationInfoCallback(&LocationInfoCallback);
        AP_SetDeathLinkSupported(true);
        AP_Start();
    }

    void APManager::ResetItemAmounts()
    {
        for (int32_t index = 0; index < apData.allReceivedItems.items.Num(); index++)
        {
            apData.allReceivedItems.items[index].amount = 0;
        }
        for (int32_t index = 0; index < apData.allReceivedItems.objects.Num(); index++)
        {
            apData.allReceivedItems.objects[index].amount = 0;
        }
        for (int32_t index = 0; index < apData.allReceivedItems.paintCans.Num(); index++)
        {
            apData.allReceivedItems.paintCans[index].unlocked = false;
        }
        for (int32_t index = 0; index < apData.allReceivedItems.guns.Num(); index++)
        {
            apData.allReceivedItems.guns[index].unlocked = false;
        }

        apData.pendingItemIDs.Empty();
    }

    void APManager::Disconnect()
    {
        APManager::ResetItemAmounts();
        AP_Shutdown();
    }

    void APManager::UpdateConnectionStatus()
    {
        // Check the connection status changed
        if (!apData.authenticated && AP_GetConnectionStatus() == AP_ConnectionStatus::Authenticated
            || apData.authenticated && AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
        {
            apData.authenticated = !apData.authenticated;

            if (!apData.authenticated)
            {
                apData.statusMessage = FString(RC::to_wstring("Offline").c_str());
                for (int i = 0; i < NB_LOCATIONS_WITH_SCRAPS; i++)
                {
                    apData.nbCheckedScrapsByLocation[i] = 0;
                }
            }
            else if (CURRENT_WORLD_VERSION == latestWorldVersion)
            {
                apData.statusMessage = FString(RC::to_wstring("Connected").c_str());
                // Scout all locations at each connection
                std::set<int64_t> locations;
                for (int i = START_LOCATION_ID; i <= LAST_LOCATION_ID; i++)
                {
                    locations.insert(i);
                }
                AP_SendLocationScouts(locations, false);
            }
            else
            {
                apData.statusMessage = FString(RC::to_wstring(
                    "Mod update required\nv" + CURRENT_WORLD_VERSION + " -> v" + latestWorldVersion
                ).c_str());
            }
        }
    }

    void APManager::CheckDeathLink()
    {
        if (AP_DeathLinkPending())
        {
            apData.pendingDeathLink = true;
        }
    }

    void APManager::CleanAPData()
    {
        // TODO: Cleanup old content from "apData" variable
        if (apData.pendingItemIDs.Num() > 0)
        {
            apData.pendingItemIDs.Empty();
        }
        AP_DeathLinkClear();
        if (apData.pendingDeathLink)
        {
            apData.pendingDeathLink = false;
        }
    }

    void APManager::SendAPLocation(int64_t locationID)
    {
        // If the Archipelago connection is not established yet, exit early
        if (AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
        {
            Output::send<LogLevel::Verbose>(STR("The player is not authenticated\n"));
            return;
        }

        // If the ID is -1, no item was found, exit early
        if (locationID == -1)
        {
            Output::send<LogLevel::Error>(STR("Item not found: locationID == -1\n"));
            return;
        }

        AP_SendItem(locationID);
    }

    void APManager::Victory()
    {
        // If the Archipelago connection is not established yet, exit early
        if (AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
        {
            Output::send<LogLevel::Verbose>(STR("The player is not authenticated\n"));
            return;
        }

        AP_StoryComplete();
    }
}
