#pragma once

#include <string>

#include <windows.h>

#include "WinApiFileHandleWrapper.h"

bool copyFile(const wchar_t* sourceFileName, const wchar_t* destinationFileName);
