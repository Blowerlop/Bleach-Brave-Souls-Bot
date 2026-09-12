#include "SellCharactersAutomator.h++"

#include "../ApplicationManager.h++"
#include "../Settings.h++"
#include "../TemplateMatching.h++"

void SellCharactersAutomator::Update(boost::coroutines2::coroutine<void>::push_type& yield,
                                     const cv::Mat& gameScreenshot)
{
    Automator::Update(yield, gameScreenshot);

    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;
    const std::string assetsPath = "assets/Inventory/Characters/Sell/";

    if (!TemplateMatching::Match(gameScreenshot, assetsPath + "CharacterList.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "Sell.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "MultiSelect.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "Reset.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);
    yield();

    switch (Settings::sellRarity.load())
    {
        case Settings::SellRarity::ONE_STARS_ONLY:
            TemplateMatching::Match(gameScreenshot, assetsPath + "RarityOneStarsOnly.jpg", coordinate);
            break;
        case Settings::SellRarity::TWO_STARS_OR_LOWER:
            TemplateMatching::Match(gameScreenshot, assetsPath + "RarityTwoStarsOrLower.jpg", coordinate);
            break;
        case Settings::SellRarity::THREE_STARS_OR_LOWER:
            TemplateMatching::Match(gameScreenshot, assetsPath + "RarityThreeStarsOrLower.jpg", coordinate);
            break;
        case Settings::SellRarity::FOUR_STARS_OR_LOWER:
            TemplateMatching::Match(gameScreenshot, assetsPath + "RarityFourStarsOrLower.jpg", coordinate);
            break;
        case Settings::SellRarity::FIVE_STARS_OR_LOWER:
            TemplateMatching::Match(gameScreenshot, assetsPath + "RarityFiveStarsOrLower.jpg", coordinate);
            break;

        default:
            break;
    }
    applicationManager.PointAndClick(coordinate);

    switch (Settings::sellLevel.load())
    {
        case Settings::SellLevel::ONE_ONLY:
            TemplateMatching::Match(gameScreenshot, assetsPath + "LevelOneOnly.jpg", coordinate);
            break;

        case Settings::SellLevel::ALL:
            TemplateMatching::Match(gameScreenshot, assetsPath + "LevelAll.jpg", coordinate);
            break;
    }
    applicationManager.PointAndClick(coordinate);

    switch (Settings::sellBadge.load())
    {
        case Settings::SellBadge::ONLY:
            TemplateMatching::Match(gameScreenshot, assetsPath + "BadgeOnly.jpg", coordinate);
            break;

        case Settings::SellBadge::ALL:
            TemplateMatching::Match(gameScreenshot, assetsPath + "BadgeAll.jpg", coordinate);
            break;
    }
    applicationManager.PointAndClick(coordinate);

    TemplateMatching::Match(gameScreenshot, assetsPath + "Select.jpg", coordinate);
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "Sell2.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "Ok.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "Close.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, "assets/Back.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);
    yield();

    onCompleted();
}

std::string SellCharactersAutomator::ToString() const
{
    return "Selling characters";
}
