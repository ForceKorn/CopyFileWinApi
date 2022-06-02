// TODO: refactor code
#include <iostream>
#include <windows.h>


bool isInvalidHandle(HANDLE hResult)
{
	return hResult == INVALID_HANDLE_VALUE;
}

void showError()
{
	std::cout << "Error: " << GetLastError() << '\n';
	system("pause");
}


int main()
{
	// TODO: get general function
	LPCWSTR destinationPath = TEXT("DestinationFile.txt");
	HANDLE hDestinationFile = CreateFile(destinationPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (isInvalidHandle(hDestinationFile))
	{
		showError();
		return 0;
	}

	LPCWSTR sourcePath = TEXT("SourceFile.txt");
	HANDLE hSourceFile = CreateFile(sourcePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (isInvalidHandle(hSourceFile))
	{
		showError();
		return 0;
	}


	// TODO: read and remove unnececary atributes
	DWORD dwFileSize = GetFileSize(hSourceFile, NULL);
	char* readBuffer = new char[dwFileSize + 1];
	LPDWORD outBytesRead = nullptr;

	BOOL isReadSuccess = ReadFile(hSourceFile, readBuffer, dwFileSize, outBytesRead, NULL);
	if (isReadSuccess == FALSE)
	{
		std::cout << "read file\n";
		printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", GetLastError());
	}

	// TODO: read and remove unnececary atributes and checks
	DWORD dwBytesWritten = 0;
	BOOL isWriteSuccess = WriteFile(hDestinationFile, readBuffer, dwFileSize, &dwBytesWritten, NULL);
	if (isWriteSuccess == FALSE)
	{
		std::cout << "Write file error: ";
		showError();
	}
	else
	{
		if (dwBytesWritten != dwFileSize)
		{
			std::cout << "Error: synchronous write\n";
		}
		else
		{
			std::cout << "Success write\n";
		}
	}


	// TODO: swap to RAII
	CloseHandle(hDestinationFile);
	CloseHandle(hSourceFile);
	
	return 0;
}