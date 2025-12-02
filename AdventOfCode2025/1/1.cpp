#include "1.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

Day1::Day1(std::shared_ptr<IInput>& _input) : input(_input)
{}

std::string Day1::runPart1()
{
	int pos = 50;
	std::vector<std::string> data;
	int res = 0;
	std::string line;
	while (std::getline(*input, line))
	{
		int num = std::stoi(line.substr(1));

		if (line.front() == 'R')
		{
			for (int i = 0; i < num; i++)
			{
				pos++;
				if (pos == 100)
					pos = 0;
			}
		}
		else
		{
			
			for (int i = 0; i < num; i++)
			{
				pos--;
				if (pos == -1)
					pos = 99;
			}
		}

		if (pos == 0)
			res++;

	}

	return std::to_string(res);
}

std::string Day1::runPart2()
{
	int pos = 50;
	std::vector<std::string> data;
	int res = 0;
	std::string line;
	while (std::getline(*input, line))
	{
		int num = std::stoi(line.substr(1));

		if (line.front() == 'R')
		{
			for (int i = 0; i < num; i++)
			{
				pos++;
				if (pos == 100)
				{
					pos = 0;
					res++;
				}
			}
		}
		else
		{

			for (int i = 0; i < num; i++)
			{
				pos--;
				if (pos == -1)
					pos = 99;
				if (pos == 0)
					res++;
			}
		}

	}

	return std::to_string(res);
}

