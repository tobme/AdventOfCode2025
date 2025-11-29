#include "6.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"
#include <unordered_set>
#include "../Helpers/PairHash.h"

namespace {

	std::vector < std::pair<int, int>> dirHelper = { {-1,0}, {0, 1}, {1, 0}, {0, -1} };

	bool move(std::pair<int,int>& pos, int dir, const std::vector<std::vector<char>>& matrix, const std::pair<int,int>& newObs = {-1,-1})
	{
		std::pair<int, int> newPos = { pos.first + dirHelper.at(dir).first, pos.second + dirHelper.at(dir).second };

		if ((0 <= newPos.first && newPos.first < matrix.size() && 0 <= newPos.second && newPos.second < matrix.front().size()) == false)
		{
			pos = newPos;
			return false;
		}
		if (matrix[newPos.first][newPos.second] == '#' || newPos == newObs)
			return false;

		pos = newPos;
		return true;
	}

	int rotate(int dir)
	{
		return (dir + 1) % 4;
	}
}

Day6::Day6(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day6::runPart1()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	std::pair<int, int> pos;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			if (matrix[row][column] == '^')
			{
				pos = std::pair<int, int>(row, column);
			}

		}
	}

	std::unordered_set<std::pair<int, int>, pair_hash> path;
	path.insert(pos);

	int dir = 0;

	while (0 <= pos.first && pos.first < matrix.size() && 0 <= pos.second && pos.second < matrix.front().size())
	{
		//Util::print(matrix, pos);

		auto moved = move(pos, dir, matrix);

		if (!moved)
		{
			dir = rotate(dir);
		}
		else
		{
			path.insert(pos);
		}
	}

	int res = path.size();

	return std::to_string(res);
}

bool simulate(const std::vector<std::vector<char>>& matrix, std::pair<int, int> pos, int dir, const std::pair<int,int>& newObs)
{
	std::unordered_set<std::string> path;
	path.insert(std::to_string(pos.first) + "_" + std::to_string(pos.second) + "_" + std::to_string(dir));

	while (0 <= pos.first && pos.first < matrix.size() && 0 <= pos.second && pos.second < matrix.front().size())
	{

		auto moved = move(pos, dir, matrix, newObs);

		std::string pathS = std::to_string(pos.first) + "_" + std::to_string(pos.second) + "_" + std::to_string(dir % 4);

		if (path.contains(pathS) && moved)
			return true;

		if (!moved)
		{
			dir = rotate(dir);
		}
		else
		{
			path.insert(pathS);
		}
	}
	return false;
}

std::string Day6::runPart2()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	std::pair<int, int> startPos;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			if (matrix[row][column] == '^')
			{
				startPos = std::pair<int, int>(row, column);
			}

		}
	}

	int dir = 0;
	auto pos = startPos;
	int res = 0;

	// Run part 1!

	std::unordered_set<std::pair<int, int>, pair_hash> path;
	path.insert(pos);

	while (0 <= pos.first && pos.first < matrix.size() && 0 <= pos.second && pos.second < matrix.front().size())
	{
		//Util::print(matrix, pos);

		auto moved = move(pos, dir, matrix);

		if (!moved)
		{
			dir = rotate(dir);
		}
		else
		{
			path.insert(pos);
		}
	}

	dir = 0;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			// skippa om inte med på vägen
			if (path.contains({row, column}))
				res += simulate(matrix, startPos, dir, { row, column });
		}
	}


	return std::to_string(res);
}

