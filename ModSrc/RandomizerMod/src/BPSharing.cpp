#include <Unreal/UFunction.hpp>
#include <Unreal/FProperty.hpp>

#include "BPSharing.hpp"
#include "APManager.hpp"
#include "Archipelago.h"

using namespace RC;
using namespace RC::Unreal;


// The ItemManager Blueprints manages the player inventory when an Archipelago item is received
UObject* ItemManager = NULL;

namespace BPSharing {
    /**
     * @brief Retreive the address of an output parameter of a Blueprint function
     * @param Stack: The reference of the stack containing the function and local parameters
     * @param Param: The address of the parameter to get from the function
     * 
     * @important This function is a duplicate from FFrame.cpp because of linking errors.
     * Adding RC_UE_API before the declaration of this function in FFrame.hpp to export it did not work.
     * @return The address of an output parameter of BP function
     */
    static void* FindOutParamValueAddress(FFrame& Stack, FProperty* Param)
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

            // Send the checked location if its ID is valid
            if (*locationID >= START_LOCATION_ID)
            {
                APManager::SendAPLocation(*locationID);
            }
        }
        else if (Stack.Node()->GetNamePrivate() == GameReloadedCpp)
        {
            Output::send<LogLevel::Verbose>(STR("GameReloadedCpp\n"));

            // BPs are reset when the game reloads, set all references to NULL for further if check not crash the game
            ItemManager = NULL;
            apData.connectionStatus = AP_ConnectionStatus::Disconnected; // BPs variables are reset as well, including AP connection
        }
        else if (Stack.Node()->GetNamePrivate() == CheckPendingAPMessageCpp)
        {
            // No header debug message for hooks called by a looping timer

            if (apData.connectionStatus == AP_ConnectionStatus::Authenticated && AP_IsMessagePending())
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
            *static_cast<TArray<int32_t>*>(outPropertyAddress) = isAPOptionEnabled;
        }
    }

    void BPSharing::SetBPObjects()
    {
        // When the game is reloaded, the ItemManager reference is set to NULL, set it when available
        if (ItemManager == NULL)
        {
            ItemManager = UObjectGlobals::FindFirstOf(STR("BP_ItemManager_C"));
        }
    }
}
