#pragma once

#define NOMINMAX
#include <iostream>
#include <string>
#include <cstddef>
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
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	void PrintYellow(std::string s, bool space = true, bool ret = false)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED|FOREGROUND_GREEN);
		std::cout << s;
		if (space) std::cout << " ";
		if (ret) std::cout << std::endl;
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	void PrintWhite(char c, bool space = true, bool ret = false)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << c;
		if (space) std::cout << " ";
		if (ret) std::cout << std::endl;
	}

	void PrintRed(char c, bool space = true, bool ret = false)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		std::cout << c;
		if (space) std::cout << " ";
		if (ret) std::cout << std::endl;
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	void PrintYellow(char c, bool space = true, bool ret = false)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
		std::cout << c;
		if (space) std::cout << " ";
		if (ret) std::cout << std::endl;
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	void PrintRedSpace()
	{
		SetConsoleTextAttribute(hStdOut, BACKGROUND_RED);
		std::cout << " ";
		SetConsoleTextAttribute(hStdOut, 0); //Go back to black background
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}

namespace Utility
{
	size_t nDifferences(std::string str0, std::string str1)
	{
		//!!Need to be the same size for this to work!!
		size_t ctr = 0;
		for (size_t i = 0; i < str0.size(); ++i)
		{
			if (str0[i] != str1[i]) ++ctr;
		}
		return ctr;
	}
}