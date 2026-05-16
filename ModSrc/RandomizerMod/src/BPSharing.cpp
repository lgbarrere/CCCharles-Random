
#include <Unreal/UFunction.hpp>
#include <Unreal/FProperty.hpp>

#include "BPSharing.hpp"
#include "APManager.hpp"
#include "Archipelago.h"


using namespace RC;
using namespace RC::Unreal;


// The ItemManager Blueprints manages the player inventory when an Archipelago item is received
UObject* ItemManager = NULL;
// The following events are executed by ItemManager Blueprint when a signal is received
UFunction* GetAllItemAmountsEvent = NULL;
UFunction* CheckItemUnlockedEvent = NULL;
UFunction* GetAPOptionsEvent = NULL;

static bool isNewGame = false;

namespace BPSharing {
    /**
    *   @brief Receive the address of an output parameter of a Blueprint function
    *   @param Stack: The reference of the stack containing the function and local parameters
    *   @param Param: The address of the parameter to get from the function
    * 
    *   @important This function is a duplicate from FFrame.cpp because of linking errors.
    *   Adding RC_UE_API before the declaration of this function in FFrame.hpp to export it did not work
    */
    void* FindOutParamValueAddress(FFrame& Stack, FProperty* Param)
    {
        auto OutParams = Stack.OutParms();
        while (OutParams && OutParams->Property != Param)
        {
            OutParams = OutParams->NextOutParm;
        }
        return OutParams ? OutParams->PropAddr : nullptr;
    }

