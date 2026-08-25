add_rules("mode.debug", "mode.release")

target("Bleach-Brave-Souls-Bot")
    set_kind("binary")
    add_files("src/*.cpp")
    add_syslinks("user32")