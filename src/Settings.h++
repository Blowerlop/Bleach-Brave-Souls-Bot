#pragma once


class Settings
{
    public:
        static inline std::atomic<float> automatorUpdateDelayInSeconds{1.0f};
        static inline std::atomic<bool> useStatsBoost{true};
};