    void BPSharing::ManageHook([[maybe_unused]] Unreal::UObject* Context, Unreal::FFrame& Stack, [[maybe_unused]] void* RESULT_DECL)
    {
        // Set the hooked functions/events names once
        static auto EveryTickSharingCppHook = FName(STR("EveryTickSharingCpp"), FNAME_Add); // Function fired every tick
        static auto SendLocationIDHook = FName(STR("SendLocationID"), FNAME_Add); // Send locationID to Archipelago
        static auto CheckPendingAPMessageCppHook = FName(STR("CheckPendingAPMessageCpp"), FNAME_Add); // Show the last Archipelago pending message
        static auto GameReloadedHook = FName(STR("GameReloaded"), FNAME_Add); // The game was reloaded, reset BP variables
        static auto CharlesDeathHook = FName(STR("CharlesDeath"), FNAME_Add); // Function from the game called if Charles died
        static auto NewGameStartHook = FName(STR("NewGameStart"), FNAME_Add); // The player lost in Nightmare mode or restarted a new game
        static auto IsUnlockedWeaponByIndexHook = FName(STR("IsUnlockedWeaponByIndex"), FNAME_Add); // Check a weapon is unlocked by its index
        static auto IsUnlockedPaintCanByIndexHook = FName(STR("IsUnlockedPaintCanByIndex"), FNAME_Add); // Check a paint can is unlocked by its index
        static auto IsUnlockedEggByIndexHook = FName(STR("IsUnlockedEggByIndex"), FNAME_Add); // Check an egg is unlocked by its index
        static auto SendDeathLinkHook = FName(STR("SendDeathLink"), FNAME_Add); // Send Deathlink at player death
        static auto CheckPendingAPOptionsHook = FName(STR("CheckPendingAPOptions"), FNAME_Add); // Check AP options once connected

        // Check the hooked function/event names are correct
        if (Stack.Node()->GetNamePrivate() == EveryTickSharingCppHook)
        {
            // No header debug message for hooks called every tick

            APManager::GetConnectionStatus();
            APManager::CheckDeathLink();

            // Set BP return value
            //apData.statusMessage = FString(to_wstring("Debugging return code").c_str());
            *(APData*)RESULT_DECL = apData;

            // Cleanup
            APManager::CleanAPData();
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
            GetAllItemAmountsEvent = NULL;
            CheckItemUnlockedEvent = NULL;
            GetAPOptionsEvent = NULL;
            apData.authenticated = false;
        }
        else if (Stack.Node()->GetNamePrivate() == CheckPendingAPMessageCppHook)
        {
            // No header debug message for hooks called by a looping timer
            if (AP_GetConnectionStatus() == AP_ConnectionStatus::Authenticated && AP_IsMessagePending())
            {
                FString pendingMessage = FString(to_wstring(AP_GetLatestMessage()->text).c_str());
                Output::send<LogLevel::Verbose>(STR("Pending message: {}\n"), to_wstring(AP_GetLatestMessage()->text).c_str());
                AP_ClearLatestMessage();

                // Set specific output value of BP function
                FProperty* outProperty = Stack.Node()->GetPropertyByName(L"APMessage");
                void* outPropertyAddress = BPSharing::FindOutParamValueAddress(Stack, outProperty);
                *static_cast<FString*>(outPropertyAddress) = pendingMessage;
            }
        }
        else if (Stack.Node()->GetNamePrivate() == CharlesDeathHook)
        {
            Output::send<LogLevel::Verbose>(STR("CharlesDeathHook\n"));

            APManager::Victory();
        }
        else if (Stack.Node()->GetNamePrivate() == NewGameStartHook)
        {
            Output::send<LogLevel::Verbose>(STR("NewGameStartHook\n"));

            // NewGameStart is managed in BPSharing::SetBPFunctions() to get all received items when possible
            isNewGame = true;
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedWeaponByIndexHook)
        {
            if (ItemManager != NULL)
            {
                Output::send<LogLevel::Verbose>(STR("IsUnlockedWeaponByIndexHook\n"));

                if (CheckItemUnlockedEvent == NULL)
                {
                    Output::send<LogLevel::Error>(STR("CheckItemUnlockedEvent not found\n"));
                    return;
                }

                int32_t* index = Stack.Node()->GetPropertyByName(STR("WeaponIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());
                ItemManager->ProcessEvent(CheckItemUnlockedEvent, &apData.allReceivedItems.weapons[*index].unlocked);
            }
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedPaintCanByIndexHook)
        {
            if (ItemManager != NULL)
            {
                Output::send<LogLevel::Verbose>(STR("IsUnlockedPaintCanByIndexHook\n"));

                if (CheckItemUnlockedEvent == NULL)
                {
                    Output::send<LogLevel::Error>(STR("CheckItemUnlockedEvent not found\n"));
                    return;
                }

                int32_t* index = Stack.Node()->GetPropertyByName(STR("PaintCanIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());
                Output::send<LogLevel::Verbose>(STR("{}\n"), *index);
                Output::send<LogLevel::Verbose>(STR("{}\n"), apData.allReceivedItems.paintCans[*index].unlocked);
                Output::send<LogLevel::Error>(STR("CheckItemUnlockedEvent not found\n"));
            }
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedEggByIndexHook)
        {
            if (ItemManager != NULL)
            {
                Output::send<LogLevel::Verbose>(STR("IsUnlockedEggByIndexHook\n"));

                if (CheckItemUnlockedEvent == NULL)
                {
                    Output::send<LogLevel::Error>(STR("CheckItemUnlockedEvent not found\n"));
                    return;
                }

                int32_t* index = Stack.Node()->GetPropertyByName(STR("EggIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());

                // EggIndex must be [19;20;21] respectively for [Green;Blue;Red], see ItemReceivedCallback() in APManager.cpp
                if (*index < 19 && *index > 21)
                {
                    // Exit early if the range of EggIndex is not respected
                    Output::send<LogLevel::Error>(STR("EggIndex out of range\n"));
                    return;
                }

                bool isEggUnlocked = APManager::CheckEggByIndex(*index);
                ItemManager->ProcessEvent(CheckItemUnlockedEvent, &isEggUnlocked);
            }
        }
        else if (Stack.Node()->GetNamePrivate() == SendDeathLinkHook)
        {
            Output::send<LogLevel::Verbose>(STR("SendDeathLinkHook\n"));

            AP_DeathLinkSend();
        }
        else if (Stack.Node()->GetNamePrivate() == CheckPendingAPOptionsHook)
        {
            if (ItemManager != NULL)
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
            if (GetAllItemAmountsEvent == NULL)
            {
                static auto GetAllItemAmounts = FName(STR("GetAllItemAmounts"), FNAME_Add);
                GetAllItemAmountsEvent = ItemManager->GetFunctionByName(GetAllItemAmounts);
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
                    apData.pendingItemIDs.Empty(); // All items will be retrieved, meaning no item will be pending
                    ItemManager->ProcessEvent(GetAllItemAmountsEvent, &apData.allReceivedItems);
                    isNewGame = false;
                }
            }
        }
    }
}
