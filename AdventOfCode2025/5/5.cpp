#include "5.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"
#include<unordered_map>
#include<unordered_set>


Day5::Day5(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day5::runPart1()
{
	std::string s;

	std::unordered_map<std::string, std::unordered_set<std::string>> orderingRules;

	while (std::getline(*input, s))
	{
		if (s == "")
			break;

		auto ss = Util::split(s, "|");

		orderingRules[ss[1]].insert(ss[0]);
	}

	int res = 0;

	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, ",");


		bool fail = false;
		for (int i = 0; i < ss.size(); i++)
		{
			auto& set = orderingRules[ss[i]];

			for (int j = i + 1; j < ss.size(); j++)
			{
				if (set.contains(ss[j]))
				{
					fail = true;
					break;
				}
			}

			if (fail)
				break;
		}

		if (!fail)
		{
			res += std::stoi(ss[std::floor(ss.size() / 2.0)]);
		}
	}

	return std::to_string(res);
}
namespace {
	bool sortHelper(std::vector<std::string>& s, std::unordered_map<std::string, std::unordered_set<std::string>>& orderingRules)
	{

		for (int i = 0; i < s.size(); i++)
		{
			auto& set = orderingRules[s[i]];
			for (int j = i + 1; j < s.size(); j++)
			{
				if (set.contains(s[j]))
				{
					std::swap(s[i], s[j]);
					return true;
				}
			}
		}
		return false;
	}

	std::vector<std::string>& sort(std::vector<std::string>& s, std::unordered_map<std::string, std::unordered_set<std::string>>& orderingRules)
	{
		bool swapped = true;
		while (swapped)
		{
			for (int i = 0; i < s.size(); i++)
			{
				swapped = sortHelper(s, orderingRules);

				if (swapped)
					break;
			}
		}
		return s;
	}
}

std::string Day5::runPart2()
{
	std::string s;

	std::unordered_map<std::string, std::unordered_set<std::string>> orderingRules;

	while (std::getline(*input, s))
	{
		if (s == "")
			break;

		auto ss = Util::split(s, "|");

		orderingRules[ss[1]].insert(ss[0]);
	}

	int res = 0;

	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, ",");


		bool fail = false;
		for (int i = 0; i < ss.size(); i++)
		{
			auto& set = orderingRules[ss[i]];

			for (int j = i + 1; j < ss.size(); j++)
			{
				if (set.contains(ss[j]))
				{
					fail = true;
					ss = sort(ss, orderingRules);
					break;
				}
			}

			if (fail)
				break;
		}

		if (fail)
		{
			res += std::stoi(ss[std::floor(ss.size() / 2.0)]);
		}
	}

	return std::to_string(res);
}

