#pragma once
#include <string>
#include <windows.h>


class Process {
    public:
        static DWORD FindProcessId(const std::string& processName);
};
