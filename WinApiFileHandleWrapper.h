#pragma once

#include <windows.h>

class WinApiFileHandleWrapper
{
public:

    WinApiFileHandleWrapper(HANDLE hFile);
    ~WinApiFileHandleWrapper();

    HANDLE get() const noexcept;
    
private:
    HANDLE m_file = INVALID_HANDLE_VALUE;
};
