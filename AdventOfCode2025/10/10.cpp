#include "10.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include "../Helpers/PairHash.h"

Day10::Day10(std::shared_ptr<IInput>& _input) : input(_input)
{}

class HikePos
{
public:
	std::pair<int, int> pos;
	int height;
	std::pair<int, int> startPos;
};

std::string Day10::runPart1()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");
	std::vector<std::pair<int, int>> dir = { {0,1}, {1,0}, {0,-1}, {-1, 0} };

	std::queue<HikePos> queue;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			if (matrix[i][j] == '0')
				queue.push(HikePos({ i,j }, 0, {i , j}));
		}
	}

	std::unordered_map<std::pair<int,int>, std::unordered_set<std::pair<int, int>, pair_hash>, pair_hash> res;

	while (!queue.empty())
	{
		auto front = queue.front();
		queue.pop();
		
		if (front.height == 9)
		{
			res[front.startPos].insert(front.pos);
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				std::pair<int, int> newPos = { front.pos.first - dir[i].first, front.pos.second - dir[i].second };
				if ((newPos.first >= 0 && newPos.first < matrix.size() && newPos.second >= 0 && newPos.second < matrix.front().size()) && (matrix[newPos.first][newPos.second] - '0') == front.height + 1)
				{
					queue.push(HikePos(newPos, front.height + 1, front.startPos));
				}
			}
		}
	}

	int res2 = 0;

	for (auto& t : res)
	{
		res2 += t.second.size();
	}

	return std::to_string(res2);
}

std::string Day10::runPart2()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");
	std::vector<std::pair<int, int>> dir = { {0,1}, {1,0}, {0,-1}, {-1, 0} };

	std::queue<HikePos> queue;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			if (matrix[i][j] == '0')
				queue.push(HikePos({ i,j }, 0, { i , j }));
		}
	}

	int res = 0;

	while (!queue.empty())
	{
		auto front = queue.front();
		queue.pop();

		if (front.height == 9)
		{
			res++;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				std::pair<int, int> newPos = { front.pos.first - dir[i].first, front.pos.second - dir[i].second };
				if ((newPos.first >= 0 && newPos.first < matrix.size() && newPos.second >= 0 && newPos.second < matrix.front().size()) && (matrix[newPos.first][newPos.second] - '0') == front.height + 1)
				{
					queue.push(HikePos(newPos, front.height + 1, front.startPos));
				}
			}
		}
	}

	return std::to_string(res);
}

