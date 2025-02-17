#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/Hooks.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/UFunctionStructs.hpp>
#include <Unreal/FProperty.hpp>

/*
#include <Runtime/Core/Public/Misc/Paths.hpp>
#include <Runtime/Core/Public/HAL/PlatformFilemanager.hpp>
*/
#include <Unreal/FString.hpp>
#include <Unreal/BPMacros.hpp>

#include "Archipelago.h"
#include "ModConsole.hpp"

using namespace RC;
using namespace RC::Unreal;

class RandomizerMod : public RC::CppUserModBase
{
public:
    RandomizerMod() : CppUserModBase()
    {
        ModName = STR("RandomizerMod");
        ModVersion = STR("1.0");
        ModDescription = STR("Choo-Choo Charles randomizer");
        ModAuthors = STR("Yaranorgoth");
        // Do not change this unless you want to target a UE4SS version
        // other than the one you're currently building with somehow.
        //ModIntendedSDKVersion = STR("2.6");

        Output::send<LogLevel::Verbose>(STR("Mod name : {}\n"), ModName);
        Output::send<LogLevel::Verbose>(STR("Version : {}\n"), ModVersion);
        Output::send<LogLevel::Verbose>(ModDescription);
        Output::send<LogLevel::Verbose>(STR("Author : {}\n"), ModAuthors);
    }

    ~RandomizerMod() override
    {
    }

    static auto CallbackFunctionHook([[maybe_unused]] Unreal::UObject* Context, Unreal::FFrame& Stack, [[maybe_unused]] void* RESULT_DECL) -> void
    {
        // Set the hooked functions/events names once
        static auto QuerySeedHook = FName(STR("QuerySeed"), FNAME_Add); // The Archipelago room seed must be sent in BP with GetGameSeed
        static auto GetGameSeedEvent = FName(STR("GetGameSeed"), FNAME_Add); // Send seed in BP as queried by QuerySeed
        static auto SendLocationIDHook = FName(STR("SendLocationID"), FNAME_Add); // Send locationID to Archipelago

        // Check the hooked function/event names are correct
        if (Stack.Node()->GetNamePrivate() == QuerySeedHook)
        {
            // If the Archipelago connection is not established yet, exit early
            if (AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
            {
                Output::send<LogLevel::Verbose>(STR("The player is not authenticated yet\n"));
                return;
            }

            // The player has interacted with the key of his train, send him the seed of the server room
            AP_RoomInfo roomInfo;
            AP_GetRoomInfo(&roomInfo);
            FString seed = FString(to_wstring(roomInfo.seed_name).c_str());
            Stack.Object()->ProcessEvent(Stack.Object()->GetFunctionByName(GetGameSeedEvent), &seed);
        }
        else if (Stack.Node()->GetNamePrivate() == SendLocationIDHook)
        {
            // If the Archipelago connection is not established yet, exit early
            if (AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
            {
                Output::send<LogLevel::Verbose>(STR("The player is not authenticated yet\n"));
                return;
            }

            Output::send<LogLevel::Verbose>(STR("SendLocationIDHook"));
            // Get the parameters in order
            int64_t* locationID = Stack.Node()->GetPropertyByName(STR("locationID"))->ContainerPtrToValuePtr<int64_t>(Stack.Locals());
            Output::send<LogLevel::Verbose>(STR("{}"), *locationID);

            // If the ID is -1, no item was found, exit early
            if (*locationID == -1)
            {
                Output::send<LogLevel::Error>(STR("Item not found : locationID == -1"));
                return;
            }

            AP_SendItem(*locationID);
        }
    }

    static bool CallbackConsole(UObject* object, const Unreal::TCHAR* command, FOutputDevice& Ar, UObject* executor)
    {
        if (command[0] == '/' || command[0] == '!')
        {
            command++; // Exclude the first character from the array

            int same = ModConsole::CheckCommand(Ar, command);

            if (same == 1)
            {
                Output::send<LogLevel::Verbose>(STR("Command detected with success : {} {}\n"), command, same);
                Output::send<LogLevel::Verbose>(STR("connection accepted !\n"));
            }
            else
            {
                Output::send<LogLevel::Verbose>(STR("Command detected with difference : {} {}\n"), command, same);
            }

            return true;
        }

        Output::send<LogLevel::Verbose>(STR("Command undetected\n"));
        return false;
    }

    auto on_unreal_init() -> void override
    {
        // You are allowed to use the 'Unreal' namespace in this function and anywhere else after this function has fired.
        auto Object = UObjectGlobals::StaticFindObject<UObject*>(nullptr, nullptr, STR("/Script/CoreUObject.Object"));
        Output::send<LogLevel::Verbose>(STR("Object Name: {}\n"), Object->GetFullName());

        Hook::RegisterProcessConsoleExecCallback(CallbackConsole);

        // Callback for all hooked functions and events
        if (UObject::ProcessLocalScriptFunctionInternal.is_ready() && Unreal::Version::IsAtLeast(4, 22))
        {
            Output::send(STR("Enabling custom event hooks\n"));
            Hook::RegisterProcessLocalScriptFunctionPostCallback(CallbackFunctionHook);
        }
    }

    auto on_update() -> void override
    {
    }
};

#define MY_AWESOME_MOD_API __declspec(dllexport)
extern "C"
{
    MY_AWESOME_MOD_API RC::CppUserModBase* start_mod()
    {
        return new RandomizerMod();
    }

    MY_AWESOME_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}
