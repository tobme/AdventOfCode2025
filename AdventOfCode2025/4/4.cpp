#include "4.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"

Day4::Day4(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day4::runPart1()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	std::string word = "XMAS";
	std::string wordRev = "SAMX";

	int res = 0;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			int rightInc = column + 3;
			int downInc = row + 3;
			int leftInc = column - 3;

			bool fail = false;

			if (rightInc < matrix.at(row).size())
			{// left
				for (int i = 0; i < 4; i++)
				{
					if (matrix[row][column + i] != word.at(i))
					{
						fail = true;
						break;
					}
				}

				if (!fail)
				{
					res++;
				}

				fail = false;

				for (int i = 0; i < 4; i++)
				{
					if (matrix[row][column + i] != wordRev.at(i))
					{
						fail = true;
						break;
					}
				}

				if (!fail)
				{
					res++;
				}
			}

			fail = false;

			if (downInc < matrix.size())
			{// down
				for (int i = 0; i < 4; i++)
				{
					if (matrix[row+i][column] != word.at(i))
					{
						fail = true;
						break;
					}
				}

				if (!fail)
				{
					res++;
				}

				fail = false;

				for (int i = 0; i < 4; i++)
				{
					if (matrix[row+i][column] != wordRev.at(i))
					{
						fail = true;
						break;
					}
				}

				if (!fail)
				{
					res++;
				}
			}

			fail = false;

			if (leftInc >= 0 && downInc < matrix.size())
			{// downleft
				for (int i = 0; i < 4; i++)
				{
					if (matrix[row + i][column-i] != word.at(i))
					{
						fail = true;
						break;
					}
				}

				if (!fail)
				{
					res++;
				}

				fail = false;

				for (int i = 0; i < 4; i++)
				{
					if (matrix[row + i][column-i] != wordRev.at(i))
					{
						fail = true;
						break;
					}
				}

				if (!fail)
				{
					res++;
				}
			}

			fail = false;

			if (rightInc < matrix.at(row).size() && downInc < matrix.size())
			{//downright
				for (int i = 0; i < 4; i++)
				{
					if (matrix[row + i][column + i] != word.at(i))
					{
						fail = true;
						break;
					}
				}

				if (!fail)
				{
					res++;
				}

				fail = false;

				for (int i = 0; i < 4; i++)
				{
					if (matrix[row + i][column + i] != wordRev.at(i))
					{
						fail = true;
						break;
					}
				}

				if (!fail)
				{
					res++;
				}
			}
		}
	}

	return std::to_string(res);
}

std::string Day4::runPart2()
{
	auto matrix = ToMatrix<char>(input, Util::transformConverter<char>, "?");

	int res = 0;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			int rightInc = row + 2;
			int downInc = column + 2;

			if (rightInc < matrix.at(row).size() && downInc < matrix.size())
			{
				bool fMas = matrix[row][column] == 'M' && matrix[row + 1][column + 1] == 'A' && matrix[row + 2][column + 2] == 'S';
				bool fMasRev = (matrix[row][column] == 'S' && matrix[row + 1][column + 1] == 'A' && matrix[row + 2][column + 2] == 'M');
				bool sMas = matrix[row + 2][column] == 'M' && matrix[row + 1][column + 1] == 'A' && matrix[row][column + 2] == 'S';
				bool sMasRev = matrix[row + 2][column] == 'S' && matrix[row + 1][column + 1] == 'A' && matrix[row][column + 2] == 'M';
				if ((fMas || fMasRev) && (sMas || sMasRev))
				{
					res++;
				}
			}
		}
	}

	return std::to_string(res);
}

