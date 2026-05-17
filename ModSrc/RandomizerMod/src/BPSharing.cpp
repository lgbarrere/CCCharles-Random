
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
        static auto EveryTickSharingCpp = FName(STR("EveryTickSharingCpp"), FNAME_Add); // Function fired every tick
        static auto SendLocationIDCpp = FName(STR("SendLocationIDCpp"), FNAME_Add); // Send locationID to Archipelago
        static auto CheckPendingAPMessageCpp = FName(STR("CheckPendingAPMessageCpp"), FNAME_Add); // Show the last Archipelago pending message
        static auto GameReloadedCpp = FName(STR("GameReloadedCpp"), FNAME_Add); // The game was reloaded, reset BP variables
        static auto CharlesDeathCpp = FName(STR("CharlesDeathCpp"), FNAME_Add); // Function from the game called if Charles died
        static auto NewGameStartCpp = FName(STR("NewGameStartCpp"), FNAME_Add); // The player lost in Nightmare mode or restarted a new game
        static auto IsUnlockedWeaponByIndexCpp = FName(STR("IsUnlockedWeaponByIndexCpp"), FNAME_Add); // Check a weapon is unlocked by its index
        static auto IsUnlockedPaintCanByIndexCpp = FName(STR("IsUnlockedPaintCanByIndexCpp"), FNAME_Add); // Check a paint can is unlocked by its index
        static auto IsUnlockedEggByIndexCpp = FName(STR("IsUnlockedEggByIndexCpp"), FNAME_Add); // Check an egg is unlocked by its index
        static auto SendDeathLinkCpp = FName(STR("SendDeathLinkCpp"), FNAME_Add); // Send Deathlink at player death
        static auto CheckPendingAPOptionsCpp = FName(STR("CheckPendingAPOptionsCpp"), FNAME_Add); // Check AP options once connected

        // Check the hooked function/event names are correct
        if (Stack.Node()->GetNamePrivate() == EveryTickSharingCpp)
        {
            // No header debug message for hooks called every tick

            APManager::UpdateConnectionStatus();
            APManager::CheckDeathLink();

            // Set BP output value
            FProperty* outProperty = Stack.Node()->GetPropertyByName(L"APData");
            void* outPropertyAddress = BPSharing::FindOutParamValueAddress(Stack, outProperty);
            *static_cast<APData*>(outPropertyAddress) = apData;

            // Cleanup
            APManager::CleanAPData();
        }
        else if (Stack.Node()->GetNamePrivate() == SendLocationIDCpp)
        {
            Output::send<LogLevel::Verbose>(STR("SendLocationIDCpp\n"));

            // Get the parameters in order
            int64_t* locationID = Stack.Node()->GetPropertyByName(STR("locationID"))->ContainerPtrToValuePtr<int64_t>(Stack.Locals());
            Output::send<LogLevel::Verbose>(STR("{}\n"), *locationID);
            APManager::SendAPLocation(*locationID);
        }
        else if (Stack.Node()->GetNamePrivate() == GameReloadedCpp)
        {
            Output::send<LogLevel::Verbose>(STR("GameReloadedCpp\n"));

            ItemManager = NULL;
            GetAllItemAmountsEvent = NULL;
            apData.authenticated = false; // BPs are reset when the game reloads, including AP connections
        }
        else if (Stack.Node()->GetNamePrivate() == CheckPendingAPMessageCpp)
        {
            // No header debug message for hooks called by a looping timer

            if (apData.authenticated && AP_IsMessagePending())
            {
                FString pendingMessage = FString(to_wstring(AP_GetLatestMessage()->text).c_str());
                Output::send<LogLevel::Verbose>(STR("Pending message: {}\n"), to_wstring(AP_GetLatestMessage()->text).c_str());
                AP_ClearLatestMessage();

                // Set BP output value
                FProperty* outProperty = Stack.Node()->GetPropertyByName(L"APMessage");
                void* outPropertyAddress = BPSharing::FindOutParamValueAddress(Stack, outProperty);
                *static_cast<FString*>(outPropertyAddress) = pendingMessage;
            }
        }
        else if (Stack.Node()->GetNamePrivate() == CharlesDeathCpp)
        {
            Output::send<LogLevel::Verbose>(STR("CharlesDeathCpp\n"));

            APManager::Victory();
        }
        else if (Stack.Node()->GetNamePrivate() == NewGameStartCpp)
        {
            Output::send<LogLevel::Verbose>(STR("NewGameStartCpp\n"));

            // NewGameStartCpp is managed in BPSharing::SetBPFunctions() to get all received items when possible
            isNewGame = true;
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedWeaponByIndexCpp)
        {
            Output::send<LogLevel::Verbose>(STR("IsUnlockedWeaponByIndexCpp\n"));

            int32_t* index = Stack.Node()->GetPropertyByName(STR("WeaponIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());

            // Set BP output value
            FProperty* outProperty = Stack.Node()->GetPropertyByName(L"Unlocked");
            void* outPropertyAddress = BPSharing::FindOutParamValueAddress(Stack, outProperty);
            *static_cast<bool*>(outPropertyAddress) = apData.allReceivedItems.weapons[*index].unlocked;
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedPaintCanByIndexCpp)
        {
            Output::send<LogLevel::Verbose>(STR("IsUnlockedPaintCanByIndexCpp\n"));

            int32_t* index = Stack.Node()->GetPropertyByName(STR("PaintCanIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());
                
            // Set BP output value
            FProperty* outProperty = Stack.Node()->GetPropertyByName(L"Unlocked");
            void* outPropertyAddress = BPSharing::FindOutParamValueAddress(Stack, outProperty);
            *static_cast<bool*>(outPropertyAddress) = apData.allReceivedItems.paintCans[*index].unlocked;
        }
        else if (Stack.Node()->GetNamePrivate() == IsUnlockedEggByIndexCpp)
        {
            Output::send<LogLevel::Verbose>(STR("IsUnlockedEggByIndexCpp\n"));

            int32_t* index = Stack.Node()->GetPropertyByName(STR("EggIndex"))->ContainerPtrToValuePtr<int32_t>(Stack.Locals());

            // EggIndex must be [19;20;21] respectively for [Green;Blue;Red], see ItemReceivedCallback() in APManager.cpp
            if (*index < 19 && *index > 21)
            {
                // Exit early if the range of EggIndex is not respected
                Output::send<LogLevel::Error>(STR("EggIndex out of range\n"));
                return;
            }

            // Set BP output value
            FProperty* outProperty = Stack.Node()->GetPropertyByName(L"Unlocked");
            void* outPropertyAddress = BPSharing::FindOutParamValueAddress(Stack, outProperty);
            *static_cast<bool*>(outPropertyAddress) = APManager::CheckEggByIndex(*index);
        }
        else if (Stack.Node()->GetNamePrivate() == SendDeathLinkCpp)
        {
            Output::send<LogLevel::Verbose>(STR("SendDeathLinkCpp\n"));

            AP_DeathLinkSend();
        }
        else if (Stack.Node()->GetNamePrivate() == CheckPendingAPOptionsCpp)
        {
            Output::send<LogLevel::Verbose>(STR("CheckPendingAPOptionsCpp\n"));

            // Set BP output value
            FProperty* outProperty = Stack.Node()->GetPropertyByName(L"APOptions");
            void* outPropertyAddress = BPSharing::FindOutParamValueAddress(Stack, outProperty);
            *static_cast<TArray<bool>*>(outPropertyAddress) = isAPOptionEnabled;
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

            // If the game is restarted and connected to AP, get all IDs to recover received items
            if (isNewGame && apData.authenticated)
            {
                if (GetAllItemAmountsEvent == NULL)
                {
                    Output::send<LogLevel::Error>(STR("GetAllItemAmounts not found\n"));
                    return;
                }

                apData.pendingItemIDs.Empty(); // All items will be retrieved, meaning no item will be pending
                ItemManager->ProcessEvent(GetAllItemAmountsEvent, &apData.allReceivedItems);
                isNewGame = false;
            }
        }
    }
}
