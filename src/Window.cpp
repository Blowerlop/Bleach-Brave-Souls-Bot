#include "Window.h++"
#include <windows.h>
#include <vector>

HWND Window::GetWindowHandleByProcessId(DWORD pid)
{
    struct Context
    {
        DWORD pid;
        HWND hwnd;
    };

    Context ctx{pid, nullptr};

    EnumWindows(
        [](HWND hwnd, LPARAM lParam) -> BOOL
        {
            auto *ctx = reinterpret_cast<Context *>(lParam);

            DWORD pid = 0;
            GetWindowThreadProcessId(hwnd, &pid);

            if (pid != ctx->pid) return TRUE;

            if (!IsWindowVisible(hwnd)) return TRUE;

            // Ignore child windows
            if (GetWindow(hwnd, GW_OWNER) != nullptr) return TRUE;

            ctx->hwnd = hwnd;
            return FALSE;
        },
        reinterpret_cast<LPARAM>(&ctx)
    );

    return ctx.hwnd;
}
