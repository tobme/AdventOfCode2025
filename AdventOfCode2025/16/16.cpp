#include "16.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include "../Helpers/PairHash.h"
#include <unordered_map>

Day16::Day16(std::shared_ptr<IInput>& _input) : input(_input)
{}

class Chief
{
public:
	Chief() { }
	Chief(unsigned long long _s, const std::pair<int,int>& _p, int _d, const std::unordered_set<std::pair<int, int>,pair_hash>& _pa = std::unordered_set<std::pair<int, int>, pair_hash>()) : score(_s), pos(_p), dir(_d), path(_pa) {}
	unsigned long long score;
	std::pair<int, int> pos;
	int dir;
	std::unordered_set<std::pair<int, int>, pair_hash> path;

	bool operator()(const Chief& l, const Chief& r) const { return l.score > r.score; };
};


struct CompareTask {
	bool operator()(const Chief& l, const Chief& r) {
		return l.score > r.score;
	}
};

struct StateHash {
	size_t operator()(const std::tuple<int, int, int>& state) const {
		return std::hash<int>()(std::get<0>(state)) ^
			(std::hash<int>()(std::get<1>(state)) << 1) ^
			(std::hash<int>()(std::get<2>(state)) << 2);
	}
};


std::string Day16::runPart1()
{
	std::string s;

	std::unordered_set<std::pair<int, int>, pair_hash> walls;

	int rowIndex = 0;
	int rowSize = 0;

	std::pair<int, int> pos;
	std::pair<int, int> goal;

	while (std::getline(*input, s))
	{
		rowSize = s.size();
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '#')
			{
				walls.insert({ rowIndex, i });
			}
			else if (s[i] == 'E')
			{
				goal = { rowIndex, i };
			}
			else if (s[i] == 'S')
			{
				pos = { rowIndex, i };
			}
		}
		rowIndex++;
	}

	std::vector<std::pair<int, int>> dirHelper = { {0,1}, {1,0}, {0,-1}, {-1,0} };

	int dir = 0;

	std::priority_queue<Chief, std::vector<Chief>, CompareTask> queue;

	unsigned long long res = 0;

	Chief tmp;

	std::unordered_map<std::tuple<int, int, int>, unsigned long long, StateHash> visited;
	visited[{pos.first, pos.second, 0}] = 0;

	queue.push(Chief(0, pos, dir));

	while (!queue.empty())
	{
		Chief front = queue.top();
		queue.pop();

		if (front.pos == goal)
		{
			res = front.score;
			tmp = front;
			break;
		}

		for (int i = -1; i <= 1; i++)
		{
			int newDir = (front.dir + i) & 0x3;
			std::pair<int,int> newPos = { front.pos.first + dirHelper[newDir].first, front.pos.second + dirHelper[newDir].second };
			unsigned long long newScore = front.score + static_cast<unsigned long long>(i == 0 ? 1 : 1001);
			auto tuple = std::make_tuple(newPos.first, newPos.second, newDir);

			if (!walls.contains(newPos))
			{
				if (visited.contains(tuple) && visited[tuple] <= newScore)
					continue;
				visited[tuple] = newScore;
				queue.push(Chief(newScore, newPos, newDir));
			}
		}
	}

	return std::to_string(res);
}

std::string Day16::runPart2()
{
	std::string s;

	std::unordered_set<std::pair<int, int>, pair_hash> walls;

	int rowIndex = 0;
	int rowSize = 0;

	std::pair<int, int> pos;
	std::pair<int, int> goal;

	while (std::getline(*input, s))
	{
		rowSize = s.size();
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '#')
			{
				walls.insert({ rowIndex, i });
			}
			else if (s[i] == 'E')
			{
				goal = { rowIndex, i };
			}
			else if (s[i] == 'S')
			{
				pos = { rowIndex, i };
			}
		}
		rowIndex++;
	}

	std::vector<std::pair<int, int>> dirHelper = { {0,1}, {1,0}, {0,-1}, {-1,0} };

	int dir = 0;

	std::priority_queue<Chief, std::vector<Chief>, CompareTask> queue;

	unsigned long long res = 0;

	std::unordered_map<std::tuple<int, int, int>, unsigned long long, StateHash> visited;
	visited[{pos.first, pos.second, 0}] = 0;

	queue.push(Chief(0, pos, dir));

	std::vector<Chief> resV;

	while (!queue.empty())
	{
		Chief front = queue.top();
		queue.pop();

		front.path.insert(front.pos);

		if (front.pos == goal)
		{
			if (resV.empty())
			{
				resV.push_back(front);
			}
			else
			{
				if (front.score < resV[0].score)
				{
					resV.clear();
					resV.push_back(front);

				}
				else if (front.score == resV[0].score)
				{
					resV.push_back(front);
				}
			}
		}

		for (int i = -1; i <= 1; i++)
		{
			int newDir = (front.dir + i) & 0x3;
			std::pair<int, int> newPos = { front.pos.first + dirHelper[newDir].first, front.pos.second + dirHelper[newDir].second };
			unsigned long long newScore = front.score + static_cast<unsigned long long>(i == 0 ? 1 : 1001);
			auto tuple = std::make_tuple(newPos.first, newPos.second, newDir);

			if (!walls.contains(newPos))
			{
				if (visited.contains(tuple) && visited[tuple] < newScore)
					continue;
				visited[tuple] = newScore;
				queue.push(Chief(newScore, newPos, newDir, front.path));
			}
		}
	}

	std::unordered_set<std::pair<int, int>, pair_hash> resSet;

	for (auto& r : resV)
	{
		for (auto& bbb : r.path)
		{
			resSet.insert(bbb);
		}
	}

	return std::to_string(resSet.size());
}

