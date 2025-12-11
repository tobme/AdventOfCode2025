#include "11.h"

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "../Helpers/Utilities.h"


Day11::Day11(std::shared_ptr<IInput>& _input) : input(_input)
{}

namespace
{

	unsigned long long pathFound(const std::string& in, std::unordered_map<std::string, std::vector<std::string>>& paths, std::unordered_map<std::string, unsigned long long>& memory)
	{
		if (in == "out")
			return 1;

		if (memory.contains(in))
			return memory[in];

		unsigned long long res = 0;

		for (auto& s : paths[in])
		{
			res += pathFound(s, paths, memory);
		}

		memory[in] = res;

		return res;
	}

	unsigned long long pathFound2(const std::string& in, std::unordered_map<std::string, std::vector<std::string>>& paths, std::unordered_map<std::string, unsigned long long>& memory, bool visitedDac, bool visitedFft)
	{
		if (in == "dac")
			visitedDac = true;
		if (in == "fft")
			visitedFft = true;

		if (in == "out")
			return visitedDac && visitedFft;

		std::string id = in + "-" + std::to_string(visitedDac) + "-" + std::to_string(visitedFft);

		if (memory.contains(id))
			return memory[id];

		unsigned long long res = 0;

		for (auto& s : paths[in])
		{
			res += pathFound2(s, paths, memory, visitedDac, visitedFft);
		}

		memory[id] = res;

		return res;
	}
}

std::string Day11::runPart1()
{
	std::string line;

	std::unordered_map<std::string, std::vector<std::string>> paths;

	while (std::getline(*input, line))
	{
		auto inOut = Util::split(line, ":");

		auto outputs = Util::split(inOut[1], " ");

		outputs.erase(outputs.begin(), outputs.begin() + 1);

		paths[inOut[0]] = outputs;
	}

	std::unordered_map<std::string, unsigned long long> memory;

	unsigned long long res = pathFound("you", paths, memory);

	return std::to_string(res);
}

std::string Day11::runPart2()
{
	std::string line;

	std::unordered_map<std::string, std::vector<std::string>> paths;

	while (std::getline(*input, line))
	{
		auto inOut = Util::split(line, ":");

		auto outputs = Util::split(inOut[1], " ");

		outputs.erase(outputs.begin(), outputs.begin() + 1);

		paths[inOut[0]] = outputs;
	}

	std::unordered_map<std::string, unsigned long long> memory;

	unsigned long long res = pathFound2("svr", paths, memory, false, false);

	return std::to_string(res);
}

