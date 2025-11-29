#include "8.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"
#include <unordered_map>
#include <unordered_set>
#include "../Helpers/PairHash.h"

Day8::Day8(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day8::runPart1()
{
	std::unordered_map<char, std::vector<std::pair<int, int>>> map;
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int col = 0; col < matrix.at(row).size(); col++)
		{
			if (matrix[row][col] != '.')
			{
				map[matrix[row][col]].push_back({ row, col });
			}
		}
	}

	std::unordered_set<std::pair<int, int>, pair_hash> antinodes;

	for (auto& nodes : map)
	{
		for (int i = 0; i < nodes.second.size(); i++)
		{
			for (int j = i+1; j < nodes.second.size(); j++)
			{
				int row = nodes.second.at(j).first - nodes.second.at(i).first;
				int col = nodes.second.at(j).second - nodes.second.at(i).second;

				std::pair<int, int> ref1 = { nodes.second.at(i).first - row, nodes.second.at(i).second - col };
				std::pair<int, int> ref2 = { nodes.second.at(j).first + row, nodes.second.at(j).second + col };

				if (ref1.first >= 0 && ref1.first < matrix.size() && ref1.second >= 0 && ref1.second < matrix.size())
				{
					antinodes.insert(ref1);
				}

				if (ref2.first >= 0 && ref2.first < matrix.front().size() && ref2.second >= 0 && ref2.second < matrix.size())
				{
					antinodes.insert(ref2);
				}
			}
		}
	}

	return std::to_string(antinodes.size());
}

std::string Day8::runPart2()
{
	std::unordered_map<char, std::vector<std::pair<int, int>>> map;
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int col = 0; col < matrix.at(row).size(); col++)
		{
			if (matrix[row][col] != '.')
			{
				map[matrix[row][col]].push_back({ row, col });
			}
		}
	}

	std::unordered_set<std::pair<int, int>, pair_hash> antinodes;

	for (auto& nodes : map)
	{
		for (int i = 0; i < nodes.second.size(); i++)
		{
			for (int j = i + 1; j < nodes.second.size(); j++)
			{
				int rowD = nodes.second.at(j).first - nodes.second.at(i).first;
				int colD = nodes.second.at(j).second - nodes.second.at(i).second;

				int rowStart = nodes.second.at(i).first;
				int colStart = nodes.second.at(i).second;

				std::pair<int, int> ref1 = { rowStart, colStart };

				while (ref1.first >= 0 && ref1.first < matrix.front().size() && ref1.second >= 0 && ref1.second < matrix.size())
				{
					antinodes.insert(ref1);
					ref1.first -= rowD;
					ref1.second -= colD;
				}

				rowStart = nodes.second.at(j).first;
				colStart = nodes.second.at(j).second;

				std::pair<int, int> ref2 = { rowStart, colStart };

				while (ref2.first >= 0 && ref2.first < matrix.front().size() && ref2.second >= 0 && ref2.second < matrix.size())
				{
					antinodes.insert(ref2);
					ref2.first += rowD;
					ref2.second += colD;
				}
			}
		}
	}

	return std::to_string(antinodes.size());
}

