#include "6.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"

Day6::Day6(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day6::runPart1()
{
	std::string line;
	std::vector<std::vector<unsigned long long>> numbers;
	std::vector<char> mathSigns;

	while (std::getline(*input, line))
	{
		std::string currNumb = "";
		std::vector<unsigned long long> lineNumber;


		for (auto c : line)
		{

			if (c == '*' || c == '+')
			{
				mathSigns.push_back(c);
			}
			else if (c == ' ')
			{
				if (currNumb != "")
				{
					lineNumber.push_back(std::stoull(currNumb));
				}
				currNumb = "";
			}
			else
			{
				currNumb += c;
			}
		}

		if (currNumb != "")
			lineNumber.push_back(std::stoull(currNumb));

		if (!lineNumber.empty())
			numbers.push_back(lineNumber);
	}

	unsigned long long res = 0;

	for (int j = 0; j < numbers.front().size(); j++)
	{
		char sign = mathSigns.at(j);
		unsigned long long locRes = (sign == '+') ? 0 : 1;

		for (int i = 0; i < numbers.size(); i++)
		{
			
			if (sign == '+')
			{
				locRes += numbers.at(i).at(j);
			}
			else
			{
				locRes *= numbers.at(i).at(j);
			}
		}
		res += locRes;
		
	}


	return std::to_string(res);
}

std::string Day6::runPart2()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "12312312");

	char lastKnownSign = ' ';

	std::vector<unsigned long long> numbers;

	unsigned long long res = 0;

	for (int j = 0; j < matrix.front().size(); j++)
	{
		std::string numb = "";
		for (int i = 0; i < matrix.size(); i++)
		{
			char c = matrix.at(i).at(j);

			if (isdigit(c))
			{
				numb += c;
			}
			else if (c == '+' || c == '*')
			{
				lastKnownSign = c;
			}
		}

		if (numb == "")
		{
			unsigned long long locRes = lastKnownSign == '+' ? 0 : 1;
			for (auto& n : numbers)
			{
				if (lastKnownSign == '+')
					locRes += n;
				else
					locRes *= n;
			}
			res += locRes;
			numbers = std::vector<unsigned long long>();
		}
		else
		{
			numbers.push_back(std::stoull(numb));
		}

	}

	if (!numbers.empty())
	{
		unsigned long long locRes = lastKnownSign == '+' ? 0 : 1;
		for (auto& n : numbers)
		{
			if (lastKnownSign == '+')
				locRes += n;
			else
				locRes *= n;
		}
		res += locRes;
	}


	return std::to_string(res);
}

