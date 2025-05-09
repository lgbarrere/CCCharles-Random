:: This script must be launched to prepare a new release version of the game by :
:: 1) Copying the packed mod file with the randomization logic
:: 2) Copying the DLL file linking Archipelago
:: It is recommended to execute launchCCCmod.bat first to enable the last version of the Mod as release

:: The following paths must be updated according to the each developer setup
set "ReleaseFolder=D:\UEProject\CCCharles-Random\Release"
set "GameFolder=D:\Program Files (x86)\Steam\steamapps\common\Choo-Choo Charles"

:: Inject the packaged Logic Mod
xcopy /Y "%GameFolder%\Obscure\Content\Paks\LogicMods\MWRandomizerMod.pak" "%ReleaseFolder%\Obscure\Content\Paks\LogicMods\"

:: Inject the C++ DLL Mod
xcopy /Y "%GameFolder%\Obscure\Binaries\Win64\ue4ss\Mods\RandomizerMod\dlls\main.dll" "%ReleaseFolder%\Obscure\Binaries\Win64\ue4ss\Mods\RandomizerMod\dlls\"
