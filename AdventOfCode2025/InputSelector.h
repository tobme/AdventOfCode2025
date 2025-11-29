#pragma once

#include <string>
#include <vector>

class InputSelector
{
public:
	static std::string GetInputFromList(const std::vector<std::string>& selector);

	static bool GetBoolFromQuestion(const std::string& question);
};

