#pragma once
#include <stop_token>

#include "../BitmapConverter.h++"


class Automator
{
    public:
        virtual ~Automator() = default;

        void Run(const std::stop_token& stopToken);

        bool DoesScreenshotMatchTemplate(const cv::String& file, cv::Point& coordinate) const;
        void PointAndClick(cv::Point coordinate) const;

    protected:
        virtual void Start();
        virtual void Update();

    private:
        HWND windowHandle = nullptr;

        static DWORD GetProcessId();
        static HWND GetWindowHandle(DWORD pid);

        cv::Mat currentScreenshotMat;
};
