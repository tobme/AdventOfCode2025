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

	auto input = fetchData(day, DataInputEnvironment::TEST_DATA);
	auto input2 = fetchData(day, DataInputEnvironment::REAL_DATA);

	auto challengeSelectorTestData = std::make_unique<ChallengeSelector>(day, input);
	auto challengeSelectorRealData = std::make_unique<ChallengeSelector>(day, input2);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	std::string answerTestDataPart1 = challengeSelectorTestData->runChallengePart1();
	std::string answerRealDataPart1 = challengeSelectorRealData->runChallengePart1();

	std::string answerTestDataPart2 = challengeSelectorTestData->runChallengePart2();
	std::string answerRealDataPart2 = challengeSelectorRealData->runChallengePart2();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Answer Test Data Part 1: " << answerTestDataPart1 << std::endl;
	std::cout << "Answer Real Data Part 1: " << answerRealDataPart1 << std::endl;

	std::cout << std::endl;

	std::cout << "Answer Test Data Part 2: " << answerTestDataPart2 << std::endl;
	std::cout << "Answer Real Data Part 2: " << answerRealDataPart2 << std::endl;

	std::cout << "Took Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " [ms]" << std::endl;

	return 0;
}