#pragma once
#include "BitmapConverter.h++"


class Automator
{
    public:
        virtual ~Automator() = default;


        virtual void Start();

        void TakeScreenshotAndMatchTemplate(const cv::String& file);
        virtual void OnScreenshotMatchTemplate(cv::Point coordinate);

    private:
        HWND windowHandle = nullptr;

        static DWORD GetProcessId();

        static HWND GetWindowHandle(DWORD pid);
};
