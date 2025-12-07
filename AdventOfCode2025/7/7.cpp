#include "7.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"
#include "../Helpers/PairHash.h"
#include <unordered_set>

Day7::Day7(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::unordered_set<std::pair<int, int>, pair_hash> usedSplits;
std::unordered_map<std::pair<int, int>, unsigned long long, pair_hash> memory;

namespace {

	int findNextSplit(const std::unordered_set<std::pair<int, int>, pair_hash>& splits, const std::pair<int, int>& pos, int maxHeight)
	{
		auto tmpPos = pos;
		tmpPos.first++;

		bool foundSplit = false;

		while (tmpPos.first <= maxHeight)
		{
			if (usedSplits.find({ tmpPos.first, tmpPos.second }) != usedSplits.end())
			{
				return 0;
			}

			if (splits.find({ tmpPos.first, tmpPos.second }) != splits.end())
			{
				usedSplits.insert({ tmpPos.first, tmpPos.second });
				foundSplit = true;
				break;
			}
			tmpPos.first++;
		}



		if (foundSplit)
		{
			return 1 + findNextSplit(splits, { tmpPos.first, tmpPos.second - 1 }, maxHeight) + findNextSplit(splits, { tmpPos.first, tmpPos.second + 1 }, maxHeight);
		}

		return 0;
	}


	unsigned long long findNextSplit2(const std::unordered_set<std::pair<int, int>, pair_hash>& splits, const std::pair<int, int>& pos, int maxHeight)
	{
		auto tmpPos = pos;
		tmpPos.first++;

		bool foundSplit = false;

		while (tmpPos.first <= maxHeight)
		{
			if (memory.find(tmpPos) != memory.end())
				return memory[tmpPos];


			if (splits.find({ tmpPos.first, tmpPos.second }) != splits.end())
			{
				foundSplit = true;
				break;
			}
			tmpPos.first++;
		}



		if (foundSplit)
		{
			unsigned long long res2 = findNextSplit2(splits, { tmpPos.first, tmpPos.second - 1 }, maxHeight) + findNextSplit2(splits, { tmpPos.first, tmpPos.second + 1 }, maxHeight);

			memory[tmpPos] = res2;

			return res2;
		}

		return 1;
	}
}

std::string Day7::runPart1()
{
	std::string line;

	std::pair<int, int> startPos;

	int height = 0;

	std::unordered_set<std::pair<int, int>, pair_hash> splits;

	while (std::getline(*input, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (line.at(i) == 'S')
				startPos = { height, i };
			else if (line.at(i) == '^')
			{
				splits.insert({ height, i });
			}
		}
		height++;
	}

	int res = findNextSplit(splits, startPos, height);

	return std::to_string(res);
}

std::string Day7::runPart2()
{
	std::string line;

	std::pair<int, int> startPos;

	int height = 0;

	std::unordered_set<std::pair<int, int>, pair_hash> splits;

	while (std::getline(*input, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (line.at(i) == 'S')
				startPos = { height, i };
			else if (line.at(i) == '^')
			{
				splits.insert({ height, i });
			}
		}
		height++;
	}

	unsigned long long res = findNextSplit2(splits, startPos, height);

	return std::to_string(res);
}

