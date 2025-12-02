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

