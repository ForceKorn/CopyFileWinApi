#include "WinApiFileHandleWrapper.h"

WinApiFileHandleWrapper::WinApiFileHandleWrapper(LPCWSTR localFileName, 
												 DWORD desiredAccess, 
												 DWORD creationDisposition)
	: m_file(CreateFile(localFileName, 
						desiredAccess, 
						NULL, 
						NULL, 
						creationDisposition, 
						FILE_ATTRIBUTE_NORMAL, 
						NULL)) {}

WinApiFileHandleWrapper::~WinApiFileHandleWrapper() 
{
	CloseHandle(m_file); 
}

WinApiFileHandleWrapper::operator HANDLE()
{
	return m_file;
}