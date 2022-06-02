#include <iostream>
#include <string>

#include <windows.h>

#include "utils.h"


int main()
{
	std::string readBuffer = readBufferFromFile(TEXT("main.cpp"));
	writeFromBufferToFile(TEXT("DestinationFile.txt"), readBuffer);

	return 0;
}