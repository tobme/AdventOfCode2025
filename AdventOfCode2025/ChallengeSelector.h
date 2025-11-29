#pragma once

#include "IInput.h"
#include "IChallenge.h"

#include <memory>

class ChallengeSelector
{
public:
	ChallengeSelector(const std::string& day, std::shared_ptr<IInput>& _input);

	std::string runChallengePart1();
	std::string runChallengePart2();
private:
	std::unique_ptr<IChallenge> challenge;
};