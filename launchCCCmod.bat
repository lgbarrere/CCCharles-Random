:: This script is responsible of the Mod injection to the game by :
:: 1) Copying the last built files of mod in the game folder
:: 2) Remove the previously built files
:: 3) Rename the newly built files to activate them
:: 4) Start the game with the Mod enabled
:: The packaging and compilation must have been launched before executing this script to enable the Mod

:: The following paths must be updated according to the each developer setup
set "ProjectFolder=D:\UEProject\CCCharles-Random\"
set "GameFolder=D:\Program Files (x86)\Steam\steamapps\common\Choo-Choo Charles\"

:: Inject the packaged Logic Mod
xcopy /Y "%ProjectFolder%Obscure\PackagedMod\WindowsNoEditor\Obscure\Content\Paks\pakchunk1-WindowsNoEditor.pak" "%GameFolder%Obscure\Content\Paks\LogicMods\"
del "%GameFolder%Obscure\Content\Paks\LogicMods\MWRandomizerMod.pak"
ren "%GameFolder%Obscure\Content\Paks\LogicMods\pakchunk1-WindowsNoEditor.pak" "MWRandomizerMod.pak"

:: The following line can be uncommented to overwrite original content of the game
@REM xcopy /Y "%ProjectFolder%Obscure\PackagedMod\WindowsNoEditor\Obscure\Content\Paks\pakchunk2-WindowsNoEditor.pak" "%GameFolder%Obscure\Content\Paks\mods\"
@REM del "%GameFolder%Obscure\Content\Paks\mods\OverwriteGameContent_P.pak"
@REM ren "%GameFolder%Obscure\Content\Paks\mods\pakchunk2-WindowsNoEditor.pak" "OverwriteGameContent_P.pak"

:: Inject the C++ DLL Mod
xcopy /Y "%ProjectFolder%ModSrc\Binaries\Game__Shipping__Win64\RandomizerMod\RandomizerMod.dll" "%GameFolder%Obscure\Binaries\Win64\ue4ss\Mods\RandomizerMod\dlls\"
del "%GameFolder%Obscure\Binaries\Win64\ue4ss\Mods\RandomizerMod\dlls\main.dll"
ren "%GameFolder%Obscure\Binaries\Win64\ue4ss\Mods\RandomizerMod\dlls\RandomizerMod.dll" "main.dll"

:: Start the game
start "" "%GameFolder%Obscure.exe"

