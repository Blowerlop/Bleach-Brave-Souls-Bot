#pragma once

#include <windows.h>


class Window {
    public:
        static HWND GetWindowHandleByProcessId(DWORD pid);
};
