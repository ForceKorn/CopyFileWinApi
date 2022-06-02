#pragma once

#include <windows.h>

class WinApiFileHandleWrapper
{
public:

	WinApiFileHandleWrapper(LPCWSTR localFileName, DWORD desiredAccess, DWORD creationDisposition);
	~WinApiFileHandleWrapper();

	operator HANDLE();

private:
	HANDLE m_file = nullptr;
};
