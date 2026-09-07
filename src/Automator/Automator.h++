#pragma once
#include "../BitmapConverter.h++"


class Automator
{
    public:
        virtual ~Automator() = default;

        virtual void Start();
        bool CanUpdate();
        virtual void Update();

        bool DoesScreenshotMatchTemplate(const cv::String& file, cv::Point& coordinate) const;
        [[nodiscard]] bool HasStarted() const;
        void PointAndClick(cv::Point coordinate) const;

    private:
        HWND windowHandle = nullptr;

        static DWORD GetProcessId();

        static HWND GetWindowHandle(DWORD pid);

        bool hasStarted = false;
        cv::Mat currentScreenshotMat;
        float currentUpdateDelay = 0;
};
