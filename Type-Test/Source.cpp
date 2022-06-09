#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
#include <random>
#include <chrono>
#include <conio.h>
#include "Misc.h"

#define MAX_TEXT_SIZE 50
#define NUMBER_WORDS_TOTAL 1000 //Number of words in our words list

int main()
{
	size_t textLength;
	std::cout << "Number of words? (Max: " << MAX_TEXT_SIZE << ") : "; std::cin >> textLength;
	textLength = std::min(textLength, (size_t)MAX_TEXT_SIZE);

	std::string Text;
	std::string InputString;
	std::ifstream in("Words.txt");
	std::vector<size_t> indices;
	indices.resize(textLength);

	for (auto& e : indices)
	{
		//Generate a random number which will be the index of the word that we'll be using
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, NUMBER_WORDS_TOTAL - 1);
		e = dist(rng);
	}

	//Since we're going to be using the >> operator to extract from the text the extracting needs to be squencial
	std::sort(indices.begin(), indices.end());

	for (auto it = indices.end() - 1; it != indices.begin(); --it)
	{
		*it -= *(it - 1);
	}

	{ //Local scope so that the vector is destroyed and wastes no more memory
		std::vector<std::string> tempTxt;
		tempTxt.resize(textLength);
		for (size_t i = 0; i < textLength; ++i)
		{
			std::string s; //using local variable might be marginally faster than accessing element of vector
			do
			{
				in >> s;
			} while (indices[i]--);
			tempTxt[i] = s;
		}
		std::shuffle(tempTxt.begin(), tempTxt.end(), std::random_device()); //The text will be ordered
																			//so we shuffle it
		for (const auto& e : tempTxt)
		{
			Text += (e + " ");
		}
	}

	Text.pop_back(); //Remove the last space
	Out::PrintYellow(Text, false);
	std::cout << std::endl;

	std::chrono::steady_clock::time_point startTime;

	for (auto it = Text.begin(); it != Text.end(); ++it) //No const correctness I'm lazy
	{
		char input = _getch();
		if (it == Text.begin()) startTime = std::chrono::steady_clock::now();
		//Check for backspaces
		if (input == 8) //ASCII for a backspace is 8
		{
			std::cout << "\b \b";
			InputString.pop_back();
			it -= 2; //Stepping the iterator back twice because backspace is still a char
		}
		else
		{
			InputString += input;
			if (input == *it) Out::PrintWhite(input, false);
			else if (input == ' ') Out::PrintRedSpace(); //Wrong character but it's a space so 
														//needs to be treated differently
			else Out::PrintRed(input, false); //Some other wrong character
		}
	}

	std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
	auto durationmS = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	auto durationS = durationmS / 1000000.;
	auto durationM = durationS / 60.;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	unsigned long long charCount = Text.end() - Text.begin();
	long double wordCount = charCount / 5.L;
	size_t nMistakes = Utility::nDifferences(Text, InputString);
	float accuracy = 1 - ((float)nMistakes / charCount);
	std::cout << "\nYou took " << durationS << " seconds\n";
	std::cout << "You typed " << charCount << " characters ";
	std::cout << "with " << nMistakes << " mistakes\n";
	std::cout << "That's an accuracy of " << accuracy * 100 << "%\n";
	std::cout << "And a speed of " << (wordCount / durationM) * accuracy << " WPM\n";
	std::cout << "Raw WPM is: " << (wordCount / durationM) << " WPM\n";
	std::cout << "Press any key to exit";
	while (!_kbhit());
	return 0;
}