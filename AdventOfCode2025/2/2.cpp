#include "2.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"


namespace {
	bool checkValid(const std::string& num)
	{
		if (num.front() == '0')
			return false;

		if (num.size() % 2 != 0)
			return true;

		std::string firstHalf = num.substr(0, num.size() / 2);
		std::string secHalf = num.substr(num.size() / 2);

		return firstHalf != secHalf;
	}

	bool checkValid2(const std::string& num)
	{
		if (num.front() == '0')
			return false;

		for (int range = 1; range <= num.size() / 2; range++)
		{
			auto startSeq = num.substr(0, range);
			int rangeMultiplier = 1;
			bool isSeq = true;

			while (range * rangeMultiplier < num.size())
			{
				auto repSeq = num.substr(range * rangeMultiplier, range);

				if (startSeq != repSeq)
				{
					isSeq = false;
					break;
				}

				rangeMultiplier++;
			}

			//std::cout << startSeq << " " << endSeq << std::endl;

			if (isSeq)
				return false;
		}

		return true;
	}

}

Day2::Day2(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day2::runPart1()
{
	std::string line;
	std::getline(*input, line);

	auto ranges = Util::split(line, ",");
	unsigned long long res = 0;

	for (auto& s : ranges)
	{
		auto positions = Util::split(s, "-");

		auto startPos = std::stoull(positions[0]);
		auto endPos = std::stoull(positions[1]);

		for (unsigned long long i = startPos; i <= endPos; i++)
		{
			if (!checkValid(std::to_string(i)))
			{
				res += i;
			}
		}
	}

	return std::to_string(res);
}

std::string Day2::runPart2()
{
	std::string line;
	std::getline(*input, line);

	auto ranges = Util::split(line, ",");
	unsigned long long res = 0;

	for (auto& s : ranges)
	{
		auto positions = Util::split(s, "-");

		auto startPos = std::stoull(positions[0]);
		auto endPos = std::stoull(positions[1]);

		for (unsigned long long i = startPos; i <= endPos; i++)
		{
			if (!checkValid2(std::to_string(i)))
			{
				//std::cout << i << std::endl;
				res += i;
			}
		}
	}

	return std::to_string(res);
}

