#include "Process.h++"

#include <windows.h>
#include <cstdio>
#include <tlhelp32.h>

DWORD Process::FindProcessId(const std::string &processName)
{
    PROCESSENTRY32 processEntry;
    DWORD pid = 0;

    HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == handle) return 0;

    processEntry.dwSize = sizeof(PROCESSENTRY32);

    BOOL hResult = Process32First(handle, &processEntry);

    while (hResult)
    {
        if (processName == processEntry.szExeFile)
        {
            pid = processEntry.th32ProcessID;
            break;
        }

        hResult = Process32Next(handle, &processEntry);
    }

    CloseHandle(handle);
    return pid;
}
