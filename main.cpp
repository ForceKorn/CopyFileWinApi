#include <iostream>
#include <string>

#include <windows.h>

#include "utils.h"


int main()
{
	const bool copyResult = copyFile(L"SourceText.txt", L"DestinationFile.txt");
	system("pause");

	return copyResult;
	
}