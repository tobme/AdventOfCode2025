#include "24.h"

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "../Helpers/Utilities.h"


Day24::Day24(std::shared_ptr<IInput>& _input) : input(_input)
{}

class Gate
{
public:
	std::string in1;
	std::string type;
	std::string in2;

	std::string output;
};

std::unordered_map<std::string, int> inputs;
std::unordered_map<std::string, Gate*> gates;

void setGateValue(Gate* g)
{
	if (inputs[g->output] != -1)
		return;

	if (inputs[g->in1] == -1)
		setGateValue(gates[g->in1]);

	if (inputs[g->in2] == -1)
		setGateValue(gates[g->in2]);

	int in1 = inputs[g->in1];
	int in2 = inputs[g->in2];
	int res;

	if (g->type == "AND")
		res = in1 & in2;
	else if (g->type == "OR")
		res = in1 | in2;
	else
		res = in1 ^ in2;

	inputs[g->output] = res;

}

void resetInputs()
{
	for (auto& i : inputs)
	{
		if (i.first.front() != 'x' && i.first.front() != 'y')
			i.second = -1;
	}
}

std::string Day24::runPart1()
{
	

	std::string s;

	std::getline(*input, s);

	while (s != "")
	{
		auto ss = Util::split(s, ": ");

		inputs[ss[0]] = std::stoi(ss[1]);

		std::getline(*input, s);
	}

	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, " ");
		auto g = new Gate();
		g->in1 = ss[0];
		g->type = ss[1];
		g->in2 = ss[2];
		g->output = ss[4];

		inputs[ss[4]] = -1;

		gates[ss[4]] = g;
	}

	for (auto& g : gates)
	{
		setGateValue(g.second);
	}

	std::vector<std::pair<std::string, int>> res{};

	for (auto& i : inputs)
	{
		if (i.first.front() == 'z')
			res.push_back(i);
	}

	std::sort(res.begin(), res.end(), [](auto& r, auto& r2){return r.first < r2.first; });

	unsigned long long ret = 0;

	for (int i = 0; i < res.size(); i++)
	{
		if (res.at(i).second == 1)
			ret += std::pow(2, i);
	}

	return std::to_string(ret);
}

std::string print(const std::string& name, int level)
{
	std::string res = "";

	for (int i = 0; i < level; i++)
		res += "";
	res += name + "\n";
	
	for (int i = 0; i < level; i++)
		res += "  ";

	auto& g = gates[name];

	if (g->in1.front() == 'x' || g->in1.front() == 'y')
	{
		res += gates[name]->in1 + "\n";
	}
	else
	{
		res += print(gates[name]->in1, level + 1) + "\n";
	}

	for (int i = 0; i < level; i++)
		res += "  ";

	res += g->type + "\n";

	for (int i = 0; i < level; i++)
		res += "  ";

	if (g->in2.front() == 'x' || g->in2.front() == 'y')
	{
		res += gates[name]->in2 + "\n";
	}
	else
	{
		res += print(gates[name]->in2, level + 1) + "\n";
	}

	return res;
}

std::string createLabel(const std::string& id, int number)
{
	std::string tmp = number < 10 ? "0" : "";
	return id + tmp + std::to_string(number);
}

bool verify_xor(const std::string& id, int number)
{
	std::cout << "Verify xor " << id << " " << number << std::endl;
	auto& g = gates[id];

	if (g->type != "XOR")
		return false;
	std::string label = createLabel("x", number);
	std::string label2 = createLabel("y", number);
	return (g->in1 == label || g->in1 == label2) && (g->in2 == label || g->in2 == label2);
}


bool verify_last_xy_carry(const std::string& id, int number)
{
	std::cout << "Verify last xy carry " << id << " " << number << std::endl;
	auto& g = gates[id];
	if (g->type != "AND")
		return false;

	auto label = createLabel("x", number);
	auto label2 = createLabel("y", number);

	return (g->in1 == label || g->in1 == label2) && (g->in2 == label || g->in2 == label2);
}

bool verify_carry_over(const std::string& id, int number);

bool verify_carry(const std::string& id, int number)
{
	std::cout << "Verify carry " << id << " " << number << std::endl;
	auto& g = gates[id];
	if (number == 1)
	{
		if (g->type != "AND")
			return false;
		return (g->in1 == "x00" || g->in1 == "y00") && (g->in2 == "x00" || g->in2 == "y00");
	}
	if (g->type != "OR")
		return false;

	return (verify_last_xy_carry(g->in1, number - 1) && verify_carry_over(g->in2, number - 1)) || (verify_last_xy_carry(g->in2, number - 1) && verify_carry_over(g->in1, number - 1));
}

bool verify_carry_over(const std::string& id, int number)
{
	std::cout << "Verify carry over " << id << " " << number << std::endl;
	auto& g = gates[id];
	if (g->type != "AND")
		return false;
	return (verify_xor(g->in1, number) && verify_carry(g->in2, number)) || (verify_xor(g->in2, number) && verify_carry(g->in1, number));
}

bool verifyZ(const std::string& zId, int number)
{
	std::cout << "Verify Z " << zId << " " << number << std::endl;

	auto& g = gates[zId];
	if (g->type != "XOR") 
		return false;

	if (number == 0)
	{
		return (g->in1 == "x00" || g->in1 == "y00") && (g->in2 == "x00" || g->in2 == "y00");
	}

	return verify_xor(g->in1, number) && verify_carry(g->in2, number) || verify_xor(g->in2, number) && verify_carry(g->in1, number);
}

bool verify_helper(int id)
{
	return verifyZ(createLabel("z", id), id);
}

std::string Day24::runPart2()
{

	std::string s;

	std::getline(*input, s);

	while (s != "")
	{
		auto ss = Util::split(s, ": ");

		inputs[ss[0]] = std::stoi(ss[1]);

		std::getline(*input, s);
	}

	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, " ");
		auto g = new Gate();
		g->in1 = ss[0];
		g->type = ss[1];
		g->in2 = ss[2];
		g->output = ss[4];

		inputs[ss[4]] = -1;

		gates[ss[4]] = g;
	}

	for (auto& g : gates)
	{
		setGateValue(g.second);
	}
	int i = 0;

	while (verify_helper(i))
	{
		std::cout << std::endl;
		i++;
	}

	std::cout << "VERIFY fail: " << i << std::endl;

	std::vector<std::string> swaps = { "z06", "vwr", "z11", "tqm", "z16", "kfs", "hcm", "gfv" };
	std::sort(swaps.begin(), swaps.end());
	std::string res = "";
	for (auto& s : swaps)
	{
		res += s + ",";
	}
	res.pop_back();
	return res;
}

