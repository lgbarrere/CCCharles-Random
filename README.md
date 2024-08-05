# CCCharles-Random
This project is a randomizer mod for Choo-Choo Charles that works with the multi-game multi-world randomizer [Archipelago](https://archipelago.gg/).
The development of this randomizer is currently in progress and actively updated.
This documentation can be updated at any moment, as the project is currently under complete reorganization.
The randomization logic is not yet available, however several useful test modules have been implemented to facilitate the development.

## Recommendations
For a better understanding of how to setup this project, some paths in this documentation are replaced by keywords as follows and should be known :
* **\<ProjectFolder\>** is the path to this project once it is downloaded, for instance **D:/UEProject/CCCharles-Random/**
* **\<GameFolder\>** is the path to folder containing all the files necessary to launch the game, for instance **D:/Program Files (x86)/Steam/steamapps/common/Choo-Choo Charles/**

### Mod Installation for testing purposes
**There is currently no release** on this Mod. However a test of the current functionalities can be done by cloning this project and by copying all the content from **result/** in \<GameFolder\>/Obscure/Binaries/Win64/

**/!\ TODO** : Update the documentation and project for the LogicMod (pakfile).

### Mod installation for development
#### Project Architecture
Before setting this project up for development, it is highly recommended to know how this project is structured.
1. **ModSrc** : Contains all the C++ dependencies of the Mod, including
* [**APCpp**](https://github.com/N00byKing/APCpp) which is used to establish a connection between the game and Archipelago.
* [**RE-UE4SS**](https://github.com/UE4SS-RE/RE-UE4SS) which contains all necessary tools to inject the C++ code as Mod in the game
* **RandomizerMod** which is the folder containing all the C++ source files to convert to DLLs and to inject as Mod in the game
2. **Obscure** which is the folder containing all the Blueprint files to inject as Mod in the game. Only the **Content** folder should be modified to Mod the game properly
3. **result** is the folder containing all the elements to copy in the \<GameFolder\> in order to setup and automatically activate the Mod.

#### Requirements
1. [Unreal Engine](https://www.unrealengine.com/en-US/download) at version 4.26.2
2. A legal copy of the Choo-Choo Charles original game (can be found on [Steam](https://store.steampowered.com/))
3. Clone this project. **IMPORTANT** : to build this project, a short path should be used to avoid the max windows path limit to be reached during the compilation (try to not exceed a length of 50 char). Then do the following commands (don't forget to replace \<ProjectFolder\> by your own path)
```
cd '\<ProjectFolder\>\ModSrc\RE-UE4SS\'
git submodule update --init --recursive
cd ..\APCpp\
git submodule update --init --recursive
```

#### How to use and build the project
##### Packaging a Blueprint
1. If there is no folder named "PackagedMod" in \<RootProjectFolder\>/Obscure/, create it (will contain the packaged Blueprints with UE4)
2. Open the "Obscure.uproject" file in \<RootProjectFolder\>/Obscure/ to launch the project with UE4 or locate it manually through UE4
3. Edit the Blueprints as you want to Mod things
4. Package the project with `File \> Package Project \> Windows (64-bits)` and prefer \<RootProjectFolder\>/Obscure/PackagedMod/ as result folder
##### Building the C++
Go to your \<ProjectFolder\>, for instance ``cd 'D:\UEProject\CCCharles-Random\ModSrc\'`` and execute the following commands to compile in order :
```
xmake f -m "Game__Shipping__Win64"
xmake
```

##### Injection of the Mod in the game
The script launchCCCmod.bat has been made to facilitate the injection.
It should be updated with your own paths corresponding to your project and game setups.

**/!\ TODO** : Section to update.

### Known Issues
**/!\ TODO** : Section to update.

### Planned updates
**/!\ TODO** : Section to update.
