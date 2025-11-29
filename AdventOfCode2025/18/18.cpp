#include "18.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"
#include <unordered_set>
#include "../Helpers/PairHash.h"
#include "queue"

Day18::Day18(std::shared_ptr<IInput>& _input) : input(_input)
{}

struct cmp
{
	bool operator()(const std::tuple<int,int,int>& l, const std::tuple<int, int, int>& r) {
		return std::get<2>(l) > std::get<2>(r);
	}
};

struct cmp2
{
	bool operator()(const std::tuple<int, int, int, std::unordered_set<std::pair<int, int>, pair_hash>>& l, const std::tuple<int, int, int, std::unordered_set<std::pair<int, int>, pair_hash>>& r) {
		return std::get<2>(l) > std::get<2>(r);
	}
};

std::string Day18::runPart1()
{
	std::string s;

	std::unordered_set<std::pair<int, int>, pair_hash> corrupted;

	int width = 71, height = 71;

	int goalX = 70;
	int goalY = 70;

	int memoryIndex = 0;
	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, ",");

		corrupted.insert({ std::stoi(ss[0]), std::stoi(ss[1]) });

		memoryIndex++;
		if (memoryIndex == 1024)
			break;
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (corrupted.contains({ j,i }))
				std::cout << "#";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}

	std::priority_queue < std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, cmp> queue;

	std::vector<std::pair<int, int>> dirHelper = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	std::unordered_set<std::pair<int, int>, pair_hash> visited;
	visited.insert({ 0,0 });

	queue.push({ 0,0,0 });

	int res = 0;

	while (!queue.empty())
	{
		auto front = queue.top();
		queue.pop();

		if (std::get<0>(front) == goalX && std::get<1>(front) == goalY)
		{
			res = std::get<2>(front);
			break;
		}

		for (int i = 0; i < dirHelper.size(); i++)
		{
			int newX = std::get<0>(front) + dirHelper[i].first;
			int newY = std::get<1>(front) + dirHelper[i].second;
			if (!visited.contains({ newX, newY }) && !corrupted.contains({newX, newY}) && newX >= 0 && newX < width && newY >= 0 && newY < height)
			{
				visited.insert({ newX, newY });
				queue.push({ newX, newY, std::get<2>(front) + 1 });
			}
		}
	}

	return std::to_string(res);
}

std::string Day18::runPart2()
{
	std::string s;

	std::unordered_set<std::pair<int, int>, pair_hash> corrupted;

	int width = 71, height = 71;

	int goalX = 70;
	int goalY = 70;

	std::priority_queue < std::tuple<int, int, int, std::unordered_set<std::pair<int,int>,pair_hash>>, std::vector<std::tuple<int, int, int, std::unordered_set<std::pair<int, int>, pair_hash>>>, cmp2> queue;

	std::vector<std::pair<int, int>> dirHelper = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	std::unordered_set<std::pair<int, int>, pair_hash> visited;
	std::unordered_set<std::pair<int, int>, pair_hash> goalPath;

	bool first = true;

	int res = 0;

	std::pair<int, int> corruptedCoords;

	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, ",");

		corruptedCoords = { std::stoi(ss[0]), std::stoi(ss[1]) };
		corrupted.insert(corruptedCoords);

		if (!goalPath.contains(corruptedCoords) && !first)
		{
			continue;
		}
		first = false;

		visited.clear();
		visited.insert({ 0,0 });

		while (!queue.empty())
			queue.pop();

		queue.push({ 0,0,0, std::unordered_set<std::pair<int,int>,pair_hash>()});

		bool foundGoal = false;

		while (!queue.empty())
		{
			auto front = queue.top();
			queue.pop();

			auto& path = std::get<3>(front);
			path.insert({ std::get<0>(front), std::get<1>(front) });

			if (std::get<0>(front) == goalX && std::get<1>(front) == goalY)
			{
				goalPath = std::get<3>(front);
				foundGoal = true;
				break;
			}

			for (int i = 0; i < dirHelper.size(); i++)
			{
				int newX = std::get<0>(front) + dirHelper[i].first;
				int newY = std::get<1>(front) + dirHelper[i].second;
				if (!visited.contains({ newX, newY }) && !corrupted.contains({ newX, newY }) && newX >= 0 && newX < width && newY >= 0 && newY < height)
				{
					visited.insert({ newX, newY });
					queue.push({ newX, newY, std::get<2>(front) + 1, std::get<3>(front)});
				}
			}
		}

		if (!foundGoal)
			break;
	}

	return std::to_string(corruptedCoords.first) + "," + std::to_string(corruptedCoords.second);
}

