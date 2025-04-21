local projectName = "RandomizerMod"

package("APCpp")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "../APCpp"))
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        table.insert(configs, "-DBUNDLED_JSONCPP=ON")
        import("package.tools.cmake").install(package, configs)
    end)
package_end()

add_requires("APCpp")

-- Define the main target for the project
target(projectName)
    -- Add rules for UE4SS mod
    add_rules("ue4ss.mod")

    -- Add APCpp package
    set_kind("binary")
    add_packages("APCpp")

    -- Include directories
    add_includedirs("./", "./include/")
    add_includedirs("../RE-UE4SS/deps/first/Helpers/include/")

    -- Add source files for the project
    add_files("dllmain.cpp", "src/*.cpp")
