#include "SellCharactersAutomator.h++"

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

    if (DoesScreenshotMatchTemplate(assetsPath + "RarityThreeStarsOrLower.jpg", coordinate)) PointAndClick(coordinate);
    if (DoesScreenshotMatchTemplate(assetsPath + "LevelAll.jpg", coordinate)) PointAndClick(coordinate);
    if (DoesScreenshotMatchTemplate(assetsPath + "BadgeOnly.jpg", coordinate)) PointAndClick(coordinate);

    if (DoesScreenshotMatchTemplate(assetsPath + "Select.jpg", coordinate)) PointAndClick(coordinate);

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
