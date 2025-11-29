#include "1.h"

#include <iostream>
#include <algorithm>
#include<string>
#include<sstream>
#include<unordered_map>

Day1::Day1(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day1::runPart1()
{
	std::string line;

	std::vector<int> left;

	std::vector<int> right;

	std::stringstream ss;

	ss << input->rdbuf();

	while (ss >> line)
	{
		left.push_back(std::stoi(line));

		ss >> line;
		right.push_back(std::stoi(line));
	}

	std::sort(left.begin(), left.end(), std::less<int>());
	std::sort(right.begin(), right.end(), std::less<int>());

	int res = 0;
	for (int i = 0; i < left.size(); i++)
	{
		res += std::abs(left.at(i) - right.at(i));
	}

	return std::to_string(res);
}

std::string Day1::runPart2()
{
	std::string line;

	std::stringstream ss;

	ss << input->rdbuf();

	std::vector<int> left;

	std::unordered_map<int, int> right;

	while (ss >> line)
	{
		left.push_back(std::stoi(line));

		ss >> line;
		right[std::stoi(line)]++;
	}

	int res = 0;
	for (int i : left)
	{
		if (right.contains(i))
		{
			res += i * right[i];
		}
	}

	return std::to_string(res);
}

