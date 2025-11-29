#pragma once

#include "IInput.h"

class Input : public IInput
{
public:
	Input(const std::string& day);

	void resetStream() override;
};

