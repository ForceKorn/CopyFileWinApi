#include "WinApiFileHandleWrapper.h"

WinApiFileHandleWrapper::WinApiFileHandleWrapper(HANDLE hFile)
	: m_file(hFile) {}

WinApiFileHandleWrapper::~WinApiFileHandleWrapper() 
{
	if (m_file)
	{
		CloseHandle(m_file);
	}
}

HANDLE WinApiFileHandleWrapper::get() const noexcept
{
	return m_file;
}