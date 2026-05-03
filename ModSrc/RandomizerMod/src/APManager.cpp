
#include <Unreal/UObject.hpp>
#include <cstring>
#include <Windows.h>

#include "Archipelago.h"
#include "APManager.hpp"
#include "Helpers/String.hpp"


using namespace std;
using namespace RC;
using namespace RC::Unreal;


APInformation information;
TArray<bool> isAPOptionEnabled;


/**
*   @brief Clear all the collected items from the player's inventory
*   @notimplemented Used by AP_SetItemClearCallback but is not necessary
*/
static void ClearInventoryCallback()
{

}


/**
*   @brief Receive an item from any world
*   @param itemID: The ID of the received item
*   @param notifyPlayer: Id true, notify the player about the received item, false otherwise
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
        information.receivedItems.items[0].amount += 1; // No cap for scraps
        break;
    case 2: // Scraps (reward 30)
        information.receivedItems.items[0].amount += 30; // No cap for scraps
        break;
    case 3: // Scraps (reward 25)
        information.receivedItems.items[0].amount += 25; // No cap for scraps
        break;
    case 4: // Scraps (reward 35)
        information.receivedItems.items[0].amount += 35; // No cap for scraps
        break;
    case 5: // Scraps (reward 40)
        information.receivedItems.items[0].amount += 40; // No cap for scraps
        break;
    case 6: // South mine key
        information.receivedItems.items[1].amount < 1 ? information.receivedItems.items[1].amount += 1 : cappedAmount = 0;
        break;
    case 7: // North mine key
        information.receivedItems.items[2].amount < 1 ? information.receivedItems.items[2].amount += 1 : cappedAmount = 0;
        break;
    case 8: // Mountain ruin key
        information.receivedItems.items[3].amount < 1 ? information.receivedItems.items[3].amount += 1 : cappedAmount = 0;
        break;
    case 9: // Barn key
        information.receivedItems.items[4].amount < 1 ? information.receivedItems.items[4].amount += 1 : cappedAmount = 0;
        break;
    case 10: // Candice key
        information.receivedItems.items[5].amount < 1 ? information.receivedItems.items[5].amount += 1 : cappedAmount = 0;
        break;
    case 11: // Dead fish
        information.receivedItems.items[6].amount < 1 ? information.receivedItems.items[6].amount += 1 : cappedAmount = 0;
        break;
    case 12: // Lockpicks
        information.receivedItems.items[7].amount < 1 ? information.receivedItems.items[7].amount += 1 : cappedAmount = 0;
        break;
    case 13: // Ancient tablet
        information.receivedItems.items[8].amount < 1 ? information.receivedItems.items[8].amount += 1 : cappedAmount = 0;
        break;
    case 14: // Blue box
        information.receivedItems.items[9].amount < 1 ? information.receivedItems.items[9].amount += 1 : cappedAmount = 0;
        break;
    case 15: // Page Drawing
        information.receivedItems.items[10].amount < 8 ? information.receivedItems.items[10].amount += 1 : cappedAmount = 0;
        break;
    case 16: // Journal
        information.receivedItems.items[11].amount < 1 ? information.receivedItems.items[11].amount += 1 : cappedAmount = 0;
        break;
    case 17: // Dynamite
        information.receivedItems.items[12].amount < 1 ? information.receivedItems.items[12].amount += 1 : cappedAmount = 0;
        break;
    case 18: // Boomer rockets
        information.receivedItems.items[13].amount < 1 ? information.receivedItems.items[13].amount += 1 : cappedAmount = 0;
        break;
    case 19: // Breaker
        information.receivedItems.items[14].amount < 4 ? information.receivedItems.items[14].amount += 1 : cappedAmount = 0;
        break;
    case 20: // Broken Bob
        information.receivedItems.items[15].amount < 1 ? information.receivedItems.items[15].amount += 1 : cappedAmount = 0;
        break;
    case 21: // Employment contracts
        information.receivedItems.items[16].amount < 1 ? information.receivedItems.items[16].amount += 1 : cappedAmount = 0;
        break;
    case 22: // Mob camp key
        information.receivedItems.items[17].amount < 1 ? information.receivedItems.items[17].amount += 1 : cappedAmount = 0;
        break;
    case 23: // Pickles jar
        information.receivedItems.items[18].amount < 1 ? information.receivedItems.items[18].amount += 1 : cappedAmount = 0;
        break;
    case 24: // Orange Paint Can
        information.receivedItems.paintCans[0].unlocked == false ? information.receivedItems.paintCans[0].unlocked = true : cappedAmount = 0;
        break;
    case 25: // Green Paint Can
        information.receivedItems.paintCans[1].unlocked == false ? information.receivedItems.paintCans[1].unlocked = true : cappedAmount = 0;
        break;
    case 26: // White Paint Can
        information.receivedItems.paintCans[2].unlocked == false ? information.receivedItems.paintCans[2].unlocked = true : cappedAmount = 0;
        break;
    case 27: // Pink Paint Can
        information.receivedItems.paintCans[3].unlocked == false ? information.receivedItems.paintCans[3].unlocked = true : cappedAmount = 0;
        break;
    case 28: // Gray Paint Can
        information.receivedItems.paintCans[4].unlocked == false ? information.receivedItems.paintCans[4].unlocked = true : cappedAmount = 0;
        break;
    case 29: // Blue Paint Can
        information.receivedItems.paintCans[5].unlocked == false ? information.receivedItems.paintCans[5].unlocked = true : cappedAmount = 0;
        break;
    case 30: // Black Paint Can
        information.receivedItems.paintCans[6].unlocked == false ? information.receivedItems.paintCans[6].unlocked = true : cappedAmount = 0;
        break;
    case 31: // Lime Paint Can
        information.receivedItems.paintCans[7].unlocked == false ? information.receivedItems.paintCans[7].unlocked = true : cappedAmount = 0;
        break;
    case 32: // Teal Paint Can
        information.receivedItems.paintCans[8].unlocked == false ? information.receivedItems.paintCans[8].unlocked = true : cappedAmount = 0;
        break;
    case 33: // Red Paint Can
        information.receivedItems.paintCans[9].unlocked == false ? information.receivedItems.paintCans[9].unlocked = true : cappedAmount = 0;
        break;
    case 34: // Purple Paint Can
        information.receivedItems.paintCans[10].unlocked == false ? information.receivedItems.paintCans[10].unlocked = true : cappedAmount = 0;
        break;
    case 35: // The Boomer
        information.receivedItems.weapons[0].unlocked == false ? information.receivedItems.weapons[0].unlocked = true : cappedAmount = 0;
        break;
    case 36: // Bob
        information.receivedItems.weapons[1].unlocked == false ? information.receivedItems.weapons[1].unlocked = true : cappedAmount = 0;
        break;
    case 37: // Green egg
        information.receivedItems.items[19].amount < 1 ? information.receivedItems.items[19].amount += 1 : cappedAmount = 0;
        break;
    case 38: // Blue egg
        information.receivedItems.items[20].amount < 1 ? information.receivedItems.items[20].amount += 1 : cappedAmount = 0;
        break;
    case 39: // Red egg
        information.receivedItems.items[21].amount < 1 ? information.receivedItems.items[21].amount += 1 : cappedAmount = 0;
        break;
    case 40: // Remote explosives
        information.receivedItems.items[22].amount < 8 ? information.receivedItems.items[22].amount += 1 : cappedAmount = 0;
        break;
    case 41: // Remote explosives (x8)
        amountToAdd = 8;
        itemID = BASE_ID + 40; // Change id to "Remote explosives" to add it cappedAmount times
        cappedAmount = (information.receivedItems.items[22].amount + amountToAdd <= 8) ? amountToAdd : 8 - information.receivedItems.items[22].amount;
        information.receivedItems.items[22].amount += cappedAmount;
        break;
    case 42: // Temple key
        information.receivedItems.items[23].amount < 1 ? information.receivedItems.items[23].amount += 1 : cappedAmount = 0;
        break;
    case 43: // Bug Spray
        information.receivedItems.weapons[2].unlocked == false ? information.receivedItems.weapons[2].unlocked = true : cappedAmount = 0;
        break;
    case 44 : // Track Switch Pack
        information.receivedItems.objects[0].amount < 1 ? information.receivedItems.objects[0].amount += 1 : cappedAmount = 0;
        break;
    case 45: // Track Switch - Barn or Tutorial
        information.receivedItems.objects[1].amount < 1 ? information.receivedItems.objects[1].amount += 1 : cappedAmount = 0;
        break;
    case 46: // Track Switch - Middle or Port
        information.receivedItems.objects[2].amount < 1 ? information.receivedItems.objects[2].amount += 1 : cappedAmount = 0;
        break;
    case 47: // Track Switch - Haunted or East
        information.receivedItems.objects[3].amount < 1 ? information.receivedItems.objects[3].amount += 1 : cappedAmount = 0;
        break;
    case 48: // Track Switch - North or Temple
        information.receivedItems.objects[4].amount < 1 ? information.receivedItems.objects[4].amount += 1 : cappedAmount = 0;
        break;
    case 49: // Track Switch - Caravan or Cultists
        information.receivedItems.objects[5].amount < 1 ? information.receivedItems.objects[5].amount += 1 : cappedAmount = 0;
        break;
    case 50: // Track Switch - Camp or Elevator
        information.receivedItems.objects[6].amount < 1 ? information.receivedItems.objects[6].amount += 1 : cappedAmount = 0;
        break;
    case 51: // Track Switch - Ruin or Temple
        information.receivedItems.objects[7].amount < 1 ? information.receivedItems.objects[7].amount += 1 : cappedAmount = 0;
        break;
    case 52: // Fogbane Relic Pack
        information.receivedItems.objects[8].amount < 1 ? information.receivedItems.objects[8].amount += 1 : cappedAmount = 0;
        break;
    case 53: // Fogbane Relic - Mine Shaft
        information.receivedItems.objects[9].amount < 1 ? information.receivedItems.objects[9].amount += 1 : cappedAmount = 0;
        break;
    case 54: // Fogbane Relic - Junkyard Area
        information.receivedItems.objects[10].amount < 1 ? information.receivedItems.objects[10].amount += 1 : cappedAmount = 0;
        break;
    case 55: // Fogbane Relic - Junkyard Shed
        information.receivedItems.objects[11].amount < 1 ? information.receivedItems.objects[11].amount += 1 : cappedAmount = 0;
        break;
    case 56: // Fogbane Relic - South House
        information.receivedItems.objects[12].amount < 1 ? information.receivedItems.objects[12].amount += 1 : cappedAmount = 0;
        break;
    case 57: // Fogbane Relic - Military Base
        information.receivedItems.objects[13].amount < 1 ? information.receivedItems.objects[13].amount += 1 : cappedAmount = 0;
        break;
    case 58: // Fogbane Relic - South Mine Outside
        information.receivedItems.objects[14].amount < 1 ? information.receivedItems.objects[14].amount += 1 : cappedAmount = 0;
        break;
    case 59: // Fogbane Relic - Middle Station
        information.receivedItems.objects[15].amount < 1 ? information.receivedItems.objects[15].amount += 1 : cappedAmount = 0;
        break;
    case 60: // Fogbane Relic - Canyon
        information.receivedItems.objects[16].amount < 1 ? information.receivedItems.objects[16].amount += 1 : cappedAmount = 0;
        break;
    case 61: // Fogbane Relic - Watchtower
        information.receivedItems.objects[17].amount < 1 ? information.receivedItems.objects[17].amount += 1 : cappedAmount = 0;
        break;
    case 62: // Fogbane Relic - Haunted House
        information.receivedItems.objects[18].amount < 1 ? information.receivedItems.objects[18].amount += 1 : cappedAmount = 0;
        break;
    case 63: // Fogbane Relic - Santiago House
        information.receivedItems.objects[19].amount < 1 ? information.receivedItems.objects[19].amount += 1 : cappedAmount = 0;
        break;
    case 64: // Fogbane Relic - Port
        information.receivedItems.objects[20].amount < 1 ? information.receivedItems.objects[20].amount += 1 : cappedAmount = 0;
        break;
    case 65: // Fogbane Relic - Doll Woods
        information.receivedItems.objects[21].amount < 1 ? information.receivedItems.objects[21].amount += 1 : cappedAmount = 0;
        break;
    case 66: // Fogbane Relic - East House
        information.receivedItems.objects[22].amount < 1 ? information.receivedItems.objects[22].amount += 1 : cappedAmount = 0;
        break;
    case 67: // Fogbane Relic - Rocket Grounds
        information.receivedItems.objects[23].amount < 1 ? information.receivedItems.objects[23].amount += 1 : cappedAmount = 0;
        break;
    case 68: // Fogbane Relic - Workshop
        information.receivedItems.objects[24].amount < 1 ? information.receivedItems.objects[24].amount += 1 : cappedAmount = 0;
        break;
    case 69: // Fogbane Relic - East Tower
        information.receivedItems.objects[25].amount < 1 ? information.receivedItems.objects[25].amount += 1 : cappedAmount = 0;
        break;
    case 70: // Fogbane Relic - Lighthouse
        information.receivedItems.objects[26].amount < 1 ? information.receivedItems.objects[26].amount += 1 : cappedAmount = 0;
        break;
    case 71: // Fogbane Relic - North Mine Outside
        information.receivedItems.objects[27].amount < 1 ? information.receivedItems.objects[27].amount += 1 : cappedAmount = 0;
        break;
    case 72: // Fogbane Relic - Wood Bridge
        information.receivedItems.objects[28].amount < 1 ? information.receivedItems.objects[28].amount += 1 : cappedAmount = 0;
        break;
    case 73: // Fogbane Relic - Museum
        information.receivedItems.objects[29].amount < 1 ? information.receivedItems.objects[29].amount += 1 : cappedAmount = 0;
        break;
    case 74: // Fogbane Relic - Barbed Shelter
        information.receivedItems.objects[30].amount < 1 ? information.receivedItems.objects[30].amount += 1 : cappedAmount = 0;
        break;
    case 75: // Fogbane Relic - West Beach
        information.receivedItems.objects[31].amount < 1 ? information.receivedItems.objects[31].amount += 1 : cappedAmount = 0;
        break;
    case 76: // Fogbane Relic - Church
        information.receivedItems.objects[32].amount < 1 ? information.receivedItems.objects[32].amount += 1 : cappedAmount = 0;
        break;
    case 77: // Fogbane Relic - West Cottage
        information.receivedItems.objects[33].amount < 1 ? information.receivedItems.objects[33].amount += 1 : cappedAmount = 0;
        break;
    case 78: // Fogbane Relic - Trailer Cabin
        information.receivedItems.objects[34].amount < 1 ? information.receivedItems.objects[34].amount += 1 : cappedAmount = 0;
        break;
    case 79: // Fogbane Relic - Towers
        information.receivedItems.objects[35].amount < 1 ? information.receivedItems.objects[35].amount += 1 : cappedAmount = 0;
        break;
    case 80: // Fogbane Relic - North Beach
        information.receivedItems.objects[36].amount < 1 ? information.receivedItems.objects[36].amount += 1 : cappedAmount = 0;
        break;
    case 81: // Fogbane Relic - Mob Camp
        information.receivedItems.objects[37].amount < 1 ? information.receivedItems.objects[37].amount += 1 : cappedAmount = 0;
        break;
    case 82: // Fogbane Relic - Mine Elevator Exit
        information.receivedItems.objects[38].amount < 1 ? information.receivedItems.objects[38].amount += 1 : cappedAmount = 0;
        break;
    case 83: // Fogbane Relic - Mountain Ruin Outside
        information.receivedItems.objects[39].amount < 1 ? information.receivedItems.objects[39].amount += 1 : cappedAmount = 0;
        break;
    case 84: // Fogbane Relic - Temple
        information.receivedItems.objects[40].amount < 1 ? information.receivedItems.objects[40].amount += 1 : cappedAmount = 0;
        break;
    case 85: // Fogbane Relic - Pickle Val
        information.receivedItems.objects[41].amount < 1 ? information.receivedItems.objects[41].amount += 1 : cappedAmount = 0;
        break;
    case 86: // Fogbane Relic - Morse Bunker
        information.receivedItems.objects[42].amount < 1 ? information.receivedItems.objects[42].amount += 1 : cappedAmount = 0;
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
            information.pendingItemIDs.Emplace(itemID);
        }
    }
}


/**
*   @brief Mark a given location as checked
*   @param locationID: The ID of the checked location
*   @notimplemented Used by AP_SetItemClearCallback but is not necessary
*/
static void LocationCheckedCallback(int64_t locationID)
{
    
}


