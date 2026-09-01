#include <filesystem>
#include <iostream>
#include <ostream>

#include "AssetsManager.h++"
#include "Process.h++"
#include "StoryQuest.h++"


void LoadAllAssets()
{
    const std::string path = "assets/";
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() != ".jpg" && entry.path().extension() != ".png") continue;

        AssetsManager::Load(entry.path().string());
    }
}

int main()
{
    LoadAllAssets();

    StoryQuest storyQuest {};
    storyQuest.Start();

    return 0;
}
