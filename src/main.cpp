#include "Process.h++"
#include "Screenshot.h++"
#include "Window.h++"
#include "opencv2/opencv.hpp"

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

    const cv::Mat src = Screenshot::Window(windowHandle);

    std::vector<uchar> buf;
    cv::imencode(".png", src, buf);

    // save img
    cv::imwrite("Screenshot.png", src);

    buf.clear();

    return 0;
}
