#pragma once

#include <string>

class IChallenge
{
public:
	IChallenge() = default;
	 virtual ~IChallenge() = default;

	virtual std::string runPart1() = 0;
	virtual std::string runPart2() = 0;
};