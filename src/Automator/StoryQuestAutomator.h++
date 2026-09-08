#pragma once
#include "Automator.h++"


class StoryQuestAutomator final : public Automator
{
    protected:
        void Update(const std::stop_token& stopStoken) override;
};
