#include "Input.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

Input::Input(const std::string& day) : IInput(day)
{

}

void Input::resetStream()
{
    this->clear();
    this->seekg(0);
}