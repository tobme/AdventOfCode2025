#pragma once

#include "../IChallenge.h"
#include "../IInput.h"
#include <string>
#include <memory>

class Day23 : public IChallenge
{
public:
	Day23(std::shared_ptr<IInput>& _input);
	std::string runPart1() override;
	std::string runPart2() override;
private:
	std::shared_ptr<IInput> input;
};