#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
/*
#include <Runtime/Core/Public/Misc/Paths.hpp>
#include <Runtime/Core/Public/HAL/PlatformFilemanager.hpp>
*/
#include <Unreal/FString.hpp>
#include <Unreal/BPMacros.hpp>

#include <../APCpp/Archipelago.h>

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
        // IP example from (after /connect archipelago.gg:) 59157
        AP_Init("localhost", "Choo-Choo charles", "YaranCCC", "");
    }

    auto on_unreal_init() -> void override
    {
        // You are allowed to use the 'Unreal' namespace in this function and anywhere else after this function has fired.
        auto Object = UObjectGlobals::StaticFindObject<UObject*>(nullptr, nullptr, STR("/Script/CoreUObject.Object"));
        Output::send<LogLevel::Verbose>(STR("Object Name: {}\n"), Object->GetFullName());
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
