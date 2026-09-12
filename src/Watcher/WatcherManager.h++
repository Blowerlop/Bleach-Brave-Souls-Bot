#pragma once
#include <thread>
#include <vector>
#include <opencv2/core/mat.hpp>

#include "WatcherController.h++"


class WatcherManager
{
    public:
        WatcherManager() = default;
        ~WatcherManager();

        void AddController(WatcherController&& controller);
        void StartRunControllersThread();

    private:
        std::vector<WatcherController> controllers;
        std::jthread thread;
};
