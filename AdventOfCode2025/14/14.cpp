#include "14.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include "../Helpers/Utilities.h"
#include <unordered_set>
#include "../Helpers/PairHash.h"

Day14::Day14(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::pair<int, int> getPos(std::string& input)
{
	auto sss = Util::split(input, "=");
	auto ssss = Util::split(sss[1], ",");

	return { std::stoi(ssss[0]), std::stoi(ssss[1]) };
}

std::string Day14::runPart1()
{
	std::string s;

	int xMax = 101;
	int yMax = 103;

	int seconds = 100;

	std::vector<std::pair<int, int>> posV;

	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, " ");

		auto pos = getPos(ss[0]);
		auto v = getPos(ss[1]);

		pos.first += (xMax * 1000);
		pos.second += (yMax * 1000);

		int newX = (pos.first + (v.first * seconds)) % xMax;
		int newY = (pos.second + (v.second * seconds)) % yMax;

		posV.push_back({ newX, newY });
	}

	std::vector<int> quadCounter{ 0,0,0,0 };

	int xHalf = xMax / 2;
	int yHalf = yMax / 2;

	for (auto& p : posV)
	{
		if (p.first < xHalf)
		{
			if (p.second < yHalf)
			{
				quadCounter[0]++;
			}
			else if (p.second > yHalf)
			{
				quadCounter[1]++;
			}
		}
		else if (p.first > xHalf)
		{
			if (p.second < yHalf)
			{
				quadCounter[2]++;
			}
			else if (p.second > yHalf)
			{
				quadCounter[3]++;
			}
		}
	}

	int res = 1;
	for (auto i : quadCounter)
	{
		res *= i;
	}

	return std::to_string(res);
}

class Robot
{
public:
	Robot(const std::pair<int,int>& _pos, const std::pair<int, int>& _v) : pos(_pos), v(_v) {}
	std::pair<int, int> pos;
	std::pair<int, int> v;
};

std::string Day14::runPart2()
{
	std::string s;

	int xMax = 101;
	int yMax = 103;

	int seconds = 100;

	std::vector<std::unique_ptr<Robot>> posV;

	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, " ");

		auto pos = getPos(ss[0]);
		auto v = getPos(ss[1]);

		posV.push_back(std::make_unique<Robot>(Robot(pos, v)));
	}

	int xHalf = xMax / 2;
	int yHalf = yMax / 2;

	std::vector<std::pair<int, int>> dirHelper = { {1,0}, {0,1}, {-1,0}, {0,-1} };

	int lowestPos = 999999;
	int lowestIndex = 0;
	int loop = 0;
	for (; loop < xMax * yMax; loop++)
	{
		std::unordered_set<std::pair<int, int>, pair_hash> posss;

		for (auto& r : posV)
		{
			r->pos.first += r->v.first;
			r->pos.second += r->v.second;

			if (r->pos.first >= xMax)
			{
				r->pos.first -= xMax;
			}
			else if (r->pos.first < 0)
			{
				r->pos.first += xMax;
			}

			if (r->pos.second >= yMax)
			{
				r->pos.second -= yMax;
			}
			else if (r->pos.second < 0)
			{
				r->pos.second += yMax;
			}

			posss.insert(r->pos);
		}

		std::queue<std::pair<int, int>> queue;

		queue.push({ 20,20 });

		std::unordered_set<std::pair<int, int>, pair_hash> visited;
		visited.insert({ 20,20 });

		while (!queue.empty())
		{
			auto front = queue.front();
			queue.pop();

			for (int i = 0; i < 4; i++)
			{
				std::pair<int, int> newPos = { front.first + dirHelper[i].first, front.second + dirHelper[i].second };
				if (newPos.first >= 0 && newPos.first < xMax && newPos.second >= 0 && newPos.second < yMax && !posss.contains(newPos) && !visited.contains(newPos))
				{
					visited.insert(newPos);
					queue.push(newPos);
				}
			}
		}

		if (visited.size() < lowestPos)
		{
			lowestPos = visited.size();
			lowestIndex = loop;

			for (int row = 0; row < xMax; row++)
			{
				for (int col = 0; col < yMax; col++)
				{
					if (posss.contains({ row, col }))
						std::cout << "1";
					else
						std::cout << ".";
				}
				std::cout << std::endl;
			}

			std::cout << lowestIndex << std::endl << std::endl;

		}
	}



	return std::to_string(lowestIndex);
}

