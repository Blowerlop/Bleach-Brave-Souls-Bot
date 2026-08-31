#pragma once

#include <opencv2/core/mat.hpp>
#include "Window.h++"


class BitmapConverter {
    public:
        BitmapConverter() = delete;
        ~BitmapConverter() = delete;

        static cv::Mat ToMat(HBITMAP hBitmap);
};