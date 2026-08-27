#include <iostream>

#include "Process.h++"
#include "Window.h++"

int main() {
    const auto pid = Process::FindProcessId("BleachBraveSouls.exe");
    std::cout << "Process id :" << pid << std::endl;

    const auto windowHandle = Window::GetWindowHandleByProcessId(pid);

    if (windowHandle != nullptr)
    {
        ShowWindow(windowHandle, SW_RESTORE);
        SetForegroundWindow(windowHandle);
    }
}
