#include "8.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"
#include <map>
#include <unordered_set>

Day8::Day8(std::shared_ptr<IInput>& _input) : input(_input)
{}

namespace {

	std::unordered_set<int> seen;

	class Circuit
	{
	public:
		Circuit(int _x, int _y, int _z, int _id) : x{ _x }, y{ _y }, z{ _z }, id{ _id }, connections {}
		{

		}

		int x;
		int y;
		int z;
		int id;

		std::vector<std::shared_ptr<Circuit>> connections;

		void addConnection(const std::shared_ptr<Circuit>& con)
		{
			connections.push_back(con);
		}

		int calcConnnections()
		{
			if (seen.find(id) != seen.end())
				return 0;

			seen.insert(id);

			int res = 1;

			for (auto& p : connections)
			{
				res += p->calcConnnections();
			}

			return res;
		}
	};

	class Link
	{
	public:
		std::shared_ptr<Circuit> a;
		std::shared_ptr<Circuit> b;
		unsigned long long dist;

	};
}

std::string Day8::runPart1()
{
	std::string line;

	std::vector<std::shared_ptr<Circuit>> circuits;

	int id = 0;

	while (std::getline(*input, line))
	{
		auto cords = Util::split(line, ",");

		circuits.push_back(std::make_shared<Circuit>(std::stoi(cords[0]), std::stoi(cords[1]), std::stoi(cords[2]), id++));
	}

	std::vector<std::unique_ptr<Link>> links;

	for (int i = 0; i < circuits.size(); i++)
	{
		for (int j = i + 1; j < circuits.size(); j++)
		{
			unsigned long long xDiff = std::pow(circuits.at(i)->x - circuits.at(j)->x, 2);
			unsigned long long yDiff = std::pow(circuits.at(i)->y - circuits.at(j)->y, 2);
			unsigned long long zDiff = std::pow(circuits.at(i)->z - circuits.at(j)->z, 2);

			unsigned long long resDiff = std::sqrt(xDiff + yDiff + zDiff);

			links.push_back(std::make_unique<Link>(circuits.at(i), circuits.at(j), resDiff));
		}
	}

	sort(links.begin(), links.end(), [](auto& p, auto& p2)
		{
			return p->dist < p2->dist;
		});

	int connections = circuits.size() == 20 ? 10: 1000;

	for (int i = 0; i < std::min<int>(connections, links.size()); i++)
	{
		links.at(i)->a->addConnection(links.at(i)->b);
		links.at(i)->b->addConnection(links.at(i)->a);
	}

	std::vector<unsigned long long> results;

	for (auto& p : circuits)
	{
		if (seen.find(p->id) == seen.end())
		{
			results.push_back(p->calcConnnections());
		}
	}

	sort(results.begin(), results.end(), std::greater<int>());

	unsigned long long res = results[0] * results[1] * results[2];

	return std::to_string(res);
}

std::string Day8::runPart2()
{
	std::string line;

	std::vector<std::shared_ptr<Circuit>> circuits;

	int id = 0;

	while (std::getline(*input, line))
	{
		auto cords = Util::split(line, ",");

		circuits.push_back(std::make_shared<Circuit>(std::stoi(cords[0]), std::stoi(cords[1]), std::stoi(cords[2]), id++));
	}

	std::vector<std::unique_ptr<Link>> links;

	for (int i = 0; i < circuits.size(); i++)
	{
		for (int j = i + 1; j < circuits.size(); j++)
		{
			unsigned long long xDiff = std::pow(circuits.at(i)->x - circuits.at(j)->x, 2);
			unsigned long long yDiff = std::pow(circuits.at(i)->y - circuits.at(j)->y, 2);
			unsigned long long zDiff = std::pow(circuits.at(i)->z - circuits.at(j)->z, 2);

			unsigned long long resDiff = std::sqrt(xDiff + yDiff + zDiff);

			links.push_back(std::make_unique<Link>(circuits.at(i), circuits.at(j), resDiff));
		}
	}

	sort(links.begin(), links.end(), [](auto& p, auto& p2)
		{
			return p->dist < p2->dist;
		});

	std::unordered_set<int> seen2;

	int index = 0;

	while (seen2.size() != circuits.size())
	{
		seen2.insert(links.at(index)->a->id);
		seen2.insert(links.at(index)->b->id);
		index++;
	}

	index--;
	unsigned long long res = static_cast<unsigned long long>(links.at(index)->a->x) * static_cast<unsigned long long>(links.at(index)->b->x);

	return std::to_string(res);
}

