#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <random>
#include <conio.h>
#include "Formatting.h"

#define MAX_TEXT_SIZE 25
#define NUMBER_WORDS_TOTAL 100 //Number of words in our words list

int main()
{
	size_t textLength;
	std::cout << "Number of words? (Max: " << MAX_TEXT_SIZE << ") : "; std::cin >> textLength;
	textLength = std::min(textLength, (size_t)MAX_TEXT_SIZE);

	std::vector<std::string> Text;
	std::ifstream in("Words.txt");
	Text.resize(textLength);
	for (auto& w : Text)
	{
		//Generate a random number which will be the index of the word that we'll be using
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, NUMBER_WORDS_TOTAL - 1);
		size_t wordIndex = dist(rng);
		std::string s; //using local variable might be marginally faster than accessing element of vector
		do
		{
			in >> s;
		} while (wordIndex--);
		w = s;
	}

	for (const auto& e : Text)
	{
		Out::PrintBlue(e);
	}

	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return 0;
}