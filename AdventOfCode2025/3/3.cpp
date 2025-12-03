#include "3.h"

#include <iostream>
#include <algorithm>
#include <cmath>

Day3::Day3(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day3::runPart1()
{
	std::string line;

	int res = 0;

	while (std::getline(*input, line))
	{
		int largest = 0;
		int secondLargest = 0;
		for (int i = 0; i < line.size(); i++)
		{
			int numb = line.at(i) - '0';

			if (numb > largest && i != line.size() - 1)
			{
				largest = numb;
				secondLargest = 0;
			}
			else if (numb > secondLargest)
			{
				secondLargest = numb;
			}
		}

		res += largest * 10 + secondLargest;
	}

	return std::to_string(res);
}

namespace {
	// Find largest number within the string from index -> s.size() - size
	// Returns index of largest number
	int findLargest(const std::string& s, int index, int size)
	{
		int largest = -1;
		int largestIndex = -1;
		for (int i = index; i < s.size() - size; i++)
		{
			int numb = s.at(i) - '0';
			if (numb > largest)
			{
				largest = numb;
				largestIndex = i;
			}
		}

		return largestIndex;
	}

	unsigned long long ipow(unsigned long long base, unsigned long long exp) {
		unsigned long long result = 1;
		while (exp > 0) {
			if (exp & 1)
				result *= base;
			base *= base;
			exp >>= 1;
		}
		return result;
	}
}

std::string Day3::runPart2()
{
	{
		std::string line;

		unsigned long long res = 0;

		while (std::getline(*input, line))
		{
			int index = 0;

			for (int i = 11; i >= 0; i--) // 0-11 -> 12 loops
			{
				index = findLargest(line, index, i);
				
				res += (line.at(index) - '0') * ipow(10, i);
				index++;
			}
		}

		return std::to_string(res);
	}
}

