local projectName = "RandomizerMod"

target(projectName)
    add_rules("ue4ss.mod")
    add_includedirs("./")

    add_includedirs("../APCpp/")
    add_includedirs("../APCpp/IXWebSocket/")
    add_includedirs("../APCpp/jsoncpp/include/")
    add_includedirs("../RE-UE4SS/deps/first/Helpers/include/")
    add_files("../APCpp/jsoncpp/src/lib_json/*.cpp")
    add_files("../APCpp/IXWebSocket/ixwebsocket/*.cpp")
    add_files("../APCpp/Archipelago.cpp")
    
    add_includedirs("./include/")
    add_files("src/*.cpp")
    add_files("dllmain.cpp")
