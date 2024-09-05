#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/Hooks.hpp>
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

    void StartArchipelagoConnexion(const char* ipAddress, const char* gameName, const char* playerName, const char* password)
    {
        // IP example from /connect archipelago.gg:38281 : IP = archipelago.gg:38281
        // AP_Init("", "Choo-Choo charles", "YaranCCC", "");
        AP_Init(ipAddress, gameName, playerName, password);
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
