#include "15.h"

#include <iostream>
#include <algorithm>
#include<unordered_set>
#include "../Helpers/PairHash.h"
#include <unordered_map>

Day15::Day15(std::shared_ptr<IInput>& _input) : input(_input)
{}



bool moveRocks(const std::pair<int, int>& pos, std::unordered_set<std::pair<int, int>, pair_hash>& rocks, const std::unordered_set<std::pair<int, int>, pair_hash>& walls, std::unordered_map<char, std::pair<int, int>>& dirHelper, char dir)
{
	std::pair<int, int> newRockPos = { pos.first + dirHelper[dir].first, pos.second + dirHelper[dir].second };

	if (walls.contains(newRockPos))
	{
		return false;
	}
	else if (rocks.contains(newRockPos))
	{
		return moveRocks(newRockPos, rocks, walls, dirHelper, dir);
	}
	else
	{
		rocks.insert(newRockPos);
		return true;
	}
}

std::string Day15::runPart1()
{
	std::string s;

	std::vector<std::string> matrix;

	int rowIndex = 0;
	std::unordered_set<std::pair<int, int>, pair_hash> rocks;
	std::unordered_set<std::pair<int, int>, pair_hash> walls;

	std::pair<int, int> pos;

	int rowSize = 0;

	while (input->peek() != '\n')
	{
		std::getline(*input, s);

		rowSize = s.size();

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '#')
			{
				walls.insert({ rowIndex, i });
			}
			else if (s[i] == 'O')
			{
				rocks.insert({ rowIndex, i });
			}
			else if (s[i] == '@')
			{
				pos = { rowIndex, i };
			}
		}
		rowIndex++;
	}

	std::getline(*input, s);

	std::string moves;

	while (std::getline(*input, s))
	{
		moves.append(s);
	}
	

	std::unordered_map<char, std::pair<int, int>> dirHelper;
	dirHelper['<'] = { 0,-1 };
	dirHelper['>'] = { 0,1 };
	dirHelper['^'] = { -1,0 };
	dirHelper['v'] = { 1,0 };

	int res = 0;

	for (auto move : moves)
	{
		std::pair<int, int> newPos = { pos.first + dirHelper[move].first, pos.second + dirHelper[move].second };

		if (!walls.contains(newPos))
		{
			if (rocks.contains(newPos))
			{
				if (moveRocks(newPos, rocks, walls, dirHelper, move))
				{
					rocks.erase(newPos);
					pos = newPos;
				}
			}
			else
			{
				pos = newPos;
			}
		}

		/*
		std::cout << move << std::endl;
		for (int i = 0; i < rowSize; i++)
		{
			for (int j = 0; j < rowIndex; j++)
			{
				if (walls.contains({ i,j }))
				{
					std::cout << "#";
				}
				else if (rocks.contains({ i,j }))
				{
					std::cout << "0";
				}
				else if (pos.first == i && pos.second == j)
				{
					std::cout << "@";
				}
				else
					std::cout << ".";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		*/
	}

	for (auto& t : rocks)
	{
		res += t.first * 100 + t.second;
	}


	return std::to_string(res);
}

class Rocks
{
public:
	Rocks(const std::pair<int, int>& _p, const std::pair<int, int>& _p2) : pos(_p), pos2(_p2) {}
	std::pair<int, int> pos;
	std::pair<int, int> pos2;

	bool intersects(const Rocks& r) const
	{
		return r.pos == this->pos || r.pos == this->pos2 || r.pos2 == this->pos || r.pos2 == this->pos2;
	}

	bool intersects(const std::pair<int, int>& p) const
	{
		return p == this->pos || p == this->pos2;
	}

	void move(char dir, std::unordered_map<char, std::pair<int, int>>& dirHelper)
	{
		pos = { pos.first + dirHelper[dir].first, pos.second + dirHelper[dir].second };
		pos2 = { pos2.first + dirHelper[dir].first, pos2.second + dirHelper[dir].second };
	}
};

bool moveRocks2(Rocks* curRock, std::vector<std::unique_ptr<Rocks>>& rocks, const std::unordered_set<std::pair<int, int>, pair_hash>& walls, std::unordered_map<char, std::pair<int, int>>& dirHelper, char dir);

