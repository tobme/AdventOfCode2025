#include "12.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"
#include<unordered_set>
#include<queue>
#include "../Helpers/PairHash.h"
#include "../Helpers/Utilities.h"
#include <unordered_map>

Day12::Day12(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day12::runPart1()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	std::vector<std::pair<int, int>> dir = { {0,1}, {1,0}, {0,-1}, {-1,0} };

	std::queue<std::pair<int, int>> queue;
	std::unordered_set<std::pair<int, int>, pair_hash> visited;
	std::unordered_map<std::string, int> fence;
	std::unordered_map<std::string, int> area;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int col = 0; col < matrix.at(row).size(); col++)
		{
			if (visited.count({ row,col }))
				continue;

			queue.push({ row,col });

			while (!queue.empty())
			{
				auto pos = queue.front();
				queue.pop();

				if (visited.count(pos))
					continue;

				std::string id = std::to_string(row) + "_" + std::to_string(col) + "_" + std::string{matrix[pos.first][pos.second]};

				area[id]++;
				visited.insert(pos);

				for (int i = 0; i < dir.size(); i++)
				{
					std::pair<int, int> newPos = { pos.first + dir[i].first, pos.second + dir[i].second };
					if (Util::isInBounds(newPos, matrix) && !visited.contains(newPos) && matrix[pos.first][pos.second] == matrix[newPos.first][newPos.second])
					{
						queue.push(newPos);
					}
					else if (!Util::isInBounds(newPos, matrix) || matrix[pos.first][pos.second] != matrix[newPos.first][newPos.second])
					{
						fence[id]++;
					}
				}
			}
		}
	}

	int res = 0;

	for (auto& r : area)
	{
		res += r.second * fence[r.first];
	}

	return std::to_string(res);
}

std::string Day12::runPart2()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	std::vector<std::pair<int, int>> dir = { {0,1}, {1,0}, {0,-1}, {-1,0} };

	std::queue<std::pair<int, int>> queue;
	std::unordered_set<std::pair<int, int>, pair_hash> visited;
	std::unordered_map<std::string, std::unordered_set<std::string>> fence;
	std::unordered_map<std::string, int> area;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int col = 0; col < matrix.at(row).size(); col++)
		{
			if (visited.count({ row,col }))
				continue;

			queue.push({ row,col });

			while (!queue.empty())
			{
				auto pos = queue.front();
				queue.pop();

				if (visited.count(pos))
					continue;

				std::string id = std::to_string(row) + "_" + std::to_string(col) + "_" + std::string{ matrix[pos.first][pos.second] };

				area[id]++;
				visited.insert(pos);

				for (int i = 0; i < dir.size(); i++)
				{
					std::pair<int, int> newPos = { pos.first + dir[i].first, pos.second + dir[i].second };
					if (Util::isInBounds(newPos, matrix) && !visited.contains(newPos) && matrix[pos.first][pos.second] == matrix[newPos.first][newPos.second])
					{
						queue.push(newPos);
					}
					else if (!Util::isInBounds(newPos, matrix) || matrix[pos.first][pos.second] != matrix[newPos.first][newPos.second])
					{
						std::string id2 = std::to_string(newPos.first) + "," + std::to_string(newPos.second) + "_" + std::to_string(i);
						fence[id].insert(id2);
					}
				}
			}
		}
	}

	std::unordered_map<std::string, int> sides;
	std::queue<std::string> queue2;

	for (auto& r : fence)
	{
		auto& fencePositions = r.second;
		
		while (!r.second.empty())
		{
			std::unordered_set<std::string> visited2;
			auto rr = *r.second.begin();
			queue2.push(rr);

			while (!queue2.empty())
			{
				auto posString = queue2.front();

				auto t = Util::split(posString, "_");
				auto tt = Util::split(t[0], ",");
				std::pair<int, int> pos = { std::stoi(tt[0]), std::stoi(tt[1]) };
				std::string movingDir = t[1];

				queue2.pop();

				if (visited2.contains(posString))
					continue;

				visited2.insert(posString);

				for (int i = 0; i < dir.size(); i++)
				{
					std::pair<int, int> newPos = { pos.first + dir[i].first, pos.second + dir[i].second };
					std::string newPosId = std::to_string(newPos.first) + "," + std::to_string(newPos.second) + "_" + movingDir;
					if (r.second.contains(newPosId))
					{
						queue2.push(newPosId);
					}
				}
				auto it = r.second.find(posString);
				if (it != r.second.end())
					r.second.erase(it);
			}

			sides[r.first]++;
		}
		
	}

	unsigned long long res = 0;

	for (auto& r : area)
	{
		res += static_cast<unsigned long long>(r.second) * static_cast<unsigned long long>(sides[r.first]);
	}

	return std::to_string(res);
}

