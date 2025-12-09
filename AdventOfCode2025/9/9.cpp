#include "9.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"
#include <unordered_map>
#include<set>
#include<unordered_set>
#include "../Helpers/PairHash.h"
#include <queue>

Day9::Day9(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day9::runPart1()
{
	std::string line;

	std::vector<std::pair<int, int>> cords;

	while (std::getline(*input, line))
	{
		auto pos = Util::split(line, ",");

		cords.push_back({ std::stoi(pos[0]), std::stoi(pos[1]) });
	}

	unsigned long long biggestRect = 0;

	for (int i = 0; i < cords.size(); i++)
	{
		for (int j = i + 1; j < cords.size(); j++)
		{
			unsigned long long tmp = static_cast<unsigned long long>(std::abs(cords.at(i).first - cords.at(j).first) + 1) * static_cast<unsigned long long>(std::abs(cords.at(i).second - cords.at(j).second) + 1);
			if (tmp > biggestRect)
				biggestRect = tmp;
		}
	}

	return std::to_string(biggestRect);
}

namespace
{
	bool isPointInPolygon(std::unordered_map<int, std::set<int, std::less<int>>>& yGreenTox,
		std::unordered_map<int, std::set<int, std::less<int>>>& xGreenToy,
		int x,
		int y)
	{
		auto upperBoundx = yGreenTox[y].upper_bound(x);

		bool isInxBounds = false;
		bool isInyBounds = false;

		if (upperBoundx != yGreenTox[y].end() && upperBoundx != yGreenTox[y].begin())
		{
			auto prev = std::prev(upperBoundx);

			if (*prev <= x && x <= *upperBoundx)
			{
				isInxBounds = true;
			}
		}

		auto upperBoundy = xGreenToy[x].upper_bound(y);

		if (upperBoundy != xGreenToy[x].end() && upperBoundy != xGreenToy[x].begin())
		{
			auto prev = std::prev(upperBoundy);

			if (*prev <= y && y <= *upperBoundy)
			{
				isInyBounds = true;
			}
		}

		return isInxBounds && isInyBounds;
	}

}

std::string Day9::runPart2()
{
	std::unordered_map<int, std::set<int, std::less<int>>> xToy;
	std::unordered_map<int, std::set<int, std::less<int>>> yTox;

	std::string line;

	std::vector<std::pair<int, int>> cords;

	while (std::getline(*input, line))
	{
		auto pos = Util::split(line, ",");

		int x = std::stoi(pos[0]);
		int y = std::stoi(pos[1]);

		xToy[x].insert(y);
		yTox[y].insert(x);
		cords.push_back({ x, y});
	}

	std::unordered_set<std::pair<int, int>, pair_hash> greenTiles;

	std::unordered_map<int, std::set<int, std::less<int>>> xGreenToy;
	std::unordered_map<int, std::set<int, std::less<int>>> yGreenTox;

	auto it = xToy.begin();
	std::pair<int, int> pos{ it->first, *it->second.begin()};
	std::queue<std::pair<int, int>> queue;
	queue.push(pos);

	while (!queue.empty())
	{
		auto currPos = queue.front();
		queue.pop();

		greenTiles.insert(currPos);
		xGreenToy[currPos.first].insert(currPos.second);
		yGreenTox[currPos.second].insert(currPos.first);

		// Find next below red tile y ->
		auto itY = xToy[currPos.first].find(currPos.second);
		
		if (itY != xToy[currPos.first].end())
		{
			auto nextItY = std::next(itY);
			if (nextItY != xToy[currPos.first].end())
			{
				if (greenTiles.find({ currPos.first, *nextItY }) == greenTiles.end())
				{
					int tmpYPos = currPos.second;

					while (tmpYPos != *nextItY)
					{
						xGreenToy[currPos.first].insert(tmpYPos);
						yGreenTox[tmpYPos].insert(currPos.first);
						greenTiles.insert({ currPos.first, tmpYPos++ });
						
					}

					queue.push({ currPos.first, tmpYPos });
				}
			}
		}

		// Find next above red tile y
		if (itY != xToy[currPos.first].begin())
		{
			auto prevItY = std::prev(itY);

			if (greenTiles.find({currPos.first, *prevItY}) == greenTiles.end())
			{
				auto tmpYPos = currPos.second;

				while (tmpYPos != *prevItY)
				{
					xGreenToy[currPos.first].insert(tmpYPos);
					yGreenTox[tmpYPos].insert(currPos.first);
					greenTiles.insert({ currPos.first, tmpYPos-- });
				}

				queue.push({ currPos.first, tmpYPos });
			}
		}

		// Find next right red tile x ->
		auto itX = yTox[currPos.second].find(currPos.first);
		
		if (itX != yTox[currPos.second].end())
		{
			auto nextX = std::next(itX);
			if (nextX != yTox[currPos.second].end())
			{
				if (greenTiles.find({ *nextX, currPos.second  }) == greenTiles.end())
				{
					int tmpXPos = currPos.first;

					while (tmpXPos != *nextX)
					{
						xGreenToy[tmpXPos].insert(currPos.second);
						yGreenTox[currPos.second].insert(tmpXPos);
						greenTiles.insert({ tmpXPos++, currPos.second});
					}

					queue.push({ tmpXPos, currPos.second  });
				}
			}
		}

		if (itX != yTox[currPos.second].begin())
		{
			auto prevX = std::prev(itX);
			if (greenTiles.find({*prevX, currPos.second}) == greenTiles.end())
			{
				auto tmpXPos = currPos.first;

				while (tmpXPos != *prevX)
				{
					xGreenToy[tmpXPos].insert(currPos.second);
					yGreenTox[currPos.second].insert(tmpXPos);
					greenTiles.insert({ tmpXPos--, currPos.second });
				}

				queue.push({ tmpXPos, currPos.second });
			}
		}
	}

	unsigned long long biggestRect = 0;

	for (int i = 0; i < cords.size(); i++)
	{
		for (int j = i + 1; j < cords.size(); j++)
		{
			unsigned long long tmp = static_cast<unsigned long long>(std::abs(cords.at(i).first - cords.at(j).first) + 1) * static_cast<unsigned long long>(std::abs(cords.at(i).second - cords.at(j).second) + 1);


			if (tmp > biggestRect)
			{
				int startX = cords.at(i).first < cords.at(j).first ? cords.at(i).first : cords.at(j).first;
				int startY = cords.at(i).second < cords.at(j).second ? cords.at(i).second : cords.at(j).second;

				int endX = cords.at(i).first > cords.at(j).first ? cords.at(i).first : cords.at(j).first;
				int endY = cords.at(i).second > cords.at(j).second ? cords.at(i).second : cords.at(j).second;

				std::pair<int,int> bLeftCorner { startX, endY };
				std::pair<int, int> tLeftCorner { startX, startY };
				std::pair<int, int> tRightCorner{ endX, startY };
				std::pair<int, int> bRightCorner{ endX, endY };



				bool xRightTop = true;
				bool xRightBop = true;
				bool yDownLeft = true;
				bool yDownRight = true;

				for (int i = startX; i < endX; i++)
				{
					if (yGreenTox[startY].contains(i))
						continue;

					xRightTop = isPointInPolygon(yGreenTox, xGreenToy, i, startY);
					if (!xRightTop)
						break;

					auto it = yGreenTox[startY].upper_bound(i);
					if (it != yGreenTox[startY].end())
						i = std::min(*it, endX);
					
				}

				if (!xRightTop)
					continue;


				for (int i = startX; i < endX; i++)
				{
					if (yGreenTox[endY].contains(i))
						continue;

					xRightBop = isPointInPolygon(yGreenTox, xGreenToy, i, endY);
					if (!xRightBop)
						break;

					auto it = yGreenTox[endY].upper_bound(i);
					if (it != yGreenTox[endY].end())
						i = std::min(*it, endX);

				}

				if (!xRightBop)
					continue;

				for (int i = startY; i < endY; i++)
				{
					if (xGreenToy[startX].contains(i))
						continue;

					yDownLeft = isPointInPolygon(yGreenTox, xGreenToy, startX, i);
					if (!yDownLeft)
						break;

					auto it = xGreenToy[startX].upper_bound(i);
					if (it != xGreenToy[startX].end())
						i = std::min(*it, endY);

				}

				if (!yDownLeft)
					continue;

				for (int i = startY; i < endY; i++)
				{
					if (xGreenToy[startX].contains(i))
						continue;

					yDownRight = isPointInPolygon(yGreenTox, xGreenToy, startX, i);
					if (!yDownRight)
						break;

					auto it = xGreenToy[startX].upper_bound(i);
					if (it != xGreenToy[startX].end())
						i = std::min(*it, endY);

				}

				if (!yDownRight)
					continue;


				biggestRect = tmp;
			}
		}
	}

	return std::to_string(biggestRect);
}

