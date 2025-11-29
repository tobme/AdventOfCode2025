#include "25.h"

#include <iostream>
#include <algorithm>

Day25::Day25(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day25::runPart1()
{
	std::string s;

	std::vector<std::vector<int>> locks;
	std::vector<std::vector<int>> keys;

	while (std::getline(*input, s))
	{
		bool lock = s[0] == '#';

		std::getline(*input, s);

		std::vector<int> fig(5, lock ? 0 : -1);

		while (s != "")
		{
			for (int i = 0; i < s.size(); i++)
			{
				if (s[i] == '#')
					fig[i]++;
			}


			if (!std::getline(*input, s))
				break;
		}

		if (lock)
			locks.push_back(fig);
		else
			keys.push_back(fig);
	}

	int res = 0;
	int maxCol = 5;

	for (auto& key : keys)
	{
		for (auto& lock : locks)
		{
			bool fail = false;
			for (int i = 0; i < keys.front().size(); i++)
			{
				if (key[i] + lock[i] > maxCol)
				{
					fail = true;
					break;
				}
			}
			if (!fail)
				res++;
		}
	}

	return std::to_string(res);
}

std::string Day25::runPart2()
{
	return "";
}

