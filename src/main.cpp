#include <iostream>

#include "Process.h++"
#include "Window.h++"

int main(int argc, char** argv) {
    const auto pid = Process::FindProcessId("BleachBraveSouls.exe");
    std::cout << pid << std::endl;

    const auto windowHandle = Window::GetWindowHandleByProcessId(pid);
    std::cout << windowHandle << std::endl;

    if (windowHandle != nullptr)
    {
        SetForegroundWindow(windowHandle);
    }
}
