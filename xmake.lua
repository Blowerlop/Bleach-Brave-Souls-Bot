add_rules("mode.debug", "mode.release")
add_requires("opencv", "d3d11", "dxgi")

target("Bleach-Brave-Souls-Bot")
    set_kind("binary")
    add_files("src/*.cpp")
    add_syslinks("user32", "d3d11", "dxgi")
    add_packages("opencv")