#include "Screenshot.h++"

#include <iostream>


HBITMAP  Screenshot::Window(HWND hWnd)
{
    HBITMAP hbmScreen = nullptr;
    HDC hdcWindow = nullptr;
    HDC hdcMemDC = nullptr;

    hdcWindow = GetWindowDC(hWnd);
    if (!hdcWindow)
    {
        std::cerr << "GetWindowDC has failed" << std::endl;
        return nullptr;
    }

    hdcMemDC = CreateCompatibleDC(hdcWindow);
    if (!hdcMemDC)
    {
        std::cerr << "CreateCompatibleDC has failed" << std::endl;
        ReleaseDC(hWnd, hdcWindow);
        return nullptr;
    }

    RECT rcWindow;
    GetWindowRect(hWnd, &rcWindow);
    int width = rcWindow.right - rcWindow.left;
    int height = rcWindow.bottom - rcWindow.top;

    hbmScreen = CreateCompatibleBitmap(hdcWindow, width, height);
    if (!hbmScreen)
    {
        std::cerr << "CreateCompatibleBitmap Failed" << std::endl;
        DeleteDC(hdcMemDC);
        ReleaseDC(hWnd, hdcWindow);
        return nullptr;
    }

    HGDIOBJ hOld = SelectObject(hdcMemDC, hbmScreen);

    if (!PrintWindow(hWnd, hdcMemDC, PW_RENDERFULLCONTENT))
    {
        std::cerr << "PrintWindow has failed" << std::endl;
        SelectObject(hdcMemDC, hOld);
        DeleteObject(hbmScreen);
        DeleteDC(hdcMemDC);
        ReleaseDC(hWnd, hdcWindow);
        return nullptr;
    }

    SelectObject(hdcMemDC, hOld);

    DeleteDC(hdcMemDC);
    ReleaseDC(hWnd, hdcWindow);

    return hbmScreen; // Need to be release with DeleteObject()
}