#include "opencv2/opencv.hpp"
#include "BitmapConverter.h++"
#include "Process.h++"
#include "Screenshot.h++"
#include "TemplateMatching.h++"
#include "Window.h++"


int main()
{
    const auto pid = Process::FindProcessId("BleachBraveSouls.exe");
    if (pid == 0)
    {
        std::cerr << "Game process not found." << std::endl;
        return 1;
    }

    const auto windowHandle = Window::GetWindowHandleByProcessId(pid);

    if (windowHandle == nullptr)
    {
        std::cerr << "Game window not found." << std::endl;
        return 1;
    }

    ShowWindow(windowHandle, SW_RESTORE);
    SetForegroundWindow(windowHandle);

    HBITMAP hbitmap = Screenshot::Window(windowHandle);
    cv::Mat gameScreenshotMat = BitmapConverter::ToMat(hbitmap);
    DeleteObject(hbitmap);

    cv::Mat template_ = cv::imread("assets/Screenshot_1.jpg");

    cv::Point coordinate{};
    bool hasMatch = TemplateMatching::match(gameScreenshotMat, template_, coordinate, true);
    std::cout << "Has match: " << std::boolalpha << hasMatch << std::endl;
    if (hasMatch)
    {
        std::cout << "Match coordinate: (" << coordinate.x << ", " << coordinate.y << ")" << std::endl;
    }

    return 0;
}
