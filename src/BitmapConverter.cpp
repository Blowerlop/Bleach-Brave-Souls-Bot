#include <opencv2/imgproc.hpp>
#include "BitmapConverter.h++"


cv::Mat BitmapConverter::ToMat(HBITMAP hBitmap)
{
    cv::Mat result;

    if (!hBitmap) return result;

    BITMAP bmpScreen;
    GetObject(hBitmap, sizeof(BITMAP), &bmpScreen);

    BITMAPINFOHEADER bi = {};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bmpScreen.bmWidth;
    bi.biHeight = -bmpScreen.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;

    DWORD dwBmpSize = bmpScreen.bmWidth * 4 * bmpScreen.bmHeight;

    HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
    if (!hDIB) return result;

    char *lpbitmap = static_cast<char *>(GlobalLock(hDIB));


    HDC hdcScreen = GetDC(nullptr);

    int scanLines = GetDIBits(hdcScreen, hBitmap, 0,
                              static_cast<UINT>(bmpScreen.bmHeight),
                              lpbitmap,
                              reinterpret_cast<BITMAPINFO *>(&bi), DIB_RGB_COLORS);

    ReleaseDC(nullptr, hdcScreen);

    if (scanLines > 0)
    {
        cv::Mat temp(
            bmpScreen.bmHeight,
            bmpScreen.bmWidth,
            CV_8UC4,
            lpbitmap
        );

        // Convert to normal OpenCV BGR.
        cv::cvtColor(
            temp,
            result,
            cv::COLOR_BGRA2BGR
        );
    }

    GlobalUnlock(hDIB);
    GlobalFree(hDIB);

    return result;
}
