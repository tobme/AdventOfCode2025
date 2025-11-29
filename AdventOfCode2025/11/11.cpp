#include "11.h"

#include <iostream>
#include <algorithm>
#include<unordered_map>
#include "../Helpers/Utilities.h"

Day11::Day11(std::shared_ptr<IInput>& _input) : input(_input)
{}

namespace {
	std::unordered_map<std::string, unsigned long long> memory;

	unsigned long long getGraveSize(unsigned long long input, int blinks, int maxBlinks)
	{

		std::string memoryString = std::to_string(input) + "_" + std::to_string(blinks);

		if (memory.contains(memoryString))
		{
			return memory[memoryString];
		}

		if (blinks == 75)
		{
			return 1;
		}

		blinks++;

		std::string sInput = std::to_string(input);

		unsigned long long res = 0;

		if (input == 0)
		{
			res += getGraveSize(1, blinks, maxBlinks);
		}
		else if (sInput.size() % 2 == 0)
		{
			std::string l = sInput.substr(0, sInput.size() / 2);
			std::string r = sInput.substr(sInput.size() / 2);

			res += getGraveSize(std::stoull(l), blinks, maxBlinks);
			res += getGraveSize(std::stoull(r), blinks, maxBlinks);
		}
		else
		{
			res += getGraveSize(input * 2024, blinks, maxBlinks);
		}

		memory[memoryString] = res;

		return res;
	}
}

std::string Day11::runPart1()
{
	std::string s;
	std::getline(*input, s);

	auto ss = Util::split(s, " ");

	std::vector<unsigned long long> input;

	for (auto& t : ss)
	{
		input.push_back(std::stoull(t));
	}

	unsigned long long res = 0;

	int maxBlinks = 25;

	for (auto i : input)
	{
		res += getGraveSize(i, 0, maxBlinks);
	}

	return std::to_string(res);
}

std::string Day11::runPart2()
{
	std::string s;
	std::getline(*input, s);

	auto ss = Util::split(s, " ");

	std::vector<unsigned long long> input;

	for (auto& t : ss)
	{
		input.push_back(std::stoull(t));
	}

	unsigned long long res = 0;

	int maxBlinks = 75;

	for (auto i : input)
	{
		res += getGraveSize(i, 0, maxBlinks);
	}

	return std::to_string(res);
}

