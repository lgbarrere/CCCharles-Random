
#include <Mod/CppUserModBase.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/FProperty.hpp>

#include "BPSharing.hpp"
#include "APManager.hpp"
#include "ModConsole.hpp"

using namespace RC;
using namespace RC::Unreal;


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
        BPSharing::ManageHook(Stack);
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

        // Initializations
        Hook::RegisterProcessConsoleExecCallback(CallbackConsole);
        APManager::initializeAPInformation();

        // Callback for all hooked functions and events
        if (UObject::ProcessLocalScriptFunctionInternal.is_ready() && Unreal::Version::IsAtLeast(4, 22))
        {
            Output::send(STR("Enabling custom event hooks\n"));
            Hook::RegisterProcessLocalScriptFunctionPostCallback(CallbackFunctionHook);
        }
    }

    auto on_update() -> void override
    {
        BPSharing::SetBPFunctions();
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
