#pragma once

#define NOMINMAX
#include <iostream>
#include <string>
#include <windows.h>

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

namespace Out
{
	//More clever methods exist, but this one is the simplest in execution

	void PrintWhite(std::string s, bool space = true, bool ret = false)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << s;
		if (space) std::cout << " ";
		if (ret) std::cout << std::endl;
	}

	void PrintRed(std::string s, bool space = true, bool ret = false)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		std::cout << s;
		if (space) std::cout << " ";
		if (ret) std::cout << std::endl;
	}

	void PrintBlue(std::string s, bool space = true, bool ret = false)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
		std::cout << s;
		if (space) std::cout << " ";
		if (ret) std::cout << std::endl;
	}
}