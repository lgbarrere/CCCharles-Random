#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/Hooks.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/FProperty.hpp>

/*
#include <Runtime/Core/Public/Misc/Paths.hpp>
#include <Runtime/Core/Public/HAL/PlatformFilemanager.hpp>
*/
#include <Unreal/FString.hpp>
#include <Unreal/BPMacros.hpp>

#include "../APCpp/Archipelago.h"
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
        static auto FuncNameToHook = FName(STR("FuncNameToHook"), FNAME_Add);

        // Check the function name is correct in the callback
        if (Stack.Node()->GetNamePrivate() != FuncNameToHook)
        {
            // Unexpected function, so exit early
            return;
        }
        FString* tmpParam = Stack.Node()->GetPropertyByName(STR("SomeParamHook"))->ContainerPtrToValuePtr<FString>(Stack.Locals());
        int32* tmpParam2 = Stack.Node()->GetPropertyByName(STR("AnotherParamHook"))->ContainerPtrToValuePtr<int32>(Stack.Locals());
        
        Output::send<LogLevel::Verbose>(STR("{}"), tmpParam->GetCharArray());
        Output::send<LogLevel::Verbose>(STR("{}"), *tmpParam2);

        Output::send<LogLevel::Verbose>(STR("FuncNameToHook has been called with success\n"));
    }

    void StartArchipelagoConnexion(const char* ipAddress, const char* gameName, const char* playerName, const char* password)
    {
        // IP example from /connect archipelago.gg:38281 : IP = archipelago.gg:38281
        // AP_Init("", "Choo-Choo charles", "YaranCCC", ""); // Raw values for test
        AP_Init(ipAddress, gameName, playerName, password); // Using variables filled by the user and Archipelago
    }

    auto on_unreal_init() -> void override
    {
        // You are allowed to use the 'Unreal' namespace in this function and anywhere else after this function has fired.
        auto Object = UObjectGlobals::StaticFindObject<UObject*>(nullptr, nullptr, STR("/Script/CoreUObject.Object"));
        Output::send<LogLevel::Verbose>(STR("Object Name: {}\n"), Object->GetFullName());

        Hook::RegisterProcessConsoleExecCallback([&](UObject* object, const Unreal::TCHAR* command, FOutputDevice& Ar, UObject* executor) -> bool
        {
            if (command[0] == '/' || command[0] == '!') {
                command++; // Exclude the first character from the array

                int same = ModConsole::CheckCommand(Ar, command);

                if(same == 1)
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
            // StartArchipelagoConnexion("localhost", "Choo-Choo charles", "YaranCCC", "");
            return false;
        });

        /// TEST OF HOOKS
        if (Unreal::UObject::ProcessLocalScriptFunctionInternal.is_ready() && Unreal::Version::IsAtLeast(4, 22))
        {
            Output::send(STR("Enabling custom events\n"));
            Unreal::Hook::RegisterProcessLocalScriptFunctionPostCallback(CallbackFunctionHook);
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
