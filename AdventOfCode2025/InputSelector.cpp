#include "InputSelector.h"

#include <iostream>


std::string InputSelector::GetInputFromList(const std::vector<std::string>& selector)
{
	std::cout << "CHOOSE AN OPTION (number): " << std::endl;

	for (int i = 0; i < selector.size(); i++)
	{
		std::cout << "[" << i + 1 << "] " << selector.at(i) << std::endl;
	}

	int number = -1;

	while (number <= 0 && number >= selector.size())
	{
		std::cin >> number;
	}

	return selector.at(number - 1);
}

bool InputSelector::GetBoolFromQuestion(const std::string& question)
{
	std::cout << question << std::endl;
	std::cout << "[1] Yes" << std::endl;
	std::cout << "[2] No" << std::endl;

	int answr = -1;

	while (answr != 1 && answr != 2)
	{
		std::cin >> answr;
	}

	return answr == 1;
}
