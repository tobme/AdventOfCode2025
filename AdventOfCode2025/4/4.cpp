#include "4.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"

Day4::Day4(std::shared_ptr<IInput>& _input) : input(_input)
{}

namespace {
	bool pick_up(const std::vector<std::vector<char>>& matrix, int i, int j)
	{
		int rolls = 0;

		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				int posX = j + x;
				int posY = i + y;

				if ((posX != j || posY != i) && posX >= 0 && posY >= 0 && posX < matrix.front().size() && posY < matrix.size())
				{

					if (matrix.at(posY).at(posX) == '@')
					{
						rolls++;
						if (rolls == 4)
							return false;
					}
				}
			}
		}

		return true;
	}
}

std::string Day4::runPart1()
{
	auto matrix = ToMatrix<char>(input);

	int res = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			char currPos = matrix.at(i).at(j);
			if (currPos == '@')
			{
				res += pick_up(matrix, i, j);
			}
		}
	}
	return std::to_string(res);
}

std::string Day4::runPart2()
{
	auto matrix = ToMatrix<char>(input);

	int res = 0;
	int replaced = 1;
	while (replaced != 0)
	{
		replaced = 0;

		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix.at(i).size(); j++)
			{
				char currPos = matrix.at(i).at(j);
				if (currPos == '@')
				{
					int lRes = pick_up(matrix, i, j);

					if (lRes)
					{
						res++;
						matrix[i][j] = '.';
						replaced++;
					}
				}
			}
		}
	}
	return std::to_string(res);
}

