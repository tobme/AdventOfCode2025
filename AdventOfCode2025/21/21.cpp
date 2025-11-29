#include "21.h"

#include <iostream>
#include <algorithm>
#include<unordered_map>
#include "../Helpers/PairHash.h"
#include <queue>
std::unordered_map<char, std::pair<int, int>> keyPad = { {'7', {0,0}}, {'8', {0,1}}, {'9', {0,2}}, {'4', {1,0}}, {'5', {1,1}}, {'6', {1,2}}, {'1', {2,0}}, {'2', {2,1}}, {'3', {2,2}}, {'0', {3,1}}, {'A', {3,2}} };
std::unordered_map<char, std::pair<int, int>> dirKeyPad = { {'^', {0,1}}, {'A', {0,2}}, {'<', {1,0}}, {'v', {1,1}}, {'>', {1,2}} };
std::unordered_map<std::pair<int, int>, char, pair_hash> revDirKeyPad = { {{0,1}, '^'}, {{0,2}, 'A'}, {{1,0}, '<'}, {{1,1}, 'v'}, {{1,2}, '>'} };

Day21::Day21(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::vector<char> moveHelper(const std::pair<int, int>& currPos, const std::pair<int, int>& goalPos)
{
	std::vector<char> ret;
	if (currPos.first > goalPos.first)
	{
		ret.push_back('^');
	}
	else if (currPos.first < goalPos.first)
	{
		ret.push_back('v');
	}

	if (currPos.second > goalPos.second)
	{
		ret.push_back('<');
	}
	else if (currPos.second < goalPos.second)
	{
		ret.push_back('>');
	}

	return ret;
}

struct cmp
{
	bool operator()(const std::tuple<int, int, std::string>& l, const std::tuple<int, int, std::string>& r) {
		return std::get<2>(l).size() > std::get<2>(r).size();
	}
};

std::unordered_map < std::string, std::pair<std::string, std::pair<int,int>> > memory;
std::unordered_map<char, std::pair<int, int>> dirHelper = { {'>', {0,1}}, {'v', {1,0}}, {'<', {0,-1}}, {'^', {-1,0}} };
std::pair<int, int> level0Pos = { 0,2 };

std::pair<std::string, std::pair<int,int>> move(std::pair<int,int>& pos, char goalC, const std::unordered_map<char, std::pair<int,int>>& keyPad, int currLayer, int maxLayer)
{
	const std::pair<int, int> goalPos = keyPad.at(goalC);

	if (currLayer == maxLayer)
	{
		return { std::string(1, revDirKeyPad[goalPos]), goalPos };
	}

	std::string id = std::to_string(pos.first) + "_" + std::to_string(pos.second) + ":" + std::to_string(goalPos.first) + "_" + std::to_string(goalPos.second) + ":" + std::to_string(currLayer) + "0_2";

	if (memory.contains(id))
		return memory[id];

	std::string res = "";
	std::vector<std::pair<std::string, std::pair<int,int>>> resV;

	std::queue< std::tuple<int, int, std::string, std::pair<int,int>>> queue;

	std::pair<int, int> startPos = { 0,2 };
	queue.push({ pos.first, pos.second, "", startPos });

	while (!queue.empty())
	{
		auto front = queue.front();
		queue.pop();

		if (std::get<0>(front) == goalPos.first && std::get<1>(front) == goalPos.second)
		{
			auto tmp = move(std::get<3>(front), 'A', dirKeyPad, currLayer + 1, maxLayer);
			resV.push_back({ std::get<2>(front) + tmp.first, std::get<3>(front) });
		}
		else
		{
			auto dV = moveHelper({std::get<0>(front), std::get<1>(front)}, goalPos);

			for (auto d : dV)
			{
				auto newRow = std::get<0>(front) + dirHelper[d].first;
				auto newCol = std::get<1>(front) + dirHelper[d].second;

				std::string tmpId = std::string(1, d) + ":" + std::to_string(currLayer) + ":" + std::to_string(std::get<3>(front).first) + "_" + std::to_string(std::get<3>(front).second);
				std::pair<std::string, std::pair<int, int>> tmp;
				
				if (memory.contains(tmpId))
					tmp = memory[tmpId];
				else
					tmp = move(std::get<3>(front), d, dirKeyPad, currLayer + 1, maxLayer);

				memory[tmpId] = tmp;

				std::string tmpId2 = std::to_string(pos.first) + "_" + std::to_string(pos.second) + ":" + std::to_string(newRow) + "_" + std::to_string(newCol) + ":" + std::to_string(currLayer) + std::to_string(tmp.second.first) + "_" + std::to_string(tmp.second.second);

				if (memory.contains(tmpId2))
				{
					if (memory[tmpId2].first.size() > tmp.first.size() + std::get<2>(front).size())
						memory[tmpId2] = { tmp.first + std::get<2>(front), tmp.second };
				}
				else
					memory[tmpId2] = { tmp.first + std::get<2>(front), tmp.second };

				std::string tmpId3 = std::to_string(std::get<0>(front)) + "_" + std::to_string(std::get<1>(front)) + ":" + std::to_string(newRow) + "_" + std::to_string(newCol) + ":" + std::to_string(currLayer) + std::to_string(tmp.second.first) + "_" + std::to_string(tmp.second.second);

				if (memory.contains(tmpId3))
				{
					if (memory[tmpId3].first.size() > tmp.first.size())
						memory[tmpId3] = tmp;
				}
				else
					memory[tmpId3] = tmp;

				if ((currLayer == 0 && (newRow != 3 || newCol != 0)) || (currLayer != 0 && (newRow != 0 || newCol != 0)))
					queue.push({ newRow, newCol, std::get<2>(front) + tmp.first, tmp.second });
			}
		}
	}
	std::pair<int, int> levelAbovePos = { 0,2 };
	if (!resV.empty())
	{
		auto it = std::min_element(resV.begin(), resV.end(), [](const auto& s, const auto& s2) { return s.first.size() < s2.first.size(); });
		res = it->first;
		levelAbovePos = it->second;
	}

	memory[id] = { res, goalPos };

	return { res, goalPos };
}

std::unordered_map < std::string, std::pair<unsigned long long, std::pair<int, int>> > memory2;

std::pair<unsigned long long, std::pair<int, int>> move2(std::pair<int, int>& pos, char goalC, const std::unordered_map<char, std::pair<int, int>>& keyPad, int currLayer, int maxLayer)
{
	const std::pair<int, int> goalPos = keyPad.at(goalC);

	if (currLayer == maxLayer)
	{
		return { 1, goalPos };
	}

	std::string id = std::to_string(pos.first) + "_" + std::to_string(pos.second) + ":" + std::to_string(goalPos.first) + "_" + std::to_string(goalPos.second) + ":" + std::to_string(currLayer) + "0_2";

	if (memory.contains(id))
		return memory2[id];

	unsigned long long res = 0;
	std::vector<std::pair<unsigned long long, std::pair<int, int>>> resV;

	std::queue< std::tuple<int, int, unsigned long long, std::pair<int, int>>> queue;

	std::pair<int, int> startPos = { 0,2 };
	queue.push({ pos.first, pos.second, 0, startPos });

	while (!queue.empty())
	{
		auto front = queue.front();
		queue.pop();

		if (std::get<0>(front) == goalPos.first && std::get<1>(front) == goalPos.second)
		{
			auto tmp = move2(std::get<3>(front), 'A', dirKeyPad, currLayer + 1, maxLayer);
			resV.push_back({ std::get<2>(front) + tmp.first, std::get<3>(front) });
		}
		else
		{
			auto dV = moveHelper({ std::get<0>(front), std::get<1>(front) }, goalPos);

			for (auto d : dV)
			{
				auto newRow = std::get<0>(front) + dirHelper[d].first;
				auto newCol = std::get<1>(front) + dirHelper[d].second;

				std::string tmpId = std::string(1, d) + ":" + std::to_string(currLayer) + ":" + std::to_string(std::get<3>(front).first) + "_" + std::to_string(std::get<3>(front).second);
				std::pair<unsigned long long, std::pair<int, int>> tmp;

				if (memory2.contains(tmpId))
					tmp = memory2[tmpId];
				else
					tmp = move2(std::get<3>(front), d, dirKeyPad, currLayer + 1, maxLayer);

				memory2[tmpId] = tmp;

				if ((currLayer == 0 && (newRow != 3 || newCol != 0)) || (currLayer != 0 && (newRow != 0 || newCol != 0)))
					queue.push({ newRow, newCol, std::get<2>(front) + tmp.first, tmp.second });
			}
		}
	}
	std::pair<int, int> levelAbovePos = { 0,2 };
	if (!resV.empty())
	{
		auto it = std::min_element(resV.begin(), resV.end(), [](const auto& s, const auto& s2) { return s.first < s2.first; });
		res = it->first;
		levelAbovePos = it->second;
	}

	memory2[id] = { res, goalPos };

	return { res, goalPos };
}

std::string Day21::runPart1()
{
	std::string s;
	
	unsigned long long totRes = 0;
	std::pair<int, int> dirKeyPadPos = { 0,2 };
	std::pair<int, int> keyPadPos = { 3,2 };

	std::vector < std::pair<int, int>> dirKeyPadPosses{ 3, dirKeyPadPos};
	dirKeyPadPosses[0] = keyPadPos;
	while (std::getline(*input, s))
	{
		std::string numberId = s;
		numberId.pop_back();
		unsigned long long numberIdI = std::stoull(numberId);
		std::string res = "";

		for (auto& c : s)
		{
			std::pair<int, int> goalPos = keyPad[c];

			auto tmp = move(keyPadPos, c, keyPad, 0, 3);
			keyPadPos = tmp.second;

			res += tmp.first;
		}
		auto size = res.size();
		totRes += size * numberIdI;
	}
	return std::to_string(totRes);
}



std::string Day21::runPart2()
{
	std::string s;

	unsigned long long totRes = 0;
	std::pair<int, int> dirKeyPadPos = { 0,2 };
	std::pair<int, int> keyPadPos = { 3,2 };

	std::vector < std::pair<int, int>> dirKeyPadPosses{ 3, dirKeyPadPos };
	dirKeyPadPosses[0] = keyPadPos;
	while (std::getline(*input, s))
	{
		std::string numberId = s;
		numberId.pop_back();
		unsigned long long numberIdI = std::stoull(numberId);
		unsigned long long res = 0;

		for (auto& c : s)
		{
			std::pair<int, int> goalPos = keyPad[c];

			auto tmp = move2(keyPadPos, c, keyPad, 0, 26);
			keyPadPos = tmp.second;

			res += tmp.first;
		}
		auto size = res;
		totRes += size * numberIdI;
	}
	return std::to_string(totRes);
}

