#include <iostream>

#include "utils.h"

void printResult(const char* msg = "")
{
    LPSTR errorText = NULL;
    
    FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, 
        GetLastError(), 
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&errorText),
        NULL, 
        NULL);

    if (errorText != NULL)
    {
        std::cout << "Result: " << msg << " " << errorText << '\n';
        LocalFree(errorText);
    }
}

bool copyFileImplementation(HANDLE hSourceFile, HANDLE hDestinationFile)
{
    constexpr size_t PAGE_SIZE  = 4096;
    char buffer[PAGE_SIZE]      = { 0 };

    DWORD dwBytesRead = 0;
    DWORD dwBytesWritten = 0;
    while (ReadFile(hSourceFile, buffer, PAGE_SIZE, &dwBytesRead, NULL) && dwBytesRead > 0)
    {
        if (SetFilePointer(hDestinationFile, NULL, NULL, FILE_END) == INVALID_SET_FILE_POINTER)
        {
            printResult("SetFilePointer");
            return false;
        }

        if (!WriteFile(hDestinationFile, buffer, dwBytesRead, &dwBytesWritten, NULL))
        {
            printResult("WriteFile");
            return false;
        }
    }

    printResult();
    return true;
}

HANDLE makeHandlerToCreateFile(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition)
{
    return CreateFileW(lpFileName, dwDesiredAccess, NULL, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
}

bool copyFile(const wchar_t* sourceFileName, const wchar_t* destinationFileName)
{
    WinApiFileHandleWrapper sourceFileWrap = 
        makeHandlerToCreateFile(sourceFileName, GENERIC_READ, OPEN_EXISTING);

    if (sourceFileWrap.get() == INVALID_HANDLE_VALUE)
    {
        printResult();
        return false;
    }

    WinApiFileHandleWrapper destinationFileWrap 
        = makeHandlerToCreateFile(destinationFileName, GENERIC_WRITE, CREATE_NEW);
    
    if (destinationFileWrap.get() == INVALID_HANDLE_VALUE)
    {
        printResult();
        return false;
    }

    return copyFileImplementation(sourceFileWrap.get(), destinationFileWrap.get());
}
