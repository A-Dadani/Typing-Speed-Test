#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
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

	std::string Text;
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

	Out::PrintYellow(Text, false);
	std::cout << std::endl;

	for (auto it = Text.begin(); it != Text.end(); ++it) //No const correctness I'm lazy
	{
		char input = _getch();
		//Check for backspaces
		if (input == 8)
		{
			std::cout << "\b \b"; //ASCII for a backspace is 8
			it -= 2; //Stepping the iterator back twice because backspace is still a char
		}
		else if (input == *it) Out::PrintWhite(input, false);
		else if (input == ' ') Out::PrintRedSpace(); //Wrong character but it's a space so 
													//needs to be treated differently
		else Out::PrintRed(input, false); //Some other wrong character
	}

	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return 0;
}