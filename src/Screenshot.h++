#pragma once

#include <opencv2/core/mat.hpp>
#include "Window.h++"

class Screenshot {
    public:
        Screenshot() = delete;

        static cv::Mat Window(HWND hwnd);

    private:
        static BITMAPINFOHEADER createBitmapHeader(int width, int height);
};
