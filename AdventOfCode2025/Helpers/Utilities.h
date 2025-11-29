#pragma once

#include<vector>
#include<string>

namespace Util
{
	template<typename T>
	T transformConverter(const std::string& s);

	std::vector<std::string> split(std::string s, std::string delimiter);

	bool isInBounds(const std::pair<int, int>& pos, const std::vector<std::vector<char>>& matrix);

    int random(int start, int end);

	void print(const std::vector<std::vector<char>>& matrix, const std::pair<int,int>& pos);
}