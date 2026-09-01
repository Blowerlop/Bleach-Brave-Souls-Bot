#pragma once



class AutoClicker {
    public:
        AutoClicker() = delete;
        ~AutoClicker() = delete;

        static void PointAndClick(int x, int y);

    private:
        static void Point(int x, int y);
        static void Click();
};
