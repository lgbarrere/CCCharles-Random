
#include <Unreal/UFunction.hpp>
#include <Unreal/FProperty.hpp>

#include "BPSharing.hpp"
#include "APManager.hpp"


using namespace RC;
using namespace RC::Unreal;


// The ItemManager Blueprints manages the player inventory when an Archipelago item is received
UObject* ItemManager = NULL;
// The following events are executed by ItemManager Blueprint when a signal is received
UFunction* EveryTickEvent = NULL;
UFunction* ItemReceivedEvent = NULL;
UFunction* ArchipelagoMessageEvent = NULL;
UFunction* GetAllItemAmountsEvent = NULL;
UFunction* ConnectionStatusUpdatedEvent = NULL;
UFunction* CheckItemUnlockedEvent = NULL;
UFunction* GetAPOptionsEvent = NULL;

static bool isNewGame = false;


namespace BPSharing {
    void BPSharing::ManageHook(Unreal::FFrame& Stack)
    {
        // Set the hooked functions/events names once
        static auto EveryTickHook = FName(STR("EveryTick"), FNAME_Add); // Function fired every tick
        static auto SendLocationIDHook = FName(STR("SendLocationID"), FNAME_Add); // Send locationID to Archipelago
        static auto GameReloadedHook = FName(STR("GameReloaded"), FNAME_Add); // The game was reloaded, reset BP variables
        static auto CharlesDeathHook = FName(STR("CharlesDeath"), FNAME_Add); // Function from the game called if Charles died
        static auto NewGameStartHook = FName(STR("NewGameStart"), FNAME_Add); // The player lost in Nightmare mode or restarted a new game
        static auto IsUnlockedWeaponByIndexHook = FName(STR("IsUnlockedWeaponByIndex"), FNAME_Add); // Check a weapon is unlocked by its index
        static auto IsUnlockedPaintCanByIndexHook = FName(STR("IsUnlockedPaintCanByIndex"), FNAME_Add); // Check a paint can is unlocked by its index
        static auto IsUnlockedEggByIndexHook = FName(STR("IsUnlockedEggByIndex"), FNAME_Add); // Check an egg is unlocked by its index
        static auto SendDeathLinkHook = FName(STR("SendDeathLink"), FNAME_Add); // Send Deathlink at player death
        static auto CheckPendingAPOptionsHook = FName(STR("CheckPendingAPOptions"), FNAME_Add); // Check AP options once connected

        // Check the hooked function/event names are correct
        if (Stack.Node()->GetNamePrivate() == EveryTickHook)
        {
            // No header debug message for hooks called every tick

            if (ItemManager != NULL)
            {
                // If the event tick event is not found, exit early
                if (EveryTickEvent == NULL)
                {
                    Output::send<LogLevel::Error>(STR("EveryTickEvent not found\n"));
                    return;
                }

                APManager::GetConnectionStatus();
                APManager::CheckDeathLink();

                ItemManager->ProcessEvent(EveryTickEvent, &information);

                // Cleanup
                APManager::CleanAPInformation();
            }
        }
        else if (Stack.Node()->GetNamePrivate() == SendLocationIDHook)
        {
            Output::send<LogLevel::Verbose>(STR("SendLocationIDHook\n"));

            // Get the parameters in order
            int64_t* locationID = Stack.Node()->GetPropertyByName(STR("locationID"))->ContainerPtrToValuePtr<int64_t>(Stack.Locals());
            Output::send<LogLevel::Verbose>(STR("{}\n"), *locationID);
            APManager::SendAPLocation(*locationID);
        }
        else if (Stack.Node()->GetNamePrivate() == GameReloadedHook)
        {
            Output::send<LogLevel::Verbose>(STR("GameReloadedHook\n"));

            ItemManager = NULL;
            EveryTickEvent = NULL;
            ItemReceivedEvent = NULL;
            ArchipelagoMessageEvent = NULL;
            GetAllItemAmountsEvent = NULL;
            ConnectionStatusUpdatedEvent = NULL;
            CheckItemUnlockedEvent = NULL;
            GetAPOptionsEvent = NULL;
            information.authenticated = false;
        }
        else if (Stack.Node()->GetNamePrivate() == GetPendingMessageHook)
        {
            // No header debug message for hooks called by a looping timer
            if (ItemManager != NULL)
            {
                // If the event tick event is not found, exit early
                if (GetPendingMessageEvent == NULL)
                {
                    Output::send<LogLevel::Error>(STR("GetPendingMessageEvent not found\n"));
                    return;
                }

                if (AP_GetConnectionStatus() == AP_ConnectionStatus::Authenticated && AP_IsMessagePending())
                {

                    FString pendingMessage = FString(to_wstring(AP_GetLatestMessage()->text).c_str());
                    Output::send<LogLevel::Verbose>(STR("Pending message: {}\n"), to_wstring(AP_GetLatestMessage()->text).c_str());
                    ItemManager->ProcessEvent(GetPendingMessageEvent, &pendingMessage);
                    AP_ClearLatestMessage();
                }
            }
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
        else if (Stack.Node()->GetNamePrivate() == NewGameStartHook)
        {
            Output::send<LogLevel::Verbose>(STR("NewGameStartHook\n"));

            // NewGameStart is managed in on_update() to get all received items when possible
            isNewGame = true;
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedWeaponByIndexHook)
        {
            Output::send<LogLevel::Verbose>(STR("IsUnlockedWeaponByIndexHook\n"));

            int32_t* index = Stack.Node()->GetPropertyByName(STR("WeaponIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());
            ItemManager->ProcessEvent(CheckItemUnlockedEvent, &information.receivedItems.weapons[*index].unlocked);
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedPaintCanByIndexHook)
        {
            Output::send<LogLevel::Verbose>(STR("IsUnlockedPaintCanByIndexHook\n"));

            int32_t* index = Stack.Node()->GetPropertyByName(STR("PaintCanIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());
            Output::send<LogLevel::Verbose>(STR("{}\n"), *index);
            Output::send<LogLevel::Verbose>(STR("{}\n"), information.receivedItems.paintCans[*index].unlocked);
            ItemManager->ProcessEvent(CheckItemUnlockedEvent, &information.receivedItems.paintCans[*index].unlocked);
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

            bool isEggUnlocked = information.receivedItems.items[*index].amount == 0 ? false : true;
            ItemManager->ProcessEvent(CheckItemUnlockedEvent, &isEggUnlocked);
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

    void BPSharing::SetBPFunctions()
    {
        // When the game is reloaded, the ItemManager reference is set to NULL, set it when available
        if (ItemManager == NULL)
        {
            ItemManager = UObjectGlobals::FindFirstOf(STR("BP_ItemManager_C"));
        }

        // Actions when ItemManager is available
        if (ItemManager != NULL)
        {
            // Set each event if not set
            if (EveryTickEvent == NULL)
            {
                static auto EveryTick = FName(STR("EveryTick"), FNAME_Add);
                EveryTickEvent = ItemManager->GetFunctionByName(EveryTick);
            }
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
                    ItemManager->ProcessEvent(GetAllItemAmountsEvent, &information.receivedItems);
                    isNewGame = false;
                }
            }
        }
    }
}