/**
 * @brief Retains only digits ('0'-'9') and the dot ('.') character from a version string
 * @note Intended to extract version-like strings
 * @param version The string to filter
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
*   @brief Get the version of the apworld from the slot_data
*   @param version: The version
*/
static void WorldVersionCallback(std::string version)
{
    latestWorldVersion = filterVersion(version);
}


/**
*   @brief Get the TrackSwitches option value from the slot_data
*   @param trackSwitchesValue: The option value
*/
static void TrackSwitchesCallback(int trackSwitchesValue)
{
    Output::send<LogLevel::Verbose>(TEXT("trackSwitchesValue: {}\n"), trackSwitchesValue);
    isAPOptionEnabled[TRACK_SWITCHES_OPTION] = trackSwitchesValue != 0;
}


/**
*   @brief Get the CursedFogs option value from the slot_data
*   @param cursedFogsValue: The option value
*/
static void CursedFogsCallback(int cursedFogsValue)
{
    Output::send<LogLevel::Verbose>(TEXT("cursedFogsValue: {}\n"), cursedFogsValue);
    isAPOptionEnabled[CURSED_FOGS_OPTION] = cursedFogsValue != 0;
}


/**
*   @brief Log used to check APCpp messages
*   @param message: The message to log
*   @note Prints functions in APCpp code must be manually replaced by calls of this function
*/
void LogFromAPCpp(std::string message) {
    Output::send<LogLevel::Verbose>(TEXT("LogFromAPCpp: {}\n"), RC::to_wstring(message).c_str());
}


