#include <Mod/CppUserModBase.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/FProperty.hpp>

#include "Archipelago.h"
#include "ModConsole.hpp"

using namespace RC;
using namespace RC::Unreal;


typedef struct {
    bool authenticated;
    FString statusMessage;
}ConnectionMessage;


const std::string CURRENT_WORLD_VERSION = "1.0.0"; // To update when the version of the AP logic changes
std::string latestWorldVersion;
TArray<bool> isAPOptionEnabled;

// The ItemManager Blueprints manages the player inventory when an Archipelago item is received
UObject* ItemManager = NULL;
// The following events are executed by ItemManager Blueprint when a signal is received
UFunction* ItemReceivedEvent = NULL;
UFunction* ArchipelagoMessageEvent = NULL;
UFunction* GetAllItemAmountsEvent = NULL;
UFunction* ConnectionStatusUpdatedEvent = NULL;
UFunction* CheckItemUnlockedEvent = NULL;
UFunction* UpdateUnlockedPaintCansEvent = NULL;
UFunction* UpdateUnlockedObjectsEvent = NULL;
UFunction* ReceiveDeathLinkEvent = NULL;
UFunction* GetAPOptionsEvent = NULL;

static bool authenticated = false;
static bool isNewGame = false;


class RandomizerMod : public RC::CppUserModBase
{
public:
    RandomizerMod() : CppUserModBase()
    {
        ModName = STR("RandomizerMod");
        ModVersion = STR("0.0.4-beta");
        ModDescription = STR("Choo-Choo Charles Archipelago Mutiworld Randomizer");
        ModAuthors = STR("Yaranorgoth");
        // Do not change this unless you want to target a UE4SS version
        // other than the one you're currently building with somehow.
        //ModIntendedSDKVersion = STR("2.6");

        Output::send<LogLevel::Verbose>(STR("Mod name: {}\n"), ModName);
        Output::send<LogLevel::Verbose>(STR("Version: {}\n"), ModVersion);
        Output::send<LogLevel::Verbose>(STR("{}\n"), ModDescription);
        Output::send<LogLevel::Verbose>(STR("Author: {}\n"), ModAuthors);
    }

    ~RandomizerMod() override
    {
    }

