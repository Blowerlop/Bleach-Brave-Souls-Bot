#include "SellCharactersAutomator.h++"

#include "../Settings.h++"

bool SellCharactersAutomator::HasSell() const
{
    return hasSell;
}

void SellCharactersAutomator::RunSequence(boost::coroutines2::coroutine<void>::push_type& yield)
{
    cv::Point coordinate;
    const std::string assetsPath = "assets/Inventory/Characters/Sell/";

    if (!DoesScreenshotMatchTemplate(assetsPath + "CharacterList.jpg", coordinate)) yield();
    PointAndClick(coordinate);

    while (!DoesScreenshotMatchTemplate(assetsPath + "Sell.jpg", coordinate)) yield();
    PointAndClick(coordinate);

    while (!DoesScreenshotMatchTemplate(assetsPath + "MultiSelect.jpg", coordinate)) yield();
    PointAndClick(coordinate);

    while (!DoesScreenshotMatchTemplate(assetsPath + "Reset.jpg", coordinate)) yield();
    PointAndClick(coordinate);
    yield();

    switch (Settings::sellRarity.load())
    {
        case Settings::SellRarity::ONE_STARS_ONLY:
            DoesScreenshotMatchTemplate(assetsPath + "RarityOneStarsOnly.jpg", coordinate);
            break;
        case Settings::SellRarity::TWO_STARS_OR_LOWER:
            DoesScreenshotMatchTemplate(assetsPath + "RarityTwoStarsOrLower.jpg", coordinate);
            break;
        case Settings::SellRarity::THREE_STARS_OR_LOWER:
            DoesScreenshotMatchTemplate(assetsPath + "RarityThreeStarsOrLower.jpg", coordinate);
            break;
        case Settings::SellRarity::FOUR_STARS_OR_LOWER:
            DoesScreenshotMatchTemplate(assetsPath + "RarityFourStarsOrLower.jpg", coordinate);
            break;
        case Settings::SellRarity::FIVE_STARS_OR_LOWER:
            DoesScreenshotMatchTemplate(assetsPath + "RarityFiveStarsOrLower.jpg", coordinate);
            break;

        default:
            break;
    }
    PointAndClick(coordinate);

    switch (Settings::sellLevel.load())
    {
        case Settings::SellLevel::ONE_ONLY:
            DoesScreenshotMatchTemplate(assetsPath + "LevelOneOnly.jpg", coordinate);
            break;

        case Settings::SellLevel::ALL:
            DoesScreenshotMatchTemplate(assetsPath + "LevelAll.jpg", coordinate);
            break;
    }
    PointAndClick(coordinate);

    switch (Settings::sellBadge.load())
    {
        case Settings::SellBadge::ONLY:
            DoesScreenshotMatchTemplate(assetsPath + "BadgeOnly.jpg", coordinate);
            break;

        case Settings::SellBadge::ALL:
            DoesScreenshotMatchTemplate(assetsPath + "BadgeAll.jpg", coordinate);
            break;
    }
    PointAndClick(coordinate);

    DoesScreenshotMatchTemplate(assetsPath + "Select.jpg", coordinate);
    PointAndClick(coordinate);

    while (!DoesScreenshotMatchTemplate(assetsPath + "Sell2.jpg", coordinate)) yield();
    PointAndClick(coordinate);

    while (!DoesScreenshotMatchTemplate(assetsPath + "Ok.jpg", coordinate)) yield();
    PointAndClick(coordinate);

    while (!DoesScreenshotMatchTemplate(assetsPath + "Select.jpg", coordinate)) yield();
    PointAndClick(coordinate);
    yield();

    hasSell.store(true);
}

void SellCharactersAutomator::Update(const std::stop_token& stopToken)
{
    Automator::Update(stopToken);

    if (!sequence)
    {
        sequence.emplace([this](boost::coroutines2::coroutine<void>::push_type& yield) { RunSequence(yield); });
    }
    else if (*sequence) (*sequence)();
}
