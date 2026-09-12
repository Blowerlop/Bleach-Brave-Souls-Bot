#pragma once
#include <stop_token>

#include "../BitmapConverter.h++"


class Automator
{
    public:
        virtual ~Automator() = default;

        void Run(const std::stop_token& stopToken);

    protected:
        virtual void Start();
        virtual void Update(const std::stop_token& stopStoken);

        bool DoesScreenshotMatchTemplate(const cv::String& file, cv::Point& coordinate) const;
        void PointAndClick(cv::Point coordinate) const;

    private:
        HWND windowHandle = nullptr;
        static DWORD GetProcessId();
        static HWND GetWindowHandle(DWORD pid);
        
        cv::Mat currentScreenshotMat;
};
