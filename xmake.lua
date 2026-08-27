add_rules("mode.debug", "mode.release")
add_requires("opencv")

target("Bleach-Brave-Souls-Bot")
    set_kind("binary")
    add_files("src/*.cpp")
    add_syslinks("user32")
    add_packages("opencv")