namespace APManager {

    APManager::setup_AP(const char* ipAddress, const char* playerName, const char* password)
    {
        AP_Init(ipAddress, "Choo-Choo Charles", playerName, password);
        AP_SetItemClearCallback(ClearInventoryCallback);
        AP_SetItemRecvCallback(ItemReceivedCallback);
        AP_SetLocationCheckedCallback(LocationCheckedCallback);
        AP_RegisterSlotDataRawCallback("world_version", &WorldVersionCallback);
        AP_RegisterSlotDataIntCallback("TrackSwitches", &TrackSwitchesCallback);
        AP_RegisterSlotDataIntCallback("CursedFogs", &CursedFogsCallback);
        AP_SetDeathLinkSupported(true);
        AP_Start();
    }

    /**
    *   @brief Initialize AP information
    */
    void APManager::initializeAPInformation()
    {
        isAPOptionEnabled.SetNum(NB_AP_OPTIONS);
        for (int i = 0; i < isAPOptionEnabled.Num(); i++)
        {
            isAPOptionEnabled[i] = false;
        }

        information.receivedItems.items.SetNum(24);
        information.receivedItems.items[0].name = FString(to_wstring("05_Scraps").c_str());
        information.receivedItems.items[1].name = FString(to_wstring("Mine1_Key").c_str());
        information.receivedItems.items[2].name = FString(to_wstring("Mine2_Key").c_str());
        information.receivedItems.items[3].name = FString(to_wstring("Mine3_Key").c_str());
        information.receivedItems.items[4].name = FString(to_wstring("01_KeyTony").c_str());
        information.receivedItems.items[5].name = FString(to_wstring("Tutorial2_Key").c_str());
        information.receivedItems.items[6].name = FString(to_wstring("Swamp_Fish").c_str());
        information.receivedItems.items[7].name = FString(to_wstring("Junkyard_LockPicks").c_str());
        information.receivedItems.items[8].name = FString(to_wstring("Junkyard_Tablet").c_str());
        information.receivedItems.items[9].name = FString(to_wstring("Canyon_BlueBox").c_str());
        information.receivedItems.items[10].name = FString(to_wstring("Pages_Drawing").c_str());
        information.receivedItems.items[11].name = FString(to_wstring("Port_Journal").c_str());
        information.receivedItems.items[12].name = FString(to_wstring("Boomer_Dynamite").c_str());
        information.receivedItems.items[13].name = FString(to_wstring("Boomer_Rockets").c_str());
        information.receivedItems.items[14].name = FString(to_wstring("Lighthouse_Breaker").c_str());
        information.receivedItems.items[15].name = FString(to_wstring("Bob_BobPiece").c_str());
        information.receivedItems.items[16].name = FString(to_wstring("Towers_Files").c_str());
        information.receivedItems.items[17].name = FString(to_wstring("Bob_Key").c_str());
        information.receivedItems.items[18].name = FString(to_wstring("Pickles_Jar").c_str());
        information.receivedItems.items[19].name = FString(to_wstring("Mine1_Egg").c_str());
        information.receivedItems.items[20].name = FString(to_wstring("Mine2_Egg").c_str());
        information.receivedItems.items[21].name = FString(to_wstring("Mine3_Egg").c_str());
        information.receivedItems.items[22].name = FString(to_wstring("Bridge_Dynamite").c_str());
        information.receivedItems.items[23].name = FString(to_wstring("Boss_ShrineKey").c_str());
        for (int i = 0; i < information.receivedItems.items.Num(); i++)
        {
            information.receivedItems.items[i].amount = 0;
        }

        const unsigned int MaxTrackSwitch = 8;
        const unsigned int MaxFogbaneRelic = 35;
        information.receivedItems.objects.SetNum(MaxTrackSwitch + MaxFogbaneRelic);
        information.receivedItems.objects[0].name = FString(to_wstring("Track Switch Pack").c_str());
        information.receivedItems.objects[1].name = FString(to_wstring("Track Switch - Barn or Tutorial").c_str());
        information.receivedItems.objects[2].name = FString(to_wstring("Track Switch - Middle or Port").c_str());
        information.receivedItems.objects[3].name = FString(to_wstring("Track Switch - Haunted or East").c_str());
        information.receivedItems.objects[4].name = FString(to_wstring("Track Switch - North or Temple").c_str());
        information.receivedItems.objects[5].name = FString(to_wstring("Track Switch - Caravan or Cultists").c_str());
        information.receivedItems.objects[6].name = FString(to_wstring("Track Switch - Camp or Elevator").c_str());
        information.receivedItems.objects[7].name = FString(to_wstring("Track Switch - Ruin or Temple").c_str());
        information.receivedItems.objects[8].name = FString(to_wstring("Fogbane Relic Pack").c_str());
        information.receivedItems.objects[9].name = FString(to_wstring("Fogbane Relic - Mine Shaft").c_str());
        information.receivedItems.objects[10].name = FString(to_wstring("Fogbane Relic - Junkyard Area").c_str());
        information.receivedItems.objects[11].name = FString(to_wstring("Fogbane Relic - Junkyard Shed").c_str());
        information.receivedItems.objects[12].name = FString(to_wstring("Fogbane Relic - South House").c_str());
        information.receivedItems.objects[13].name = FString(to_wstring("Fogbane Relic - Military Base").c_str());
        information.receivedItems.objects[14].name = FString(to_wstring("Fogbane Relic - South Mine Outside").c_str());
        information.receivedItems.objects[15].name = FString(to_wstring("Fogbane Relic - Middle Station").c_str());
        information.receivedItems.objects[16].name = FString(to_wstring("Fogbane Relic - Canyon").c_str());
        information.receivedItems.objects[17].name = FString(to_wstring("Fogbane Relic - Watchtower").c_str());
        information.receivedItems.objects[18].name = FString(to_wstring("Fogbane Relic - Haunted House").c_str());
        information.receivedItems.objects[19].name = FString(to_wstring("Fogbane Relic - Santiago House").c_str());
        information.receivedItems.objects[20].name = FString(to_wstring("Fogbane Relic - Port").c_str());
        information.receivedItems.objects[21].name = FString(to_wstring("Fogbane Relic - Doll Woods").c_str());
        information.receivedItems.objects[22].name = FString(to_wstring("Fogbane Relic - East House").c_str());
        information.receivedItems.objects[23].name = FString(to_wstring("Fogbane Relic - Rocket Grounds").c_str());
        information.receivedItems.objects[24].name = FString(to_wstring("Fogbane Relic - Workshop").c_str());
        information.receivedItems.objects[25].name = FString(to_wstring("Fogbane Relic - East Tower").c_str());
        information.receivedItems.objects[26].name = FString(to_wstring("Fogbane Relic - Lighthouse").c_str());
        information.receivedItems.objects[27].name = FString(to_wstring("Fogbane Relic - North Mine Outside").c_str());
        information.receivedItems.objects[28].name = FString(to_wstring("Fogbane Relic - Wood Bridge").c_str());
        information.receivedItems.objects[29].name = FString(to_wstring("Fogbane Relic - Museum").c_str());
        information.receivedItems.objects[30].name = FString(to_wstring("Fogbane Relic - Barbed Shelter").c_str());
        information.receivedItems.objects[31].name = FString(to_wstring("Fogbane Relic - West Beach").c_str());
        information.receivedItems.objects[32].name = FString(to_wstring("Fogbane Relic - Church").c_str());
        information.receivedItems.objects[33].name = FString(to_wstring("Fogbane Relic - West Cottage").c_str());
        information.receivedItems.objects[34].name = FString(to_wstring("Fogbane Relic - Trailer Cabin").c_str());
        information.receivedItems.objects[35].name = FString(to_wstring("Fogbane Relic - Towers").c_str());
        information.receivedItems.objects[36].name = FString(to_wstring("Fogbane Relic - North Beach").c_str());
        information.receivedItems.objects[37].name = FString(to_wstring("Fogbane Relic - Mob Camp").c_str());
        information.receivedItems.objects[38].name = FString(to_wstring("Fogbane Relic - Mine Elevator Exit").c_str());
        information.receivedItems.objects[39].name = FString(to_wstring("Fogbane Relic - Mountain Ruin Outside").c_str());
        information.receivedItems.objects[40].name = FString(to_wstring("Fogbane Relic - Temple").c_str());
        information.receivedItems.objects[41].name = FString(to_wstring("Fogbane Relic - Pickle Val").c_str());
        information.receivedItems.objects[42].name = FString(to_wstring("Fogbane Relic - Morse Bunker").c_str());
        for (int i = 0; i < information.receivedItems.objects.Num(); i++)
        {
            information.receivedItems.objects[i].amount = 0;
        }

        information.receivedItems.paintCans.SetNum(11);
        information.receivedItems.paintCans[0].name = FString(to_wstring("Orange Paint Can").c_str());
        information.receivedItems.paintCans[1].name = FString(to_wstring("Green Paint Can").c_str());
        information.receivedItems.paintCans[2].name = FString(to_wstring("White Paint Can").c_str());
        information.receivedItems.paintCans[3].name = FString(to_wstring("Pink Paint Can").c_str());
        information.receivedItems.paintCans[4].name = FString(to_wstring("Gray Paint Can").c_str());
        information.receivedItems.paintCans[5].name = FString(to_wstring("Blue Paint Can").c_str());
        information.receivedItems.paintCans[6].name = FString(to_wstring("Black Paint Can").c_str());
        information.receivedItems.paintCans[7].name = FString(to_wstring("Lime Paint Can").c_str());
        information.receivedItems.paintCans[8].name = FString(to_wstring("Teal Paint Can").c_str());
        information.receivedItems.paintCans[9].name = FString(to_wstring("Red Paint Can").c_str());
        information.receivedItems.paintCans[10].name = FString(to_wstring("Purple Paint Can").c_str());
        for (int i = 0; i < information.receivedItems.paintCans.Num(); i++)
        {
            information.receivedItems.paintCans[i].unlocked = false;
        }

        information.receivedItems.weapons.SetNum(3);
        information.receivedItems.weapons[0].name = FString(to_wstring("The Boomer").c_str());
        information.receivedItems.weapons[1].name = FString(to_wstring("Bob").c_str());
        information.receivedItems.weapons[2].name = FString(to_wstring("Bug Spray").c_str());
        for (int i = 0; i < receivedItems.weapons.Num(); i++)
        {
            information.receivedItems.weapons[i].unlocked = false;
        }
    }

