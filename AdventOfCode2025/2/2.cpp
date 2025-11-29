#include "2.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/InputTransformer.h"

namespace {
	enum class Flow : int
	{
		INCREASING = 1,
		DEFAULT = 0,
		DECREASING = -1
	};

	int isSafe(const std::vector<int>& v)
	{
		Flow flow = Flow::DEFAULT;
		int last = v.front();
		for (int column = 1; column < v.size(); column++)
		{
			int newNumber = v.at(column);
			Flow newFlow = last > newNumber ? Flow::DECREASING : Flow::INCREASING;

			if ((std::abs(last - newNumber) > 3 || std::abs(last - newNumber) == 0) || (flow != Flow::DEFAULT && newFlow != flow))
			{
				return 0;
			}

			flow = newFlow;
			last = newNumber;
		}
		return 1;
	}

	int isSafe2(const std::vector<int>& v, int skipIndex)
	{
		Flow flow = Flow::DEFAULT;
		auto last = v.front();
		int column = 1;

		if (skipIndex == 0)
		{
			last = v.at(1);
			column++;
		}

		for (; column < v.size(); column++)
		{
			if (column == skipIndex)
				continue;

			int newNumber = v.at(column);
			Flow newFlow = last > newNumber ? Flow::DECREASING : Flow::INCREASING;

			if ((std::abs(last - newNumber) > 3 || std::abs(last - newNumber) == 0) || (flow != Flow::DEFAULT && newFlow != flow))
			{
				return 0;
			}

			flow = newFlow;
			last = newNumber;
		}
		return 1;
	}
}

Day2::Day2(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day2::runPart1()
{
	auto matrix = ToMatrix<int>(input);

	int res = 0;

	for (int row = 0; row < matrix.size(); row++)
	{
		res += isSafe(matrix.at(row));
	}

	return std::to_string(res);
}

std::string Day2::runPart2()
{
	auto matrix = ToMatrix<int>(input);

	int res = 0;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			auto tmp = isSafe2(matrix.at(row), column);
			if (tmp == 1)
			{
				res++;
				break;
			}
		}
	}

	return std::to_string(res);
}

