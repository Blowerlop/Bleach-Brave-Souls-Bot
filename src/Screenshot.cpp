#include "Screenshot.h++"

#include <iostream>


HBITMAP Screenshot::Window(HWND hWnd)
{
    HBITMAP hbmScreen = nullptr;
    HDC hdcWindow = nullptr;
    HDC hdcMemDC = nullptr;

    hdcWindow = GetWindowDC(hWnd);
    if (!hdcWindow)
    {
        throw std::runtime_error("GetWindowDC has failed");
        return nullptr;
    }

    hdcMemDC = CreateCompatibleDC(hdcWindow);
    if (!hdcMemDC)
    {
        ReleaseDC(hWnd, hdcWindow);

        throw std::runtime_error("CreateCompatibleDC has failed");
        return nullptr;
    }

    RECT rcWindow;
    GetWindowRect(hWnd, &rcWindow);
    int width = rcWindow.right - rcWindow.left;
    int height = rcWindow.bottom - rcWindow.top;

    hbmScreen = CreateCompatibleBitmap(hdcWindow, width, height);
    if (!hbmScreen)
    {
        DeleteDC(hdcMemDC);
        ReleaseDC(hWnd, hdcWindow);

        throw std::runtime_error("CreateCompatibleBitmap has failed");
        return nullptr;
    }

    HGDIOBJ hOld = SelectObject(hdcMemDC, hbmScreen);

    if (!PrintWindow(hWnd, hdcMemDC, PW_RENDERFULLCONTENT))
    {
        SelectObject(hdcMemDC, hOld);
        DeleteObject(hbmScreen);
        DeleteDC(hdcMemDC);
        ReleaseDC(hWnd, hdcWindow);

        throw std::runtime_error("PrintWindow has failed");
        return nullptr;
    }

    SelectObject(hdcMemDC, hOld);

    DeleteDC(hdcMemDC);
    ReleaseDC(hWnd, hdcWindow);

    return hbmScreen; // Need to be release with DeleteObject()
}