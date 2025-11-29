#pragma once

#include<vector>
#include "../IInput.h"
#include <functional>
#include "Utilities.h"

template<typename T>
std::vector<std::vector<T>> ToMatrix(std::shared_ptr<IInput>& input, std::function<T(std::string)> func = Util::transformConverter<T>, const std::string& delimeter = " ");