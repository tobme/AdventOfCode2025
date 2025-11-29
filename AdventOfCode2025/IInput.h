#pragma once

#include <fstream>
#include <vector>

class IInput : public std::fstream
{
public:
	IInput(const std::string& day) : std::fstream(day) {}
	~IInput() = default;

	virtual void resetStream() = 0;
};