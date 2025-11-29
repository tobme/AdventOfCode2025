#include "17.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"

Day17::Day17(std::shared_ptr<IInput>& _input) : input(_input)
{}

void Day17::adv(int operand)
{
	unsigned long long opValue = getOperandValue(operand);

	A = static_cast<unsigned long long>((double)A / std::pow(2, opValue));
}

void Day17::bxl(int operand)
{
	B ^= operand;
}

void Day17::bst(int operand)
{
	unsigned long long opValue = getOperandValue(operand);

	B = opValue % 8;
}

void Day17::jnz(int operand)
{
	if (A != 0)
	{
		instructionPointer = operand - 2;
	}
}

void Day17::bxc(int operand)
{
	B ^= C;
}

std::string outValue = "";

void Day17::out(int operand)
{
	unsigned long long opValue = getOperandValue(operand) % 8;

	res.append(std::to_string(opValue) + ",");
	outValue = std::to_string(opValue);
}

void Day17::bdv(int operand)
{
	unsigned long long opValue = getOperandValue(operand);

	B = static_cast<unsigned long long>((double)A / std::pow(2, opValue));
}

void Day17::cdv(int operand)
{
	unsigned long long opValue = getOperandValue(operand);

	C = static_cast<unsigned long long>((double)A / std::pow(2, opValue));
}



unsigned long long Day17::getOperandValue(int operand)
{
	switch (operand)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return operand;
	case 4:
		return A;
	case 5:
		return B;
	case 6:
		return C;
	case 7:
		throw;
	}
}

void Day17::performInstruction(int index)
{
	int opcode = std::stoi(instructions[index]);
	int operand = std::stoi(instructions[index+1]);

	switch (opcode)
	{
	case 0:
		adv(operand);
		break;
	case 1:
		bxl(operand);
		break;
	case 2:
		bst(operand);
		break;
	case 3:
		jnz(operand);
		break;
	case 4:
		bxc(operand);
		break;
	case 5:
		out(operand);
		break;
	case 6:
		bdv(operand);
		break;
	case 7:
		cdv(operand);
		break;
	default:
		throw;
	}
}

std::string Day17::runPart1()
{
	std::string s;

	std::getline(*input, s);
	auto ss = Util::split(s, ": ");
	A = std::stoi(ss[1]);

	std::getline(*input, s);
	ss = Util::split(s, ": ");
	B = std::stoi(ss[1]);

	std::getline(*input, s);
	ss = Util::split(s, ": ");
	C = std::stoi(ss[1]);

	std::getline(*input, s);
	std::getline(*input, s);
	ss = Util::split(s, ": ");
	instructions = Util::split(ss[1], ",");

	while (instructionPointer < instructions.size())
	{
		performInstruction(instructionPointer);
		instructionPointer += 2;
	}
	return res;
}

void printBytes(unsigned long long b)
{
	std::string out = "";

	int i = 16 * 3;

	while (b != 0)
	{
		if (b >= std::pow(2, i))
		{
			b -= std::pow(2, i);
			out += "1";
		}
		else
			out += "0";

		i--;
	}
	std::cout << out << std::endl;
}

unsigned long long find2(unsigned long long answr, int resPtr, const std::vector<std::string>& instructions)
{
	if (resPtr == -1) return answr;

	for (int i = 0; i < 8; i++)
	{
		unsigned long long a = (answr << 3) | i;
		unsigned long long b = a % 8;
		b ^= 2;
		unsigned long long c = a >> b;
		b ^= 7;
		b ^= c;
		unsigned long long print = b % 8;

		if (print == std::stoull(instructions.at(resPtr)))
		{
			unsigned long long tmp = find2(a, resPtr - 1, instructions);
			if (tmp != 0)
				return tmp;
		}
	}

	return 0;
}

std::string Day17::runPart2()
{
	std::string s;

	std::getline(*input, s);
	auto ss = Util::split(s, ": ");
	A = std::stoi(ss[1]);
	A = 117440;

	std::getline(*input, s);
	ss = Util::split(s, ": ");
	B = std::stoi(ss[1]);

	std::getline(*input, s);
	ss = Util::split(s, ": ");
	C = std::stoi(ss[1]);

	std::getline(*input, s);
	std::getline(*input, s);
	ss = Util::split(s, ": ");
	instructions = Util::split(ss[1], ",");

	int resPtr = 0;

	int timesCounter = 0;

	std::vector<unsigned long long> resHelper(16,0);

	int stepInc = 0;

	unsigned long long retRes = 0;
	unsigned long long i = 0;

	auto answ = find2(0, 15, instructions);

	return std::to_string(retRes);
}

