#include "9.h"

#include <iostream>
#include <algorithm>

Day9::Day9(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day9::runPart1()
{
	std::string s;
	std::getline(*input, s);

	int id = 0;
	bool file = true;
	std::vector<int> output{};

	for (char c : s)
	{
		if (file)
		{
			file = false;
			for (int i = 0; i < c - '0'; i++)
				output.push_back(id);
			id++;
		}
		else
		{
			file = true;
			for (int i = 0; i < c - '0'; i++)
				output.push_back(-1);
		}
	}

	auto first = output.begin();
	auto end = output.rbegin();

	while (true)
	{
		first = std::find_if(first, output.end(), [](int c) { return c == -1;});
		end = std::find_if(end, output.rend(), [](int c) { return c != -1;});

		if (first == end.base())
			break;

		std::swap(*first, *end);
	}

	unsigned long long index = 0;
	unsigned long long res = 0;

	while (output[index] != -1)
	{
		res += index * static_cast<unsigned long long>(output[index]);
		index++;
	}

	return std::to_string(res);
}

static int findLength(std::vector<int>::iterator it, int id, std::vector<int>::iterator end)
{
	int index = 0;

	while (it != end && *it == id)
	{
		it++;
		index++;
	}
	return index;
}

static int findLength(std::vector<int>::reverse_iterator it, int id, std::vector<int>::reverse_iterator end)
{
	int index = 0;

	while (it != end && (*it) == id)
	{
		it++;
		index++;
	}
	return index;
}

std::string Day9::runPart2()
{
	std::string s;
	std::getline(*input, s);

	int id = 0;
	bool file = true;
	std::vector<int> output{};

	for (char c : s)
	{
		if (file)
		{
			file = false;
			for (int i = 0; i < c - '0'; i++)
				output.push_back(id);
			id++;
		}
		else
		{
			file = true;
			for (int i = 0; i < c - '0'; i++)
				output.push_back(-1);
		}
	}

	auto first = output.begin();
	auto end = output.rbegin();

	int lookId = *std::find_if(output.rbegin(), output.rend(), [](int c) { return c != -1;});

	for (int i = lookId; i > 0; i--)
	{
		first = std::find_if(output.begin(), output.end(), [](int c) { return c == -1;});
		end = std::find_if(output.rbegin(), output.rend(), [&i](int c) { return c == i;});

		int endLength = findLength(end, *end, output.rend());

		while (first != end.base() && first < end.base())
		{
			int startLength = findLength(first, -1, output.end());

			if (startLength >= endLength)
			{
				for (int j = 0; j < endLength; j++)
				{
					std::swap(*first, *end);
					first++;
					end++;
				}
				break;
			}
			else
			{
				first += startLength;
				first = std::find_if(first, output.end(), [](int c) { return c == -1;});
			}
		}
	}

	unsigned long long res = 0;

	for (unsigned long long index = 0; index < output.size(); index++)
	{
		if (output[index] != -1)
			res += index * static_cast<unsigned long long>(output[index]);
	}

	return std::to_string(res);
}

