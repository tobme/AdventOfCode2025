#include "7.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"

Day7::Day7(std::shared_ptr<IInput>& _input) : input(_input)
{}

bool calc(const std::vector<std::string>& values, int index, unsigned long long res, unsigned long long sum)
{
	if (res > sum)
		return false;
	if (index == values.size())
	{
		return res == sum;
	}

	bool plus = calc(values, index + 1, res + std::stoull(values.at(index)), sum);
	bool times = calc(values, index + 1, res * std::stoull(values.at(index)), sum);

	return plus || times;
}

bool calc2(const std::vector<std::string>& values, int index, unsigned long long res, unsigned long long sum)
{
	if (res > sum)
		return false;
	if (index == values.size())
	{
		return res == sum;
	}

	bool plus = calc2(values, index + 1, res + std::stoull(values.at(index)), sum);
	bool times = calc2(values, index + 1, res * std::stoull(values.at(index)), sum);
	bool append = calc2(values, index + 1, std::stoull(std::to_string(res) + values.at(index)), sum);

	return plus || times || append;
}

std::string Day7::runPart1()
{
	std::string s;
	unsigned long long res = 0;
	while (std::getline(*input, s))
	{
		auto it = s.find_first_of(':');

		unsigned long long sum = std::stoull(s.substr(0, it));

		auto rest = Util::split(s.substr(it + 2), " ");
		
		if (calc(rest, 1, std::stoi(rest.at(0)), sum))
		{
			res += sum;
		}
	}
	return std::to_string(res);
}

std::string Day7::runPart2()
{
	std::string s;
	unsigned long long res = 0;
	while (std::getline(*input, s))
	{
		auto it = s.find_first_of(':');

		unsigned long long sum = std::stoull(s.substr(0, it));

		auto rest = Util::split(s.substr(it + 2), " ");

		if (calc2(rest, 1, std::stoi(rest.at(0)), sum))
		{
			res += sum;
		}
	}
	return std::to_string(res);
}

