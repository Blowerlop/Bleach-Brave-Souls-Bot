#pragma once


class Settings
{
    public:
        enum class SellRarity
        {
            ONE_STARS_ONLY,
            TWO_STARS_OR_LOWER,
            THREE_STARS_OR_LOWER,
            FOUR_STARS_OR_LOWER,
            FIVE_STARS_OR_LOWER,
        };

        enum class SellLevel
        {
            ONE_ONLY,
            ALL
        };

        enum class SellBadge
        {
            ONLY,
            ALL
        };

        static inline std::atomic<float> automatorUpdateDelayInSeconds{1.0f};
        static inline std::atomic<bool> useStatsBoost{true};
        static inline std::atomic<bool> automaticallySellCharactersIfMaximumCapacityReached{true};
        static inline std::atomic<SellRarity> sellRarity{SellRarity::THREE_STARS_OR_LOWER};
        static inline std::atomic<SellLevel> sellLevel{SellLevel::ALL};
        static inline std::atomic<SellBadge> sellBadge{SellBadge::ONLY};

};