    /**
    *   @brief Reset all received items amounts and all unlocked train components to 0
    */
    void APManager::ResetItemAmounts()
    {
        for (int32_t index = 0; index != information.receivedItems.items.Num(); index++)
        {
            information.receivedItems.items[index].amount = 0;
        }
        for (int32_t index = 0; index != information.receivedItems.paintCans.Num(); index++)
        {
            information.receivedItems.paintCans[index].unlocked = false;
        }
        for (int32_t index = 0; index != information.receivedItems.weapons.Num(); index++)
        {
            information.receivedItems.weapons[index].unlocked = false;
        }

        pendingItemIDs.Empty();
    }

    void APManager::Disconnect()
    {
        APManager::ResetItemAmounts();
        AP_Shutdown();
    }

    /**
    *   @brief Check if the player is authenticated or not
    */
    void APManager::GetConnectionStatus()
    {
        // Check the connection status changed
        if (!information.authenticated && AP_GetConnectionStatus() == AP_ConnectionStatus::Authenticated
            || information.authenticated && AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
        {
            information.authenticated = !information.authenticated;

            if (!information.authenticated)
            {
                information.statusMessage = FString(RC::to_wstring("Offline").c_str());
            }
            else if (CURRENT_WORLD_VERSION == latestWorldVersion)
            {
                information.statusMessage = FString(RC::to_wstring("Connected").c_str());
            }
            else
            {
                information.statusMessage = FString(RC::to_wstring(
                    "Mod update required\nv" + CURRENT_WORLD_VERSION + " -> v" + latestWorldVersion
                ).c_str());
            }
        }
    }

    /**
    *   @brief Check a Deathlink was received
    */
    void APManager::CheckDeathLink()
    {
        if (AP_DeathLinkPending())
        {
            information.pendingDeathLink = true;
        }
    }

    /**
    *   @brief Clean old AP information
    */
    void APManager::CleanAPInformation()
    {
        // TODO: Cleanup old content from "information" variable
        if (pendingItemIDs.Num() > 0)
        {
            pendingItemIDs.Empty();
        }
        AP_DeathLinkClear();
        if (information.pendingDeathLink)
        {
            information.pendingDeathLink = false;
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
}
