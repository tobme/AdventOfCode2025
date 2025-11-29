#include "20.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"
#include "../Helpers/PairHash.h"
#include<unordered_set>
#include<queue>
#include<unordered_map>

#include<map>

Day20::Day20(std::shared_ptr<IInput>& _input) : input(_input)
{}

class Racer
{
public:
	Racer(const std::pair<int, int>& _p, int _s, int _w) : pos(_p), score(_s), wallWalked(_w) {}

	std::pair<int, int> pos;
	int score;
	int wallWalked;

	bool operator<(const Racer& r) const
	{
		return r.score < this->score;
	}
};

struct StateHash {
	size_t operator()(const std::tuple<int, int, int, int>& state) const {
		return std::hash<int>()(std::get<0>(state)) ^
			(std::hash<int>()(std::get<1>(state)) << 1) ^
			(std::hash<int>()(std::get<2>(state) << 2)) ^
			(std::hash<int>()(std::get<3>(state) << 3));
	}
};

std::string Day20::runPart1()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	std::pair<int, int> pos;
	std::pair<int, int> goal;
	std::unordered_set<std::pair<int, int>, pair_hash> walls;
	std::unordered_map<std::pair<int, int>, int, pair_hash> visited;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			if (matrix[i][j] == 'S')
				pos = { i,j };
			else if (matrix[i][j] == 'E')
				goal = { i,j };
			else if (matrix[i][j] == '#')
				walls.insert({ i,j });
		}
	}

	visited[goal] = 0;

	std::priority_queue<Racer> queue;

	std::vector<std::pair<int, int>> dirHelper = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	int res = 999999;

	queue.push(Racer(goal, 0, true));

	while (!queue.empty())
	{
		auto front = queue.top();
		queue.pop();

		if (front.pos == pos)
		{
			res = std::min(res, front.score);
		}

		for (int i = 0; i < dirHelper.size(); i++)
		{
			std::pair<int, int> newPos = { front.pos.first + dirHelper[i].first, front.pos.second + dirHelper[i].second };

			if (!walls.contains(newPos))
			{
				if (!visited.contains(newPos))
				{
					visited[newPos] = front.score + 1;
					queue.push(Racer(newPos, front.score + 1, front.wallWalked));
				}
			}
		}
	}

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			if (walls.contains({ i,j }))
				std::cout << "##";
			else if (visited.contains({ i,j }))
			{
				auto v = visited[{i, j}];
				if (v < 10)
					std::cout << ".";
				std::cout << v;
			}
				
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}

	int goalScore = res - 100;

	queue.push(Racer(pos, 0, false));
	std::unordered_set<std::pair<int, int>, pair_hash> path;
	path.insert(pos);

	int totScore = 0;

	while (!queue.empty())
	{
		auto front = queue.top();
		queue.pop();

		if (front.score == goalScore)
		{
			continue;
		}

		for (int i = 0; i < dirHelper.size(); i++)
		{
			std::pair<int, int> newPos = { front.pos.first + dirHelper[i].first, front.pos.second + dirHelper[i].second };

			if (!walls.contains(newPos))
			{
				if (!path.contains(newPos))
				{
					path.insert(newPos);
					queue.push(Racer(newPos, front.score + 1, front.wallWalked));
				}
			}
			else if (walls.contains(newPos))
			{
				for (int j = 0; j < dirHelper.size(); j++)
				{
					std::pair<int,int> wallPos = {newPos.first + dirHelper[j].first, newPos.second + dirHelper[j].second };

					if (wallPos.first > 0 && wallPos.first < matrix.size() && wallPos.second > 0 && wallPos.second < matrix.front().size() && !walls.contains(wallPos) && wallPos != front.pos)
					{
						int newScore = front.score + 2 + visited[wallPos];

						if (newScore <= goalScore)
							totScore++;
					}
				}
			}
		}
	}

	return std::to_string(totScore);
}

std::string Day20::runPart2()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	std::pair<int, int> pos;
	std::pair<int, int> goal;
	std::unordered_set<std::pair<int, int>, pair_hash> walls;
	std::unordered_map<std::pair<int, int>, int, pair_hash> visited;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			if (matrix[i][j] == 'S')
				pos = { i,j };
			else if (matrix[i][j] == 'E')
				goal = { i,j };
			else if (matrix[i][j] == '#')
				walls.insert({ i,j });
		}
	}

	visited[goal] = 0;

	std::priority_queue<Racer> queue;

	std::vector<std::pair<int, int>> dirHelper = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	int res = 999999;

	queue.push(Racer(goal, 0, true));

	while (!queue.empty())
	{
		auto front = queue.top();
		queue.pop();

		if (front.pos == pos)
		{
			res = std::min(res, front.score);
		}

		for (int i = 0; i < dirHelper.size(); i++)
		{
			std::pair<int, int> newPos = { front.pos.first + dirHelper[i].first, front.pos.second + dirHelper[i].second };

			if (!walls.contains(newPos))
			{
				if (!visited.contains(newPos))
				{
					visited[newPos] = front.score + 1;
					queue.push(Racer(newPos, front.score + 1, front.wallWalked));
				}
			}
		}
	}

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			if (walls.contains({ i,j }))
				std::cout << "##";
			else if (visited.contains({ i,j }))
			{
				auto v = visited[{i, j}];
				if (v < 10)
					std::cout << ".";
				std::cout << v;
			}

			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}

	int goalScore = res - 100;

	std::unordered_set<std::tuple<int,int,int,int>, StateHash> resTot;

	std::map<int, int> debug;

	for (auto& p : visited)
	{
		if (res - p.second > goalScore)
			continue;

		queue.push(Racer(p.first, res - p.second, 0));

		std::pair<int, int> startPos = p.first;

		std::unordered_set<std::pair<int, int>, pair_hash> path;
		path.insert(startPos);

		while (!queue.empty())
		{
			auto front = queue.top();
			queue.pop();

			if (front.score > goalScore)
			{
				continue;
			}

			if (!walls.contains(front.pos))
			{
				int newScore = front.score + visited[front.pos];
				if (newScore <= goalScore && !resTot.contains({ startPos.first, startPos.second, front.pos.first, front.pos.second }))
				{
					debug[res - newScore]++;
					resTot.insert({ startPos.first, startPos.second, front.pos.first, front.pos.second });
				}
			}

			for (int i = 0; i < dirHelper.size(); i++)
			{
				std::pair<int, int> newPos = { front.pos.first + dirHelper[i].first, front.pos.second + dirHelper[i].second };

				if (newPos.first >= 0 && newPos.first < matrix.size() && newPos.second >= 0 && newPos.second < matrix.front().size() && !walls.contains(newPos) && !path.contains(newPos) && front.wallWalked < 20)
				{
					path.insert(newPos);
					queue.push(Racer(newPos, front.score + 1, front.wallWalked + 1));
				}
				else if (walls.contains(newPos) && front.wallWalked < 20)
				{
					if (newPos.first >= 0 && newPos.first < matrix.size() && newPos.second >= 0 && newPos.second < matrix.front().size() && !path.contains(newPos))
					{
						path.insert(newPos);
						queue.push(Racer(newPos, front.score + 1, front.wallWalked + 1));
					}
				}
			}
		}
	}

	for (auto& i : debug)
	{
		std::cout << "There are " << i.second << " Saved: " << i.first << std::endl;
	}

	return std::to_string(resTot.size());
}

