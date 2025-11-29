#include "ChallengeSelector.h"

#include <iostream>
#include <chrono>
#include <memory>

#include "1/1.h"
#include "2/2.h"
#include "3/3.h"
#include "4/4.h"
#include "5/5.h"
#include "6/6.h"
#include "7/7.h"
#include "8/8.h"
#include "9/9.h"
#include "10/10.h"
#include "11/11.h"
#include "12/12.h"
#include "13/13.h"
#include "14/14.h"
#include "15/15.h"
#include "16/16.h"
#include "17/17.h"
#include "18/18.h"
#include "19/19.h"
#include "20/20.h"
#include "21/21.h"
#include "22/22.h"
#include "23/23.h"
#include "24/24.h"
#include "25/25.h"

std::unique_ptr<IChallenge> getChallengeFunction(const std::string& day, std::shared_ptr<IInput>& input)
{
	if (day == "1")
	{
		return std::make_unique<Day1>(input);
	}
	else if (day == "2")
	{
		return std::make_unique<Day2>(input);
	}
	else if (day == "3")
	{
		return std::make_unique<Day3>(input);
	}
	else if (day == "4")
	{
		return std::make_unique<Day4>(input);
	}
	else if (day == "5")
	{
		return std::make_unique<Day5>(input);
	}
	else if (day == "6")
	{
		return std::make_unique<Day6>(input);
	}
	else if (day == "7")
	{
		return std::make_unique<Day7>(input);
	}
	else if (day == "8")
	{
		return std::make_unique<Day8>(input);
	}
	else if (day == "9")
	{
		return std::make_unique<Day9>(input);
	}
	else if (day == "10")
	{
		return std::make_unique<Day10>(input);
	}
	else if (day == "11")
	{
		return std::make_unique<Day11>(input);
	}
	else if (day == "12")
	{
		return std::make_unique<Day12>(input);
	}
	else if (day == "13")
	{
		return std::make_unique<Day13>(input);
	}
	else if (day == "14")
	{
		return std::make_unique<Day14>(input);
	}
	else if (day == "15")
	{
		return std::make_unique<Day15>(input);
	}
	else if (day == "16")
	{
		return std::make_unique<Day16>(input);
	}
	else if (day == "17")
	{
		return std::make_unique<Day17>(input);
	}
	else if (day == "18")
	{
		return std::make_unique<Day18>(input);
	}
	else if (day == "19")
	{
		return std::make_unique<Day19>(input);
	}
	else if (day == "20")
	{
		return std::make_unique<Day20>(input);
	}
	else if (day == "21")
	{
		return std::make_unique<Day21>(input);
	}
	else if (day == "22")
	{
		return std::make_unique<Day22>(input);
	}
	else if (day == "23")
	{
		return std::make_unique<Day23>(input);
	}
	else if (day == "24")
	{
		return std::make_unique<Day24>(input);
	}
	else if (day == "25")
	{
		return std::make_unique<Day25>(input);
	}

	return nullptr;
}

ChallengeSelector::ChallengeSelector(const std::string& day, std::shared_ptr<IInput>& _input)
{
	challenge = getChallengeFunction(day, _input);
}

std::string ChallengeSelector::runChallengePart1()
{
	return challenge->runPart1();
}

std::string ChallengeSelector::runChallengePart2()
{
	return challenge->runPart2();
}

