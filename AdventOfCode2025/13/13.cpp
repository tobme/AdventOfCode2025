#include "13.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"

Day13::Day13(std::shared_ptr<IInput>& _input) : input(_input)
{}
namespace {
	std::pair<double, double> getcooridnates(std::string& s)
	{
		auto ss = Util::split(s, ":");
		auto sss = Util::split(ss[1], ",");

		return { std::stod(sss[0].substr(3)), std::stod(sss[1].substr(3)) };
	}

	std::pair<double, double> calcInsertion(const std::pair<double, double>& buttonA, const std::pair<double, double>& buttonB, const std::pair<double, double>& prize)
	{
		double bX = buttonB.second * (buttonA.first / buttonB.first);

		double numberA = buttonA.second - bX;

		double a = (prize.second - ((buttonB.second * prize.first) / buttonB.first)) / numberA;

		double b = (prize.first - (buttonA.first * a)) / buttonB.first;

		return { a,b };
	}

	bool withinRange(double x, double range)
	{
		return std::abs(std::round(x) - x) <= range;
	}
}
std::string Day13::runPart1()
{
	std::string s;
	
	int res = 0;
	while (std::getline(*input, s))
	{
		std::string line2;
		std::string line3;

		std::getline(*input, line2);
		std::getline(*input, line3);

		std::string junk;
		std::getline(*input, junk);

		auto buttonA = getcooridnates(s);
		auto buttonB = getcooridnates(line2);
		auto prize = getcooridnates(line3);

		auto insertion = calcInsertion(buttonA, buttonB, prize);

		if (withinRange(insertion.first, 0.001) && withinRange(insertion.second, 0.001))
		{
			res += insertion.first * 3 + insertion.second;
		}
	}

	return std::to_string(res);
}

std::string Day13::runPart2()
{
	std::string s;

	unsigned long long res = 0;
	while (std::getline(*input, s))
	{
		std::string line2;
		std::string line3;

		std::getline(*input, line2);
		std::getline(*input, line3);

		std::string junk;
		std::getline(*input, junk);

		auto buttonA = getcooridnates(s);
		auto buttonB = getcooridnates(line2);
		auto prize = getcooridnates(line3);

		prize.first += 10000000000000;
		prize.second += 10000000000000;

		auto insertion = calcInsertion(buttonA, buttonB, prize);

		if (withinRange(insertion.first, 0.001) && withinRange(insertion.second, 0.001))
		{
			res += insertion.first * 3 + insertion.second;
		}
	}

	return std::to_string(res);
}

