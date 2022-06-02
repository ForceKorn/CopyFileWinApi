#pragma once

#include <string>

#include <windows.h>

#include "WinApiFileHandleWrapper.h"

bool isInvalidHandle(HANDLE hResult);

void printLastError();

void printAndExitOnInvalidHandle(HANDLE hFile);

void writeFromBufferToFile(const LPCTSTR destinationFileName, const std::string& readBuffer);

std::string readBufferFromFile(const LPCTSTR sourceFileName);
