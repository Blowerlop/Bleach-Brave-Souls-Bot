#pragma once

#include "Window.h++"

class Screenshot {
    public:
        Screenshot() = delete;
        ~Screenshot() = delete;

        static HBITMAP Window(HWND hWnd);
};
