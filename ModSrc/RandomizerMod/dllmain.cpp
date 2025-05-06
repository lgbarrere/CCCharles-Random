#include <Mod/CppUserModBase.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/FProperty.hpp>

#include "Archipelago.h"
#include "ModConsole.hpp"

using namespace RC;
using namespace RC::Unreal;

UFunction* AuthenticatedEvent = NULL;
UFunction* ArchipelagoMessageEvent = NULL;
UFunction* LostConnectionEvent = NULL;

class RandomizerMod : public RC::CppUserModBase
{
public:
    RandomizerMod() : CppUserModBase()
    {
        ModName = STR("RandomizerMod");
        ModVersion = STR("0.0.1");
        ModDescription = STR("Choo-Choo Charles randomizer");
        ModAuthors = STR("Yaranorgoth");
        // Do not change this unless you want to target a UE4SS version
        // other than the one you're currently building with somehow.
        //ModIntendedSDKVersion = STR("2.6");

        Output::send<LogLevel::Verbose>(STR("Mod name : {}\n"), ModName);
        Output::send<LogLevel::Verbose>(STR("Version : {}\n"), ModVersion);
        Output::send<LogLevel::Verbose>(STR("{}\n"), ModDescription);
        Output::send<LogLevel::Verbose>(STR("Author : {}\n"), ModAuthors);
    }

    ~RandomizerMod() override
    {
    }

    /*
    * TODO : Starting Dataloader implementation, to adapt in Mod context
    FString LoadFileToString(FString filename)
    {
        FString folder = FPaths::GameContentDir();
        FString result;
        IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

        if (file.CreateDirectory(*folder))
        {
            FString saveFile = folder + "/" + filename;
            FFileHelper::LoadFileToString(result, *saveFile);
        }

        return result;
    }
    */

    static auto CallbackFunctionHook([[maybe_unused]] Unreal::UObject* Context, Unreal::FFrame& Stack, [[maybe_unused]] void* RESULT_DECL) -> void
    {
        // Set the hooked functions/events names once
        static auto SendLocationIDHook = FName(STR("SendLocationID"), FNAME_Add); // Send locationID to Archipelago
        static auto GameReloadedHook = FName(STR("GameReloaded"), FNAME_Add); // The game was reloaded, reset gameReload
        static auto CharlesDeathHook = FName(STR("CharlesDeath"), FNAME_Add); // Function from the game called if Charles died

        // Check the hooked function/event names are correct
        if (Stack.Node()->GetNamePrivate() == SendLocationIDHook)
        {
            // If the Archipelago connection is not established yet, exit early
            if (AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
            {
                Output::send<LogLevel::Verbose>(STR("The player is not authenticated yet\n"));
                return;
            }

            Output::send<LogLevel::Verbose>(STR("SendLocationIDHook\n"));
            // Get the parameters in order
            int64_t* locationID = Stack.Node()->GetPropertyByName(STR("locationID"))->ContainerPtrToValuePtr<int64_t>(Stack.Locals());
            Output::send<LogLevel::Verbose>(STR("{}\n"), *locationID);

            // If the ID is -1, no item was found, exit early
            if (*locationID == -1)
            {
                Output::send<LogLevel::Error>(STR("Item not found : locationID == -1\n"));
                return;
            }

            AP_SendItem(*locationID);
        }
        else if (Stack.Node()->GetNamePrivate() == GameReloadedHook)
        {
            gameReload = true;
            ItemManager = NULL;
            AuthenticatedEvent = NULL;
            ArchipelagoMessageEvent = NULL;
            LostConnectionEvent = NULL;
            ItemReceivedEvent = NULL;
        }
        else if (Stack.Node()->GetNamePrivate() == CharlesDeathHook)
        {
            AP_StoryComplete();
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
        // Send the game seed at first authentication
        AP_ConnectionStatus connectionStatus = AP_GetConnectionStatus();
        if (gameReload && connectionStatus == AP_ConnectionStatus::Authenticated)
        {
            // Get ItemManager reference if not done, leave the function if it cannot be found
            if (!ItemManager) {
                ItemManager = UObjectGlobals::FindFirstOf(STR("ItemManager_C"));
                if (!ItemManager) {
                    Output::send<LogLevel::Error>(STR("ItemManager not found\n"));
                    return;
                }
            }

            // Get Authenticated event reference (to add itemID to inventory) if not done, leave the function if it cannot be found
            static auto Authenticated = FName(STR("Authenticated"), FNAME_Add);
            if (!AuthenticatedEvent)
            {
                AuthenticatedEvent = ItemManager->GetFunctionByName(Authenticated);
                if (!AuthenticatedEvent)
                {
                    Output::send<LogLevel::Error>(STR("Authenticated not found\n"));
                    return;
                }
            }

            gameReload = false;

            AP_RoomInfo roomInfo;
            AP_GetRoomInfo(&roomInfo);
            FString seed = FString(to_wstring(roomInfo.seed_name).c_str());
            ItemManager->ProcessEvent(AuthenticatedEvent, &seed);
        }
        // Otherwise, if disconnected, reset gameReload to send the seed once re-authenticated
        else if (!gameReload && connectionStatus != AP_ConnectionStatus::Authenticated)
        {
            gameReload = true;

            static auto LostConnection = FName(STR("LostConnection"), FNAME_Add);
            if (!LostConnectionEvent)
            {
                if (ItemManager)
                {
                    LostConnectionEvent = ItemManager->GetFunctionByName(LostConnection);
                    if (!LostConnectionEvent)
                    {
                        Output::send<LogLevel::Error>(STR("Connection not found\n"));
                        return;
                    }
                }
            }
            
            if (ItemManager)
            {
                ItemManager->ProcessEvent(LostConnectionEvent, NULL);
            }
        }
        else if (connectionStatus == AP_ConnectionStatus::Authenticated)
        {
            //Output::send<LogLevel::Verbose>(STR("Checking pending message...\n"));
            if (AP_IsMessagePending())
            {
                //Output::send<LogLevel::Verbose>(STR("Pending message found\n"));
                static auto ArchipelagoMessage = FName(STR("ArchipelagoMessage"), FNAME_Add);
                if (!ArchipelagoMessageEvent)
                {
                    ArchipelagoMessageEvent = ItemManager->GetFunctionByName(ArchipelagoMessage);
                    if (!ArchipelagoMessageEvent)
                    {
                        Output::send<LogLevel::Error>(STR("ArchipelagoMessage not found\n"));
                        return;
                    }
                }

                if (ItemManager)
                {
                    FString message = FString(to_wstring(AP_GetLatestMessage()->text).c_str());
                    //Output::send<LogLevel::Verbose>(STR("{}\n"), to_wstring(AP_GetLatestMessage()->text).c_str());
                    // Bug here due to game restart making ItemManager a wrong reference
                    //ItemManager->ProcessEvent(ArchipelagoMessageEvent, &message);
                }
            }
        }
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
