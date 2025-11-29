#include "19.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"
#include <unordered_set>
#include <unordered_map>

Day19::Day19(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::unordered_set<std::string> notFound;

static int found(const std::string& s, size_t index, std::unordered_set<std::string>& stripes)
{
	if (notFound.contains(s.substr(index)))
		return 0;

	for (size_t i = s.size() - index; i > 0; i--)
	{
		auto tmp = s.substr(index, i);

		if (stripes.contains(tmp))
		{
			std::string stmp = s.substr(0, (i+index));
			
			if (stmp == s)
			{
				return 1;
			}
			auto f = found(s, i+index, stripes);

			if (f == 1)
			{
				return 1;
			}

		}
	}

	notFound.insert(s.substr(index));

	return 0;
}


unsigned long long found2(const std::string& s, size_t index, std::unordered_set<std::string>& stripes, std::unordered_map<std::string, unsigned long long>& memory)
{
	std::string substr = s.substr(index);

	if (memory.contains(substr))
		return memory[substr];

	unsigned long long res = 0;

	for (size_t i = s.size() - index; i > 0; i--)
	{
		auto tmp = s.substr(index, i);

		if (stripes.contains(tmp))
		{
			std::string stmp = s.substr(0, (i + index));

			if (stmp == s)
			{
				//stripes.insert(stmp);
				res++;
			}
			else
				res += found2(s, i + index, stripes, memory);
		}
	}

	memory[substr] = res;

	return res;
}

std::string Day19::runPart1()
{
	std::string s;
	std::getline(*input, s);

	std::unordered_set<std::string> stripes;

	while (s != "")
	{
		auto sss = Util::split(s, ", ");

		for (auto& ss : sss)
		{
			stripes.insert(ss);
		}
		
		std::getline(*input, s);
	}

	int res = 0;

	while (std::getline(*input, s))
	{
		int tmp = found(s, 0, stripes);

		res += tmp;
	}

	return std::to_string(res);
}

std::string Day19::runPart2()
{
	std::string s;
	std::getline(*input, s);

	std::unordered_set<std::string> stripes;
	std::unordered_map<std::string, unsigned long long> memory;

	while (s != "")
	{
		auto sss = Util::split(s, ", ");

		for (auto& ss : sss)
		{
			stripes.insert(ss);
		}

		std::getline(*input, s);
	}

	unsigned long long res = 0;

	while (std::getline(*input, s))
	{
		unsigned long long tmp = found2(s, 0, stripes, memory);

		res += tmp;
	}

	return std::to_string(res);
}

