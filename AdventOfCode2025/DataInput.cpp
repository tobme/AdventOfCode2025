#pragma once

#include "DataInputEnvironment.h"

#include "IInput.h"
#include "Input.h"

#include <memory>
#include <string>
#include<iostream>

static std::shared_ptr<IInput> fetchData(const std::string& day, const DataInputEnvironment& env)
{

	std::string path = day + "/" + (env == DataInputEnvironment::TEST_DATA ? "TestData" : "InputData") + ".txt";

	auto file = std::make_shared<Input>(path);

	if (!*file)
	{
		std::cout << "Error opening file" << std::endl;
		return nullptr;
	}

	return file;
}

static void sendData(const std::string& answer, const DataInputEnvironment& env)
{

}

