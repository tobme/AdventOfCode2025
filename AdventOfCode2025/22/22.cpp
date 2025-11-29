#include "22.h"

#include <iostream>
#include <algorithm>
#include<unordered_map>

Day22::Day22(std::shared_ptr<IInput>& _input) : input(_input)
{}

unsigned long long mix(unsigned long long number)
{
	for (int i = 0; i < 2000; i++)
	{
		unsigned long long tmp = number * 64;
		number ^= tmp;
		number %= 16777216;

		tmp = number / 32;
		number ^= tmp;
		number %= 16777216;

		tmp = number * 2048;
		number ^= tmp;
		number %= 16777216;
	}

	return number;
}

std::unordered_map<std::string, int> mix2(std::string& num)
{
	int lastValue = num.back() - '0';

	unsigned long long number = std::stoull(num);

	std::vector<std::pair<int,int>> changeVector;

	for (int i = 0; i < 2000; i++)
	{
		unsigned long long tmp = number * 64;
		number ^= tmp;
		number %= 16777216;

		tmp = number / 32;
		number ^= tmp;
		number %= 16777216;

		tmp = number * 2048;
		number ^= tmp;
		number %= 16777216;

		int newValue = std::to_string(number).back() - '0';

		int change = newValue - lastValue;

		changeVector.push_back({ change, newValue });

		lastValue = newValue;
	}

	auto itStart = changeVector.begin();

	auto itEnd = changeVector.begin() + 3;

	std::unordered_map<std::string, int> changeMap;

	while (itEnd != changeVector.end())
	{
		std::string id = std::to_string(itStart->first) + "_" + std::to_string((itStart+1)->first) + "_" + std::to_string((itStart + 2)->first) + "_" + std::to_string((itStart + 3)->first);
		
		if (!changeMap.contains(id))
		{
			changeMap[id] = (itStart + 3)->second;
		}

		itStart++;
		itEnd++;
	}

	return changeMap;
}

std::string Day22::runPart1()
{
	std::string s;

	unsigned long long res = 0;

	while (std::getline(*input, s))
	{
		res += mix(std::stoull(s));
	}

	return std::to_string(res);
}

std::string Day22::runPart2()
{
	std::string s;

	int res = 0;

	std::unordered_map<std::string, int> bigMap;

	while (std::getline(*input, s))
	{
		auto m = mix2(s);

		for (auto& mm : m)
		{
			if (bigMap.contains(mm.first))
				bigMap[mm.first] += mm.second;
			else
				bigMap[mm.first] = mm.second;
		}
	}

	for (auto& m : bigMap)
	{
		res = std::max(res, m.second);
	}

	return std::to_string(res);
}

