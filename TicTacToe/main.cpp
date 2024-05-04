#include "src/Application/Application.h"
#include <Windows.h>
#include <iostream>

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	try {
		Application().Run();
	}
	catch (...) {
		std::cout << "Something happen!!!" << std::endl;
	}

	return 0;
}