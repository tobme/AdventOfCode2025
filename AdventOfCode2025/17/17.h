#pragma once

#include "../IChallenge.h"
#include "../IInput.h"
#include <string>
#include <memory>

class Day17 : public IChallenge
{
public:
	Day17(std::shared_ptr<IInput>& _input);
	std::string runPart1() override;
	std::string runPart2() override;
private:
	std::shared_ptr<IInput> input;

	unsigned long long A = 0;
	unsigned long long B = 0;
	unsigned long long C = 0;
	int instructionPointer = 0;
	std::vector<std::string> instructions;
	std::string res;

	void adv(int opValue);
	void bxl(int opValue);
	void bst(int opValue);
	void jnz(int opValue);
	void bxc(int opValue);
	void out(int opValue);
	void bdv(int opValue);
	void cdv(int opValue);
	unsigned long long getOperandValue(int opCode);
	void performInstruction(int index);
};