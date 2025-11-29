#pragma once

#include "../IChallenge.h"
#include "../IInput.h"
#include <string>
#include <memory>

class Day11 : public IChallenge
{
public:
	Day11(std::shared_ptr<IInput>& _input);
	std::string runPart1() override;
	std::string runPart2() override;
private:
	std::shared_ptr<IInput> input;
};