    static auto CallbackFunctionHook([[maybe_unused]] Unreal::UObject* Context, Unreal::FFrame& Stack, [[maybe_unused]] void* RESULT_DECL) -> void
    {
        // Set the hooked functions/events names once
        static auto SendLocationIDHook = FName(STR("SendLocationID"), FNAME_Add); // Send locationID to Archipelago
        static auto GameReloadedHook = FName(STR("GameReloaded"), FNAME_Add); // The game was reloaded, reset BP variables
        static auto CharlesDeathHook = FName(STR("CharlesDeath"), FNAME_Add); // Function from the game called if Charles died
        static auto CheckPendingMessageHook = FName(STR("CheckPendingMessage"), FNAME_Add); // Show the last Archipelago pending message
        static auto NewGameStartHook = FName(STR("NewGameStart"), FNAME_Add); // The player lost in Nightmare mode or restarted a new game
        static auto GetConnectionStatusHook = FName(STR("GetConnectionStatus"), FNAME_Add); // Check if the player is authenticated or not
        static auto GetPendingItemsHook = FName(STR("GetPendingItems"), FNAME_Add); // Check if the player receives new items
        static auto IsUnlockedWeaponByIndexHook = FName(STR("IsUnlockedWeaponByIndex"), FNAME_Add); // Check a weapon is unlocked by its index
        static auto IsUnlockedPaintCanByIndexHook = FName(STR("IsUnlockedPaintCanByIndex"), FNAME_Add); // Check a paint can is unlocked by its index
        static auto IsUnlockedEggByIndexHook = FName(STR("IsUnlockedEggByIndex"), FNAME_Add); // Check an egg is unlocked by its index
        static auto GetUnlockedPaintCansHook = FName(STR("GetUnlockedPaintCans"), FNAME_Add); // Get an boolean array of the unlocked Paint Cans
        static auto GetUnlockedObjectsHook = FName(STR("GetUnlockedObjects"), FNAME_Add); // Get an int array of the unlocked Objects amounts
        static auto CheckDeathLinkHook = FName(STR("CheckDeathLink"), FNAME_Add); // Check a Deathlink was received
        static auto SendDeathLinkHook = FName(STR("SendDeathLink"), FNAME_Add); // Send Deathlink at player death
        static auto CheckPendingAPOptionsHook = FName(STR("CheckPendingAPOptions"), FNAME_Add); // Check AP options once connected

        // Check the hooked function/event names are correct
        if (Stack.Node()->GetNamePrivate() == SendLocationIDHook)
        {
            Output::send<LogLevel::Verbose>(STR("SendLocationIDHook\n"));

            // If the Archipelago connection is not established yet, exit early
            if (AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
            {
                Output::send<LogLevel::Verbose>(STR("The player is not authenticated\n"));
                return;
            }

            // Get the parameters in order
            int64_t* locationID = Stack.Node()->GetPropertyByName(STR("locationID"))->ContainerPtrToValuePtr<int64_t>(Stack.Locals());
            Output::send<LogLevel::Verbose>(STR("{}\n"), *locationID);

            // If the ID is -1, no item was found, exit early
            if (*locationID == -1)
            {
                Output::send<LogLevel::Error>(STR("Item not found: locationID == -1\n"));
                return;
            }

            AP_SendItem(*locationID);
        }
        else if (Stack.Node()->GetNamePrivate() == GameReloadedHook)
        {
            Output::send<LogLevel::Verbose>(STR("GameReloadedHook\n"));

            ItemManager = NULL;
            ItemReceivedEvent = NULL;
            ArchipelagoMessageEvent = NULL;
            GetAllItemAmountsEvent = NULL;
            ConnectionStatusUpdatedEvent = NULL;
            CheckItemUnlockedEvent = NULL;
            UpdateUnlockedPaintCansEvent = NULL;
            UpdateUnlockedObjectsEvent = NULL;
            ReceiveDeathLinkEvent = NULL;
            GetAPOptionsEvent = NULL;
            authenticated = false;
        }
        else if (Stack.Node()->GetNamePrivate() == CharlesDeathHook)
        {
            Output::send<LogLevel::Verbose>(STR("CharlesDeathHook\n"));

            // If the Archipelago connection is not established yet, exit early
            if (AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
            {
                Output::send<LogLevel::Verbose>(STR("The player is not authenticated\n"));
                return;
            }

            AP_StoryComplete();
        }
        else if (Stack.Node()->GetNamePrivate() == CheckPendingMessageHook)
        {
            // No header debug message for hooks called every tick

            if (AP_GetConnectionStatus() == AP_ConnectionStatus::Authenticated && AP_IsMessagePending())
            {
                if (ItemManager != NULL)
                {
                    if (ArchipelagoMessageEvent == NULL)
                    {
                        Output::send<LogLevel::Error>(STR("ArchipelagoMessage not found\n"));
                        return;
                    }

                    FString message = FString(to_wstring(AP_GetLatestMessage()->text).c_str());
                    Output::send<LogLevel::Verbose>(STR("Pending message: {}\n"), to_wstring(AP_GetLatestMessage()->text).c_str());
                    if (ItemManager != NULL)
                    {
                        ItemManager->ProcessEvent(ArchipelagoMessageEvent, &message);
                    }
                    AP_ClearLatestMessage();
                }
            }
        }
        else if (Stack.Node()->GetNamePrivate() == NewGameStartHook)
        {
            Output::send<LogLevel::Verbose>(STR("NewGameStartHook\n"));

            // NewGameStart is managed in on_update() to get all received items when possible
            isNewGame = true;
        }
        else if (Stack.Node()->GetNamePrivate() == GetConnectionStatusHook)
        {
            // No header debug message for hooks called every tick

            if (ItemManager != NULL)
            {
                if (ConnectionStatusUpdatedEvent == NULL)
                {
                    Output::send<LogLevel::Error>(STR("ConnectionStatusUpdated not found\n"));
                    return;
                }

                // Check the connection status changed
                if (!authenticated && AP_GetConnectionStatus() == AP_ConnectionStatus::Authenticated
                    || authenticated && AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
                {
                    ConnectionMessage connectionMessage;

                    authenticated = !authenticated;
                    connectionMessage.authenticated = authenticated;

                    if (!authenticated)
                    {
                        connectionMessage.statusMessage = FString(RC::to_wstring("Offline").c_str());
                    }
                    else if (CURRENT_WORLD_VERSION == latestWorldVersion)
                    {
                        connectionMessage.statusMessage = FString(RC::to_wstring("Connected").c_str());
                    }
                    else
                    {
                        connectionMessage.statusMessage = FString(RC::to_wstring(
                            "Mod update required\nv" + CURRENT_WORLD_VERSION + " -> v" + latestWorldVersion
                        ).c_str());
                    }
                    ItemManager->ProcessEvent(ConnectionStatusUpdatedEvent, &connectionMessage);
                }
            }
        }
        else if (Stack.Node()->GetNamePrivate() == GetPendingItemsHook)
        {
            // No header debug message for hooks called every tick

            if (ItemReceivedEvent == NULL)
            {
                Output::send<LogLevel::Error>(STR("ItemReceivedEvent not found\n"));
                return;
            }

            if (pendingItemIDs.Num() > 0)
            {
                ItemManager->ProcessEvent(ItemReceivedEvent, &pendingItemIDs);
                pendingItemIDs.Empty();
            }
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedWeaponByIndexHook)
        {
            Output::send<LogLevel::Verbose>(STR("IsUnlockedWeaponByIndexHook\n"));

            int32_t* index = Stack.Node()->GetPropertyByName(STR("WeaponIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());
            ItemManager->ProcessEvent(CheckItemUnlockedEvent, &receivedItems.weapons[*index].unlocked);
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedPaintCanByIndexHook)
        {
            Output::send<LogLevel::Verbose>(STR("IsUnlockedPaintCanByIndexHook\n"));

            int32_t* index = Stack.Node()->GetPropertyByName(STR("PaintCanIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());
            Output::send<LogLevel::Verbose>(STR("{}\n"), *index);
            Output::send<LogLevel::Verbose>(STR("{}\n"), receivedItems.paintCans[*index].unlocked);
            ItemManager->ProcessEvent(CheckItemUnlockedEvent, &receivedItems.paintCans[*index].unlocked);
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedEggByIndexHook)
        {
            Output::send<LogLevel::Verbose>(STR("IsUnlockedEggByIndexHook\n"));

            int32_t* index = Stack.Node()->GetPropertyByName(STR("EggIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());

            // EggIndex must be [19;20;21] respectively for [Green;Blue;Red], see ItemReceivedCallback()
            if (*index < 19 && *index > 21)
            {
                // Exit early if the range of EggIndex is not respected
                Output::send<LogLevel::Error>(STR("EggIndex out of range\n"));
                return;
            }

            bool isEggUnlocked = receivedItems.items[*index].amount == 0 ? false : true;
            ItemManager->ProcessEvent(CheckItemUnlockedEvent, &isEggUnlocked);
        }
        else if (Stack.Node()->GetNamePrivate() == GetUnlockedPaintCansHook)
        {
            // No header debug message for hooks called every tick

            if (UpdateUnlockedPaintCansEvent == NULL)
            {
                Output::send<LogLevel::Error>(STR("UpdateUnlockedPaintCansEvent not found\n"));
                return;
            }

            ItemManager->ProcessEvent(UpdateUnlockedPaintCansEvent, &receivedItems.paintCans);
        }
        else if (Stack.Node()->GetNamePrivate() == GetUnlockedObjectsHook)
        {
            // No header debug message for hooks called every tick

            if (UpdateUnlockedObjectsEvent == NULL)
            {
                Output::send<LogLevel::Error>(STR("UpdateUnlockedObjectsEvent not found\n"));
                return;
            }

            ItemManager->ProcessEvent(UpdateUnlockedObjectsEvent, &receivedItems.objects);
        }
        else if (Stack.Node()->GetNamePrivate() == CheckDeathLinkHook)
        {
            // No header debug message for hooks called every tick

            if (ReceiveDeathLinkEvent == NULL)
            {
                Output::send<LogLevel::Error>(STR("ReceiveDeathLinkEvent not found\n"));
                return;
            }

            if (AP_DeathLinkPending())
            {
                ItemManager->ProcessEvent(ReceiveDeathLinkEvent, NULL);
                AP_DeathLinkClear();
            }
        }
        else if (Stack.Node()->GetNamePrivate() == SendDeathLinkHook)
        {
            Output::send<LogLevel::Verbose>(STR("SendDeathLinkHook\n"));

            AP_DeathLinkSend();
        }
        else if (Stack.Node()->GetNamePrivate() == CheckPendingAPOptionsHook)
        {
            Output::send<LogLevel::Verbose>(STR("CheckPendingAPOptionsHook\n"));

            if (GetAPOptionsEvent == NULL)
            {
                Output::send<LogLevel::Error>(STR("GetAPOptionsEvent not found\n"));
                return;
            }

            ItemManager->ProcessEvent(GetAPOptionsEvent, &isAPOptionEnabled);
        }
    }

    static bool CallbackConsole(UObject* object, const Unreal::TCHAR* command, FOutputDevice& Ar, UObject* executor)
    {
        bool same = ModConsole::CheckCommand(Ar, command);

        if (same)
        {
            Output::send<LogLevel::Verbose>(STR("Command detected with success: {}\n"), command);
        }
        else
        {
            Output::send<LogLevel::Verbose>(STR("Command not found or missing arguments: {}\n"), command);
        }
        
        return same;
    }

    auto on_unreal_init() -> void override
    {
        // You are allowed to use the 'Unreal' namespace in this function and anywhere else after this function has fired.
        auto Object = UObjectGlobals::StaticFindObject<UObject*>(nullptr, nullptr, STR("/Script/CoreUObject.Object"));
        Output::send<LogLevel::Verbose>(STR("Object Name: {}\n"), Object->GetFullName());

        // Initialisations
        Hook::RegisterProcessConsoleExecCallback(CallbackConsole);
        isAPOptionEnabled.SetNum(NB_AP_OPTIONS);
        for (int i = 0; i < isAPOptionEnabled.Num(); i++)
        {
            isAPOptionEnabled[i] = false;
        }

        receivedItems.items.SetNum(24);
        receivedItems.items[0].name = FString(to_wstring("05_Scraps").c_str());
        receivedItems.items[1].name = FString(to_wstring("Mine1_Key").c_str());
        receivedItems.items[2].name = FString(to_wstring("Mine2_Key").c_str());
        receivedItems.items[3].name = FString(to_wstring("Mine3_Key").c_str());
        receivedItems.items[4].name = FString(to_wstring("01_KeyTony").c_str());
        receivedItems.items[5].name = FString(to_wstring("Tutorial2_Key").c_str());
        receivedItems.items[6].name = FString(to_wstring("Swamp_Fish").c_str());
        receivedItems.items[7].name = FString(to_wstring("Junkyard_LockPicks").c_str());
        receivedItems.items[8].name = FString(to_wstring("Junkyard_Tablet").c_str());
        receivedItems.items[9].name = FString(to_wstring("Canyon_BlueBox").c_str());
        receivedItems.items[10].name = FString(to_wstring("Pages_Drawing").c_str());
        receivedItems.items[11].name = FString(to_wstring("Port_Journal").c_str());
        receivedItems.items[12].name = FString(to_wstring("Boomer_Dynamite").c_str());
        receivedItems.items[13].name = FString(to_wstring("Boomer_Rockets").c_str());
        receivedItems.items[14].name = FString(to_wstring("Lighthouse_Breaker").c_str());
        receivedItems.items[15].name = FString(to_wstring("Bob_BobPiece").c_str());
        receivedItems.items[16].name = FString(to_wstring("Towers_Files").c_str());
        receivedItems.items[17].name = FString(to_wstring("Bob_Key").c_str());
        receivedItems.items[18].name = FString(to_wstring("Pickles_Jar").c_str());
        receivedItems.items[19].name = FString(to_wstring("Mine1_Egg").c_str());
        receivedItems.items[20].name = FString(to_wstring("Mine2_Egg").c_str());
        receivedItems.items[21].name = FString(to_wstring("Mine3_Egg").c_str());
        receivedItems.items[22].name = FString(to_wstring("Bridge_Dynamite").c_str());
        receivedItems.items[23].name = FString(to_wstring("Boss_ShrineKey").c_str());
        for (int i = 0; i < receivedItems.items.Num(); i++)
        {
            receivedItems.items[i].amount = 0;
        }

        const unsigned int MaxTrackSwitch = 8;
        const unsigned int MaxFogbaneRelic = 35;
        receivedItems.objects.SetNum(MaxTrackSwitch + MaxFogbaneRelic);
        receivedItems.objects[0].name = FString(to_wstring("Track Switch Pack").c_str());
        receivedItems.objects[1].name = FString(to_wstring("Track Switch - Barn or Tutorial").c_str());
        receivedItems.objects[2].name = FString(to_wstring("Track Switch - Middle or Port").c_str());
        receivedItems.objects[3].name = FString(to_wstring("Track Switch - Haunted or East").c_str());
        receivedItems.objects[4].name = FString(to_wstring("Track Switch - North or Temple").c_str());
        receivedItems.objects[5].name = FString(to_wstring("Track Switch - Caravan or Cultists").c_str());
        receivedItems.objects[6].name = FString(to_wstring("Track Switch - Camp or Elevator").c_str());
        receivedItems.objects[7].name = FString(to_wstring("Track Switch - Ruin or Temple").c_str());
        receivedItems.objects[8].name = FString(to_wstring("Fogbane Relic Pack").c_str());
        receivedItems.objects[9].name = FString(to_wstring("Fogbane Relic - Mine Shaft").c_str());
        receivedItems.objects[10].name = FString(to_wstring("Fogbane Relic - Junkyard Area").c_str());
        receivedItems.objects[11].name = FString(to_wstring("Fogbane Relic - Junkyard Shed").c_str());
        receivedItems.objects[12].name = FString(to_wstring("Fogbane Relic - South House").c_str());
        receivedItems.objects[13].name = FString(to_wstring("Fogbane Relic - Military Base").c_str());
        receivedItems.objects[14].name = FString(to_wstring("Fogbane Relic - South Mine Outside").c_str());
        receivedItems.objects[15].name = FString(to_wstring("Fogbane Relic - Middle Station").c_str());
        receivedItems.objects[16].name = FString(to_wstring("Fogbane Relic - Canyon").c_str());
        receivedItems.objects[17].name = FString(to_wstring("Fogbane Relic - Watchtower").c_str());
        receivedItems.objects[18].name = FString(to_wstring("Fogbane Relic - Haunted House").c_str());
        receivedItems.objects[19].name = FString(to_wstring("Fogbane Relic - Santiago House").c_str());
        receivedItems.objects[20].name = FString(to_wstring("Fogbane Relic - Port").c_str());
        receivedItems.objects[21].name = FString(to_wstring("Fogbane Relic - Doll Woods").c_str());
        receivedItems.objects[22].name = FString(to_wstring("Fogbane Relic - East House").c_str());
        receivedItems.objects[23].name = FString(to_wstring("Fogbane Relic - Rocket Grounds").c_str());
        receivedItems.objects[24].name = FString(to_wstring("Fogbane Relic - Workshop").c_str());
        receivedItems.objects[25].name = FString(to_wstring("Fogbane Relic - East Tower").c_str());
        receivedItems.objects[26].name = FString(to_wstring("Fogbane Relic - Lighthouse").c_str());
        receivedItems.objects[27].name = FString(to_wstring("Fogbane Relic - North Mine Outside").c_str());
        receivedItems.objects[28].name = FString(to_wstring("Fogbane Relic - Wood Bridge").c_str());
        receivedItems.objects[29].name = FString(to_wstring("Fogbane Relic - Museum").c_str());
        receivedItems.objects[30].name = FString(to_wstring("Fogbane Relic - Barbed Shelter").c_str());
        receivedItems.objects[31].name = FString(to_wstring("Fogbane Relic - West Beach").c_str());
        receivedItems.objects[32].name = FString(to_wstring("Fogbane Relic - Church").c_str());
        receivedItems.objects[33].name = FString(to_wstring("Fogbane Relic - West Cottage").c_str());
        receivedItems.objects[34].name = FString(to_wstring("Fogbane Relic - Trailer Cabin").c_str());
        receivedItems.objects[35].name = FString(to_wstring("Fogbane Relic - Towers").c_str());
        receivedItems.objects[36].name = FString(to_wstring("Fogbane Relic - North Beach").c_str());
        receivedItems.objects[37].name = FString(to_wstring("Fogbane Relic - Mob Camp").c_str());
        receivedItems.objects[38].name = FString(to_wstring("Fogbane Relic - Mine Elevator Exit").c_str());
        receivedItems.objects[39].name = FString(to_wstring("Fogbane Relic - Mountain Ruin Outside").c_str());
        receivedItems.objects[40].name = FString(to_wstring("Fogbane Relic - Temple").c_str());
        receivedItems.objects[41].name = FString(to_wstring("Fogbane Relic - Pickle Val").c_str());
        receivedItems.objects[42].name = FString(to_wstring("Fogbane Relic - Morse Bunker").c_str());
        for (int i = 0; i < receivedItems.objects.Num(); i++)
        {
            receivedItems.objects[i].amount = 0;
        }

        receivedItems.paintCans.SetNum(11);
        receivedItems.paintCans[0].name = FString(to_wstring("Orange Paint Can").c_str());
        receivedItems.paintCans[1].name = FString(to_wstring("Green Paint Can").c_str());
        receivedItems.paintCans[2].name = FString(to_wstring("White Paint Can").c_str());
        receivedItems.paintCans[3].name = FString(to_wstring("Pink Paint Can").c_str());
        receivedItems.paintCans[4].name = FString(to_wstring("Gray Paint Can").c_str());
        receivedItems.paintCans[5].name = FString(to_wstring("Blue Paint Can").c_str());
        receivedItems.paintCans[6].name = FString(to_wstring("Black Paint Can").c_str());
        receivedItems.paintCans[7].name = FString(to_wstring("Lime Paint Can").c_str());
        receivedItems.paintCans[8].name = FString(to_wstring("Teal Paint Can").c_str());
        receivedItems.paintCans[9].name = FString(to_wstring("Red Paint Can").c_str());
        receivedItems.paintCans[10].name = FString(to_wstring("Purple Paint Can").c_str());
        for (int i = 0; i < receivedItems.paintCans.Num(); i++)
        {
            receivedItems.paintCans[i].unlocked = false;
        }
        
        receivedItems.weapons.SetNum(3);
        receivedItems.weapons[0].name = FString(to_wstring("The Boomer").c_str());
        receivedItems.weapons[1].name = FString(to_wstring("Bob").c_str());
        receivedItems.weapons[2].name = FString(to_wstring("Bug Spray").c_str());
        for (int i = 0; i < receivedItems.weapons.Num(); i++)
        {
            receivedItems.weapons[i].unlocked = false;
        }

        // Callback for all hooked functions and events
        if (UObject::ProcessLocalScriptFunctionInternal.is_ready() && Unreal::Version::IsAtLeast(4, 22))
        {
            Output::send(STR("Enabling custom event hooks\n"));
            Hook::RegisterProcessLocalScriptFunctionPostCallback(CallbackFunctionHook);
        }
    }

    auto on_update() -> void override
    {
        // When the game is reloaded, the ItemManager reference is set to NULL, set it when available
        if (ItemManager == NULL)
        {
            ItemManager = UObjectGlobals::FindFirstOf(STR("ItemManager_C"));
        }

        // Actions when ItemManager is available
        if (ItemManager != NULL)
        {
            // Set each event if not set
            if (ItemReceivedEvent == NULL)
            {
                static auto ItemReceived = FName(STR("ItemReceived"), FNAME_Add);
                ItemReceivedEvent = ItemManager->GetFunctionByName(ItemReceived);
            }

            if (ArchipelagoMessageEvent == NULL)
            {
                static auto ArchipelagoMessage = FName(STR("ArchipelagoMessage"), FNAME_Add);
                ArchipelagoMessageEvent = ItemManager->GetFunctionByName(ArchipelagoMessage);
            }

            if (GetAllItemAmountsEvent == NULL)
            {
                static auto GetAllItemAmounts = FName(STR("GetAllItemAmounts"), FNAME_Add);
                GetAllItemAmountsEvent = ItemManager->GetFunctionByName(GetAllItemAmounts);
            }
            if (ConnectionStatusUpdatedEvent == NULL)
            {
                static auto ConnectionStatusUpdated = FName(STR("ConnectionStatusUpdated"), FNAME_Add);
                ConnectionStatusUpdatedEvent = ItemManager->GetFunctionByName(ConnectionStatusUpdated);
            }
            if (CheckItemUnlockedEvent == NULL)
            {
                static auto CheckItemUnlocked = FName(STR("CheckItemUnlocked"), FNAME_Add);
                CheckItemUnlockedEvent = ItemManager->GetFunctionByName(CheckItemUnlocked);
            }
            if (UpdateUnlockedPaintCansEvent == NULL)
            {
                static auto UpdateUnlockedPaintCans = FName(STR("UpdateUnlockedPaintCans"), FNAME_Add);
                UpdateUnlockedPaintCansEvent = ItemManager->GetFunctionByName(UpdateUnlockedPaintCans);
            }
            if (UpdateUnlockedObjectsEvent == NULL)
            {
                static auto UpdateUnlockedObjects = FName(STR("UpdateUnlockedObjects"), FNAME_Add);
                UpdateUnlockedObjectsEvent = ItemManager->GetFunctionByName(UpdateUnlockedObjects);
            }
            if (ReceiveDeathLinkEvent == NULL)
            {
                static auto ReceiveDeathLink = FName(STR("ReceiveDeathLink"), FNAME_Add);
                ReceiveDeathLinkEvent = ItemManager->GetFunctionByName(ReceiveDeathLink);
            }
            if (GetAPOptionsEvent == NULL)
            {
                static auto GetAPOptions = FName(STR("GetAPOptions"), FNAME_Add);
                GetAPOptionsEvent = ItemManager->GetFunctionByName(GetAPOptions);
            }

            // If the game is restarted and connected to AP, get all IDs to recover received items
            if (isNewGame && AP_GetConnectionStatus() == AP_ConnectionStatus::Authenticated)
            {
                if (GetAllItemAmountsEvent == NULL)
                {
                    Output::send<LogLevel::Error>(STR("GetAllItemAmounts not found\n"));
                }
                else
                {
                    pendingItemIDs.Empty(); // All items will be retrieved, meaning no item will be pending
                    ItemManager->ProcessEvent(GetAllItemAmountsEvent, &receivedItems);
                    isNewGame = false;
                }
            }
        }
    }
};

#define RANDOMIZER_MOD_API __declspec(dllexport)
extern "C"
{
    RANDOMIZER_MOD_API RC::CppUserModBase* start_mod()
    {
        return new RandomizerMod();
    }

    RANDOMIZER_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}
