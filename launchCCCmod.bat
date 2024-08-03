:: This script copies the last packaged/built mod in the game folder, then start the game
:: The packaging and compilation must be launched once before executing this script to enable the Mod 

:: Inject the packaged Logic Mod
xcopy /Y "D:\UEProject\CCCharles-Random\Obscure\PackagedMod\WindowsNoEditor\Obscure\Content\Paks\pakchunk1-WindowsNoEditor.pak" "D:\Program Files (x86)\Steam\steamapps\common\Choo-Choo Charles\Obscure\Content\Paks\LogicMods"

del "D:\Program Files (x86)\Steam\steamapps\common\Choo-Choo Charles\Obscure\Content\Paks\LogicMods\TesterMod.pak"

ren "D:\Program Files (x86)\Steam\steamapps\common\Choo-Choo Charles\Obscure\Content\Paks\LogicMods\pakchunk1-WindowsNoEditor.pak" "TesterMod.pak"

:: Inject the C++ DLL Mod
xcopy /Y "D:\UEProject\CCCharles-Random\ModSrc\Binaries\Game__Shipping__Win64\RandomizerMod\RandomizerMod.dll" "D:\Program Files (x86)\Steam\steamapps\common\Choo-Choo Charles\Obscure\Binaries\Win64\ue4ss\Mods\RandomizerMod\dlls"

del "D:\Program Files (x86)\Steam\steamapps\common\Choo-Choo Charles\Obscure\Binaries\Win64\ue4ss\Mods\RandomizerMod\dlls\main.dll"

ren "D:\Program Files (x86)\Steam\steamapps\common\Choo-Choo Charles\Obscure\Binaries\Win64\ue4ss\Mods\RandomizerMod\dlls\RandomizerMod.dll" "main.dll"

:: Start the game
start D:\"Program Files (x86)"\Steam\steamapps\common\"Choo-Choo Charles"\Obscure.exe