bool moveHelper(Rocks* curRock, Rocks& cpy, std::vector<std::unique_ptr<Rocks>>& rocks, const std::unordered_set<std::pair<int, int>, pair_hash>& walls, std::unordered_map<char, std::pair<int, int>>& dirHelper, char dir)
{
	bool intersected = true;
	for (std::unique_ptr<Rocks>& r : rocks)
	{
		if (curRock != r.get() && r->intersects(cpy))
		{
			 intersected &= moveRocks2(r.get(), rocks, walls, dirHelper, dir);
		}
	}
	return intersected;
}

bool moveRocks2(Rocks* curRock, std::vector<std::unique_ptr<Rocks>>& rocks, const std::unordered_set<std::pair<int, int>, pair_hash>& walls, std::unordered_map<char, std::pair<int, int>>& dirHelper, char dir)
{
	auto cpy = *curRock;
	cpy.move(dir, dirHelper);

	if (walls.contains(cpy.pos) || walls.contains(cpy.pos2))
	{
		return false;
	}

	bool insertected = moveHelper(curRock, cpy, rocks, walls, dirHelper, dir);

	if (insertected)
	{
		curRock->pos = cpy.pos;
		curRock->pos2 = cpy.pos2;

		return true;
	}

	return false;
}

Rocks* intersectsVector(std::vector<std::unique_ptr<Rocks>>& rocks, const std::pair<int,int>& p)
{
	for (auto& r : rocks)
	{
		if (r->intersects(p))
			return r.get();
	}
	return nullptr;
}

std::string Day15::runPart2()
{
	std::string s;

	std::vector<std::string> matrix;

	int rowIndex = 0;
	std::vector<std::unique_ptr<Rocks>> rocks;
	std::unordered_set<std::pair<int, int>, pair_hash> walls;

	std::pair<int, int> pos;

	int rowSize = 0;

	while (input->peek() != '\n')
	{
		std::getline(*input, s);

		rowSize = s.size();

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '#')
			{
				walls.insert({ rowIndex, i * 2 });
				walls.insert({ rowIndex, (i * 2) + 1 });
			}
			else if (s[i] == 'O')
			{
				rocks.push_back(std::make_unique<Rocks>( std::pair<int,int>( rowIndex, i * 2 ), std::pair<int,int>( rowIndex, (i * 2) + 1 ) ));
			}
			else if (s[i] == '@')
			{
				pos = { rowIndex, i * 2 };
			}
		}
		rowIndex++;
	}

	std::getline(*input, s);

	std::string moves;

	while (std::getline(*input, s))
	{
		moves.append(s);
	}

	std::unordered_map<char, std::pair<int, int>> dirHelper;
	dirHelper['<'] = { 0,-1 };
	dirHelper['>'] = { 0,1 };
	dirHelper['^'] = { -1,0 };
	dirHelper['v'] = { 1,0 };

	int res = 0;

	for (auto move : moves)
	{
		std::pair<int, int> newPos = { pos.first + dirHelper[move].first, pos.second + dirHelper[move].second };
		/*
		std::cout << move << std::endl;
		for (int i = 0; i < rowSize; i++)
		{
			for (int j = 0; j < rowIndex * 2; j++)
			{
				if (walls.contains({ i,j }))
				{
					std::cout << "#";
				}
				else if (std::find_if(rocks.begin(), rocks.end(), [&i, &j](std::unique_ptr<Rocks>& r) { return r->pos.first == i && r->pos.second == j;}) != rocks.end())
				{
					std::cout << "[";
				}
				else if (std::find_if(rocks.begin(), rocks.end(), [&i, &j](std::unique_ptr<Rocks>& r) { return r->pos2.first == i && r->pos2.second == j;}) != rocks.end())
				{
					std::cout << "]";
				}
				else if (pos.first == i && pos.second == j)
				{
					std::cout << "@";
				}
				else
					std::cout << ".";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		*/

		if (!walls.contains(newPos))
		{
			if (intersectsVector(rocks, newPos) != nullptr)
			{
				std::vector<std::unique_ptr<Rocks>> cpyVector;

				for (auto& r : rocks)
				{
					cpyVector.push_back(std::unique_ptr<Rocks>(new Rocks(*r)));
				}

				auto it = intersectsVector(cpyVector, newPos);

				if (moveRocks2(it, cpyVector, walls, dirHelper, move))
				{
					pos = newPos;
					rocks.clear();

					for (auto& r : cpyVector)
					{
						rocks.push_back(std::unique_ptr<Rocks>(new Rocks(*r.get())));
					}
				}
			}
			else
			{
				pos = newPos;
			}
		}
		
	}

	for (auto& t : rocks)
	{
		res += t->pos.first * 100 + t->pos.second;
	}


	return std::to_string(res);
}

