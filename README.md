# CCCharles-Random
This project is a randomizer mod for Choo-Choo Charles that works with the multi-game multi-world randomizer [Archipelago](https://archipelago.gg/).
The development of this randomizer is currently in progress and actively updated.
The game is considered playable, however it is an alpha version and it is not yet released on Archipelago.
Several useful test modules have been implemented to facilitate the development.
The currently used UE4SS version UE4SS_v3.0.1-98-g5c1bfc4.zip comes from [the experimental RE-UE4SS](https://github.com/UE4SS-RE/RE-UE4SS/releases/tag/experimental).

## Current features
All items from missions and items on the ground (mainly scraps) are randomized by Mod Blueprints.
The randomization logic is a work in progress, no randomization option is available for the moment.
APCpp is used with C++ to send a checked location to the Archipelago server or to receive items from any world.
A consolidation of the code is in progress.
For developpers, a **Mod Debug Tool** is available to make the modding easier to develop, an Overlay has been added and can be displayed by pressing "F1" while playing.
The Overlay gives a list of useful shortcuts to test newly added features (speed boost, teleportation, item swap, ...).

## Recommendations
> [!TIP]
> For a better understanding of how to setup this project, some paths in this documentation are replaced by keywords as follows and should be known :
* **\<ProjectFolder\>** is the path to this project once it is downloaded, for instance **D:/UEProject/CCCharles-Random/**
* **\<GameFolder\>** is the path to folder containing all the files necessary to launch the game, for instance **D:/Program Files (x86)/Steam/steamapps/common/Choo-Choo Charles/**

## Mod Installation for playing
### Setup the game
The releases of this game are currently unofficial. However, the Mod can be installed and played by following these instructions :
1. Click the green "<> Code" button
2. Click "Download ZIP" or clone this project.
3. In **Release/**, copy the **Obscure/** folder to **\<GameFolder\>** (where the **Obscure/** folder and **Obscure.exe** are placed)
4. Launch the game, if "OFFLINE" is written at the upper-right corner of the screen, the Mod is working
> [!NOTE]
> The content from the **Release/** folder can by manually placed while the paths to files are respected.

### Host the game
See **Setup the game** section to have the **Release/** folder downloaded.

In this section, **Archipelago/** refers to the path where Archipelago is installed locally.

Follow these steps to host a remote multiplayer or a local singleplayer session :
1. Double-click the **cccharles.apworld** in **Release/** to automatically install the world randomization logic
2. Put the **CCCharles.yaml** from **Release/** to **Archipelago/Players/** with the yaml of each player to host
3. Launch the Archipelago launcher and click "Generate" to setup a game with the yaml in **Archipelago/ouput/**
4. For a multiplayer session, go to [the Archipelago HOST GAME page](https://archipelago.gg/uploads)
5. Click "Upload File" and select the generated **AP_\<seed\>.zip** in **Archipelago/output/**
6. Send the generated room page to each player
> [!TIP]
> For a local singleplayer session, click "Host" in the Archipelago launcher by using the generated AP_<seed>.zip in **Archipelago/output/**

## Connection to the Archipelago server room
> [!NOTE]
> Before playing, it is highly recommended to check out the **Known Issues** section
* The game console must be opened to type Archipelago commands, press "`" (or "~") key in querty and "²" key in azerty
* Type ``/connect <IP> <PlayerName>`` with \<IP\> and \<PlayerName\> found on the hosting Archipelago web page in the form ``archipelago.gg:XXXXX`` and ``CCCharles``
* Disconnection is automatic at game closure but can be manually done with ``/disconnect``

## Mod installation for development
### Project Architecture
> [!TIP]
> Before setting this project up for development, it is highly recommended to know how this project is structured.
1. **ModSrc** : Contains all the C++ dependencies of the Mod, including
* [**APCpp**](https://github.com/N00byKing/APCpp) which is used to establish a connection between the game and Archipelago.
* [**RE-UE4SS**](https://github.com/UE4SS-RE/RE-UE4SS) which contains all necessary tools to inject the C++ code as Mod in the game
* **RandomizerMod** which is the folder containing all the C++ source files to convert to DLLs and to inject as Mod in the game
2. **Obscure** which is the folder containing all the Blueprint files to inject as Mod in the game. Only the **Content** folder should be modified to Mod the game properly
3. **Release** is the folder containing all the elements to copy in the \<GameFolder\> in order to setup and automatically activate the Mod (see **Mod Installation for playing** for details). The **prepareRelease.bat** script can be launched to prepare a new release version of the Mod.
> [!IMPORTANT]
> This script should be updated with your own paths corresponding to your project and game setups.
> Follow the comments in this script to fill it properly. Moreover, it is recommended to execute **launchCCCmod.bat** first to make the last built Mod as release.

### Requirements
This section is inspired by the [UE4SS Documentation](https://docs.ue4ss.com/dev/index.html), check it out for details.
If needed, link the Github account to the Epic Game account and [setup the ssh key](https://www.youtube.com/watch?v=X40b9x9BFGo).
1. A computer running Windows
2. [Microsoft Visual Studio Community](https://visualstudio.microsoft.com/fr/vs/community/) 2019 (prefer recent versions) or 2022
3. [Rust](https://www.rust-lang.org/tools/install) >= 1.73.0
4. [xmake](https://xmake.io/#/) >= 2.9.3
5. [cmake](https://cmake.org/download/) recent versions prefered
6. [Unreal Engine](https://www.unrealengine.com/en-US/download) exactly at version 4.26.2
7. A legal copy of the Choo-Choo Charles original game (can be found on [Steam](https://store.steampowered.com/))
8. Clone this project with ``git clone https://github.com/lgbarrere/CCCharles-Random.git``

> [!CAUTION]
> For unknown reason, updating Microsoft Visual Studio Community 2022 to a recent version can cause build errors.
> This can be fixed by using the following known working tools or by manually installing the Microsoft Visual Studio Community 2022 at the version **17.10.5** :
```
Rust version 1.79.0
Microsoft C/C++ Compiler (x64) version 19.40.33815
Microsoft C/C++ Compiler Toolset version 14.40.33807
```

> [!WARNING]
> To build this project, a short path should be used to avoid the [Maximum Path Length Limitation](https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=registry) to be reached during the compilation (try to not exceed a length of 50 char for the project path).

Then do the following commands (don't forget to replace \<ProjectFolder\> by your own path) :
```
cd '<ProjectFolder>/ModSrc/RE-UE4SS/'
git submodule update --init --recursive
cd ../APCpp/
git submodule update --init --recursive
```

### How to use and build the project
#### Packaging a Blueprint
1. If there is no folder named "PackagedMod" in \<RootProjectFolder\>/Obscure/, create it : this folder will contain the packaged Blueprints with UE4
2. Open the "Obscure.uproject" file in \<RootProjectFolder\>/Obscure/ to launch the project with UE4 or locate it manually through UE4
3. Edit the Blueprints as you want to Mod things
4. Package the project with `File > Package Project > Windows (64-bits)` and prefer \<RootProjectFolder\>/Obscure/PackagedMod/ as result folder
#### Building the C++
1. Make sure to copy :
``<ProjectFolder>/archives/APCpp build patch/CMakeLists.txt``
In :
``<ProjectFolder>/ModSrc/APCpp`` (replace the existing CMakeLists.txt in any)
2. Go to your \<ProjectFolder\>, for instance ``cd 'D:/UEProject/CCCharles-Random/ModSrc/'`` and execute the following commands to compile in order :
```
xmake f -m "Game__Shipping__Win64"
xmake
```
> [!NOTE]
> If asked while building, press "y" in the console, then "enter".

#### Injection of the Mod in the game
The **launchCCCmod.bat** script has been made to facilitate the injection of the built C++ and Blueprints.
> [!IMPORTANT]
> This script should be updated with your own paths corresponding to your project and game setups.
> Follow the comments in this script to fill it properly.

## Planned updates
* See "todo.txt" for details

## Known Issues
### Major issues
* When an item is received while in loading screen, a crash sometimes occurrs. That bug does not break the game and a restart is sufficient, but it is recommended to connect after the game is started.
* If the player receives the **Box of Rockets**, the bunker at the **Training Explosive** region will be opened once loaded. It may be possible to break the mission state if the player interacts with elements in unexpected order.
* After game reset, mission states are not restored when the player had received the end item. There is currently no fix on that bug, ``/hint_location <Player> <Location>`` should be used in this case on the hosted Archipelago web page (or in the local console if played locally).

### Minor issues
* Only affects mod developers, the Overlay makes the viewport be unfocused when clicked. When this happens, press "F1" again to hide the Overlay and click again to get the focus back to normal.
* Sometimes, the unlocked weapons can look a bit "glitchy" or have a wrong color, the issue is only visual and does not affect the gameplay
* When the game is reloaded, an egg can sometimes be duplicated.
* The current version of the command parser does not accept console commands with a player names containing whitespaces. It is recommended to use underscores "_" instead, for instance : CCCharles_Player_1.
* Sometimes, an item reception or sending a location can fail (rare cases). Reloading the game is supposed to respawn all items on the ground and restarting a new game retrieves all unlocked items from Archipelago, that can be used as workarounds.
* When an egg is received, if the player goes to one of the three mine exits before talking to the NPC who gives its entry key, the player will no longer be able to interact with this NPC. Make sure to talk to them before approaching their respective mines. Restart a new game otherwise.
