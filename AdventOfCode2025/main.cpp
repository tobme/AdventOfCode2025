#pragma once

#include "ChallengeSelector.h"

#include "InputSelector.h"
#include "DataInput.cpp"

#include <iostream>
#include<ctime>
#include <chrono>

using namespace std::chrono;

int main()
{
	auto now = zoned_time{ current_zone(), system_clock::now() }.get_local_time();

	// Get a local time_point with days precision
	auto ld = floor<days>(now);

	// Convert local days-precision time_point to a local {y, m, d} calendar
	year_month_day ymd{ ld };

	// Split time since local midnight into {h, m, s, subseconds}
	hh_mm_ss hms{ now - ld };

	int intDay = unsigned{ ymd.day() };

	// Get day
	std::string day;

	std::cout << "Day: (c current day):";
	std::cin >> day;
	std::cout << std::endl;

	if (day == "c")
		day = std::to_string(intDay);

	auto part = InputSelector::GetInputFromList({ "Part1", "Part2"});

	auto dataSelection = InputSelector::GetInputFromList({ "Test Data", "Real Data" });

	DataInputEnvironment env = dataSelection == "Test Data" ? DataInputEnvironment::TEST_DATA : DataInputEnvironment::REAL_DATA;

	auto input = fetchData(day, env);

	auto challengeSelector = std::make_unique<ChallengeSelector>(day, input);

	std::string answer = "";

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	if (part == "Part1")
	{
		answer = challengeSelector->runChallengePart1();
	}
	else
	{
		answer = challengeSelector->runChallengePart2();
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Answer: " << answer << std::endl;
	std::cout << "Took Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " [ms]" << std::endl;

	return 0;
}