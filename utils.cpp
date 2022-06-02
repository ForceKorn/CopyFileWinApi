#include <iostream>

#include "utils.h"


bool isInvalidHandle(HANDLE hResult)
{
	return hResult == INVALID_HANDLE_VALUE;
}

void printLastError()
{
	std::cout << "Error: " << GetLastError() << '\n';
	system("pause");
}

void printAndExitOnInvalidHandle(HANDLE hFile)
{
	if (isInvalidHandle(hFile))
	{
		printLastError();
		std::exit(EXIT_FAILURE);
	}
}

std::string readBufferFromFile(const LPCTSTR sourceFileName)
{
	WinApiFileHandleWrapper sourceFileWrap(sourceFileName, GENERIC_READ, OPEN_EXISTING);
	printAndExitOnInvalidHandle(sourceFileWrap);

	std::string readBuffer((size_t)GetFileSize(sourceFileWrap, NULL), '_');

	BOOL isReadSuccess = ReadFile(sourceFileWrap, (LPVOID)&readBuffer[0], (DWORD)readBuffer.size(), NULL, NULL);
	if (isReadSuccess == FALSE)
	{
		std::cout << "readBufferFromFile ";
		printLastError();
	}

	return readBuffer;
}

void writeFromBufferToFile(const LPCTSTR destinationFileName, const std::string& readBuffer)
{
	WinApiFileHandleWrapper destinationFileWrap(TEXT("DestinationFile.txt"), GENERIC_WRITE, CREATE_ALWAYS);
	printAndExitOnInvalidHandle(destinationFileWrap);

	BOOL isWriteSuccess = WriteFile(destinationFileWrap, (LPCVOID)readBuffer.c_str(),
		(DWORD)readBuffer.size(), NULL, NULL);

	if (isWriteSuccess == FALSE)
	{
		std::cout << "writeFromBufferToFile ";
		printLastError();
	}
	else
	{
		std::cout << "Success on write\n";
	}
}
