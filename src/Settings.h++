#pragma once

#include <fstream>

#include "nlohmann/json.hpp"
#include <iostream>


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

        enum class BuySoulTicketsAmount
        {
            FIVE,
            TWENTY_FIVE,
            FIFTY
        };

        static inline std::atomic<float> automatorUpdateDelayInSeconds{1.0f};
        static inline std::atomic<bool> useStatsBoost{true};
        static inline std::atomic<bool> automaticallySellCharactersIfMaximumCapacityReached{true};
        static inline std::atomic<SellRarity> sellRarity{SellRarity::THREE_STARS_OR_LOWER};
        static inline std::atomic<SellLevel> sellLevel{SellLevel::ALL};
        static inline std::atomic<SellBadge> sellBadge{SellBadge::ONLY};
        static inline std::atomic<BuySoulTicketsAmount> buySoulTicketsAmount{BuySoulTicketsAmount::TWENTY_FIVE};
        static inline std::array<int, 10> dailyTeam{};


        static nlohmann::json ToJson()
        {
            nlohmann::json json;

            json["automatorUpdateDelayInSeconds"] = automatorUpdateDelayInSeconds.load();
            json["useStatsBoost"] = useStatsBoost.load();
            json["automaticallySellCharactersIfMaximumCapacityReached"] =
                    automaticallySellCharactersIfMaximumCapacityReached.load();
            json["sellRarity"] = sellRarity.load();
            json["sellLevel"] = sellLevel.load();
            json["sellBadge"] = sellBadge.load();
            json["buySoulTicketsAmount"] = buySoulTicketsAmount.load();
            json["dailyTeam"] = dailyTeam;

            return json;
        }

        static void FromJson(const nlohmann::json& json)
        {
            if (json.empty()) return;

            automatorUpdateDelayInSeconds.store(json.value("automatorUpdateDelayInSeconds",
                                                           automatorUpdateDelayInSeconds.load()));

            useStatsBoost.store(json.value("useStatsBoost", useStatsBoost.load()));

            automaticallySellCharactersIfMaximumCapacityReached.store(json.value(
                "automaticallySellCharactersIfMaximumCapacityReached",
                automaticallySellCharactersIfMaximumCapacityReached.load()));

            sellRarity.store(static_cast<SellRarity>(
                json.value("sellRarity", static_cast<int>(sellRarity.load()))));

            sellLevel.store(static_cast<SellLevel>(
                json.value("sellLevel", static_cast<int>(sellLevel.load()))));

            sellBadge.store(static_cast<SellBadge>(
                json.value("sellBadge", static_cast<int>(sellBadge.load()))));

            buySoulTicketsAmount.store(static_cast<BuySoulTicketsAmount>(
                json.value("buySoulTicketsAmount", static_cast<int>(buySoulTicketsAmount.load()))));

            dailyTeam = json.value("dailyTeam", dailyTeam);
        }

        static void Save()
        {
            try
            {
                std::filesystem::path path(relativeFilePath);
                while (path.has_parent_path() && !std::filesystem::exists(path.parent_path()))
                {
                    path = path.parent_path();
                    std::filesystem::create_directories(path);
                }

                std::ofstream file(relativeFilePath);
                if (!file.is_open())
                {
                    throw std::runtime_error(std::format("Settings::Save could not open file"));
                }

                file << ToJson();
                std::cout << "Settings::Save complete" << std::endl;
            }
            catch (const std::exception& e)
            {
                throw std::runtime_error(std::format("Settings::Save failed: \n{}", e.what()));
            }
        }

        static void Load()
        {
            // The file is not created, we need to save it first to create the default settings file.
            if (!std::filesystem::exists(relativeFilePath))
            {
                Save();
                return;
            }

            try
            {
                std::ifstream file(relativeFilePath);
                if (!file.is_open())
                {
                    throw std::runtime_error(std::format("Settings::Load could not open file"));
                }

                nlohmann::json json;
                file >> json;

                FromJson(json);
                std::cout << "Settings::Load complete" << std::endl;
            }
            catch (const std::exception& e)
            {
                throw std::runtime_error(std::format("Settings::Load failed: \n{}", e.what()));
            }
        }

    private:
        static const inline std::string relativeFilePath = "config/settings.json";
};
