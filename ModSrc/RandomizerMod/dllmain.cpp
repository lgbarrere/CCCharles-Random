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
        ModDescription = STR("Choo-Choo Charles randomizer file loader");
        ModAuthors = STR("Yaranorgoth");
        // Do not change this unless you want to target a UE4SS version
        // other than the one you're currently building with somehow.
        //ModIntendedSDKVersion = STR("2.6");

        Output::send<LogLevel::Verbose>(STR("RandomizerMod says hello\n"));
    }

    ~RandomizerMod() override
    {
    }

    // This function is to rework, to be called in the Blueprints to load a file with all locations
    // TArray<FString> LoadFileToStringArray(FString fileName)
    // {
    //     TArray<FString> result;
    //     FString directory = FPaths::ProjectContentDir();
    //     IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

    //     if (file.CreateDirectory(*directory))
    //     {
    //         FString myFile = directory + "/" + fileName;
    //         FFileHelper::LoadFileToStringArray(result, *myFile);
    //     }

    //     return result;
    // }

    static auto CallbackFunctionHook([[maybe_unused]] Unreal::UObject* Context, Unreal::FFrame& Stack, [[maybe_unused]] void* RESULT_DECL) -> void
    {
        // In the callback, or anywhere else on or after on_unnreal_init.
        static auto FuncNameToHook = FName(STR("FuncNameToHook"), FNAME_Add); // TODO : Temporary for tests, to remove
        static auto SendLocationIDHook = FName(STR("SendLocationID"), FNAME_Add);
        static auto FuncNameToCall = FName(STR("FuncNameToCall"), FNAME_Add);

        // Check the function name is correct in the callback
        if (Stack.Node()->GetNamePrivate() == FuncNameToHook)
        {
            // Get the parameters in order
            FString* tmpParam = Stack.Node()->GetPropertyByName(STR("SomeParamHook"))->ContainerPtrToValuePtr<FString>(Stack.Locals());
            int64_t* tmpParam2 = Stack.Node()->GetPropertyByName(STR("AnotherParamHook"))->ContainerPtrToValuePtr<int64_t>(Stack.Locals());

            Output::send<LogLevel::Verbose>(STR("FuncNameToHook has been called with success\n"));
            Output::send<LogLevel::Verbose>(STR("{}"), tmpParam->GetCharArray());
            Output::send<LogLevel::Verbose>(STR("{}"), *tmpParam2);

            // Call a BP function to pass parameters
            FString itemName = FString(STR("Some_item"));
            AP_SendItem(*tmpParam2);
            Stack.Object()->ProcessEvent(Stack.Object()->GetFunctionByName(FuncNameToCall), &itemName);
        }

        else if (Stack.Node()->GetNamePrivate() == SendLocationIDHook)
        {
            Output::send<LogLevel::Verbose>(STR("SendLocationIDHook"));
            int64_t* locationID = Stack.Node()->GetPropertyByName(STR("locationID"))->ContainerPtrToValuePtr<int64_t>(Stack.Locals());
            Output::send<LogLevel::Verbose>(STR("{}"), *locationID);

            // If the ID is -1, no item was found, exit early
            if (*locationID == -1)
            {
                Output::send<LogLevel::Verbose>(STR("Item not found"));
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

        /// TEST OF HOOKS
        if (UObject::ProcessLocalScriptFunctionInternal.is_ready() && Unreal::Version::IsAtLeast(4, 22))
        {
            Output::send(STR("Enabling custom events\n"));
            Hook::RegisterProcessLocalScriptFunctionPostCallback(CallbackFunctionHook);
            // UObjectGlobals::RegisterHook("FuncNameToHook", NULL, NULL, NULL);
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
