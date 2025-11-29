#include "3.h"

#include <iostream>
#include <algorithm>

namespace {

	unsigned long long match(std::string::const_iterator begin, std::string::const_iterator end)
	{
		std::string currentString{ begin, end };

		auto match = currentString[0] == 'm' && currentString[1] == 'u' && currentString[2] == 'l' && currentString [3] == '(';

		if (!match)
			return 0;

		int maxEntries = 3;
		int currentEntries = 0;
		auto index = 4;

		while (isdigit(currentString[index]))
		{
			currentEntries++;
			index++;

			if (currentEntries > maxEntries)
			{
				return 0;
			}
		}

		if (currentEntries == 0)
			return 0;

		unsigned long long firstMult = std::stoull(std::string(currentString.begin() + 4, currentString.begin() + index));

		currentEntries = 0;
		if (currentString[index] != ',')
			return 0;

		index++;
		int startIndex = index;

		while (isdigit(currentString[index]))
		{
			currentEntries++;
			index++;

			if (currentEntries > maxEntries)
			{
				return 0;
			}
		}

		if (currentEntries == 0)
			return 0;

		unsigned long long secondMult = std::stoull(std::string(currentString.begin() + startIndex, currentString.begin() + index));

		if (currentString[index] != ')')
			return 0;

		return firstMult * secondMult;
		
	}
}

Day3::Day3(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day3::runPart1()
{
	std::string s;

	unsigned long long res = 0;

	while (std::getline(*input, s))
	{
		auto first = s.begin();

		while ((first = std::find(first, s.end(), 'm')) != s.end())
		{
			res += match(first, s.end());
			first++;
		}
	}

	return std::to_string(res);
}

std::string Day3::runPart2()
{
	std::string s;

	unsigned long long res = 0;

	auto pred = [](char c) {
		return c == 'd' || c == 'm';
		};

	bool enabled = true;

	while (std::getline(*input, s))
	{
		auto first = s.begin();

		while ((first = std::find_if(first, s.end(), pred)) != s.end())
		{
			auto answ = match(first, s.end());

			if (std::string(first, first + 4) == "do()")
			{
				enabled = true;
			}
			else if (std::string(first, first + 7) == "don't()")
			{
				enabled = false;
			}

			if (enabled)
				res += answ;

			first++;
		}
	}

	return std::to_string(res);
}

