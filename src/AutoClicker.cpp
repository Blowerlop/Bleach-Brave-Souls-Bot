#include "AutoClicker.h++"
#include "Window.h++"

void AutoClicker::Point(const int x, const int y)
{
    SetCursorPos(x, y);
}

void AutoClicker::Click()
{
    tagINPUT input {};

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

void AutoClicker::PointAndClick(int x, int y)
{
    Point(x, y);
    Click();
}
