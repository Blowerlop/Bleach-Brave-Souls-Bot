set_languages("c++23")
add_rules("mode.debug", "mode.release")
add_requires("opencv", "vulkan-loader", "magic_enum", "nlohmann_json")
add_requires("imgui 1.92.9-docking", {configs = {glfw = true, vulkan = true}})
add_requires("boost", {configs = {coroutine = true, signals = true}})

target("Bleach-Brave-Souls-Bot")
    set_kind("binary")
    add_files("src/**.cpp")
    add_syslinks("user32")
    add_packages("opencv", "imgui", "vulkan-loader", "boost", "magic_enum", "nlohmann_json")
    add_defines("NOMINMAX")

    if is_plat("windows") then
            add_ldflags("/SUBSYSTEM:WINDOWS", "/ENTRY:mainCRTStartup", {force = true})
    end

    after_build(function (target)
            local assetDirectory = path.join(target:targetdir(), "assets")
                os.mkdir(assetDirectory)
                os.cp("assets/*", assetDirectory)
    end)