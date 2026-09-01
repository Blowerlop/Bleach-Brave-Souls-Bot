#include "AssetsManager.h++"

#include <opencv2/imgcodecs.hpp>

std::map<std::string, cv::Mat> AssetsManager::cache {};

cv::Mat& AssetsManager::Load(const cv::String &file)
{
    if (const auto it = cache.find(file); it != cache.end())
    {
        return it->second;
    }

    const auto [it, _] = cache.emplace(file, cv::imread(file));
    return it->second;
}
