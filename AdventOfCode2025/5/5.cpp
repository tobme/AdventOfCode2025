#include "5.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"


Day5::Day5(std::shared_ptr<IInput>& _input) : input(_input)
{}

namespace {
	bool isInRange(const std::pair<unsigned long long, unsigned long long>& p, unsigned long long id)
	{
		return id >= p.first && id <= p.second;
	}
}

std::string Day5::runPart1()
{
	std::string line;
	std::vector<std::pair<unsigned long long, unsigned long long>> ranges;
	unsigned long long res = 0;

	while (std::getline(*input, line))
	{
		if (line == "")
			break;

		auto range = Util::split(line, "-");
		unsigned long long startRange = std::stoull(range[0]);
		unsigned long long endRange = std::stoull(range[1]);
		ranges.push_back(std::pair<unsigned long long, unsigned long long>(startRange, endRange));
	}

	while (std::getline(*input, line))
	{
		unsigned long long id = std::stoull(line);

		for (auto& p : ranges)
		{
			bool inRange = isInRange(p, id);
			if (inRange)
			{
				res++;
				break;
			}
		}
	}

	return std::to_string(res);

}

namespace {

	void extendRanges(std::vector<std::pair<unsigned long long, unsigned long long>>& ranges, std::pair<unsigned long long, unsigned long long>& curr)
	{
		auto startRange = curr.first;
		auto endRange = curr.second;

		for (auto& p : ranges)
		{
			if (&p == &curr)
				continue;

			if (startRange >= p.first && endRange <= p.second)
			{
				// Range exists inside other
				curr.first = 0;
				curr.second = 0;
				break;
			}

			if (startRange < p.first && endRange >= p.first && endRange <= p.second)
			{
				// EXTEND START
				p.first = startRange;
				curr.first = 0;
				curr.second = 0;
				extendRanges(ranges, p);
			}
			if (startRange >= p.first && startRange <= p.second && endRange > p.second)
			{
				// EXTEND END
				p.second = endRange;
				curr.first = 0;
				curr.second = 0;
				extendRanges(ranges, p);
			}
		}
	}
}

std::string Day5::runPart2()
{
	std::string line;
	std::vector<std::pair<unsigned long long, unsigned long long>> ranges;
	unsigned long long res = 0;

	while (std::getline(*input, line))
	{
		if (line == "")
			break;

		auto range = Util::split(line, "-");
		unsigned long long startRange = std::stoull(range[0]);
		unsigned long long endRange = std::stoull(range[1]);


		ranges.push_back(std::pair<unsigned long long, unsigned long long>(startRange, endRange));
	}

	for (auto& p : ranges)
	{
		extendRanges(ranges, p);
	}

	auto it =std::remove_if(ranges.begin(), ranges.end(), [](auto& p1)
		{
			return p1.first == 0 && p1.second == 0;
		});

	ranges.erase(it, ranges.end());

	for (auto& p : ranges)
	{
		res += p.second - p.first + 1;
	}

	return std::to_string(res);
}

