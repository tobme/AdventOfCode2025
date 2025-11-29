#include "23.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"
#include <unordered_map>
#include<unordered_set>
#include <map>
#include<queue>

std::unordered_map<std::string, std::unordered_set<std::string>> connections;
std::vector<std::unordered_set<std::string>> lanConnections;

Day23::Day23(std::shared_ptr<IInput>& _input) : input(_input)
{}

size_t hashThreeStrings(const std::string& str1, const std::string& str2, const std::string& str3) {
	std::hash<std::string> hash_fn;

	// Store the strings in a vector
	std::vector<std::string> strings = { str1, str2, str3 };

	// Sort the strings to ensure order doesn't matter
	std::sort(strings.begin(), strings.end());

	// Hash each string after sorting
	size_t final_hash = 0;
	for (const auto& str : strings) {
		final_hash ^= hash_fn(str) + 0x9e3779b9 + (final_hash << 6) + (final_hash >> 2); // XOR and shift
	}

	return final_hash;
}

void interconnected(const std::string& startPos, const std::string& currPos, const std::unordered_set<std::string>& visited)
{
	for (auto& c : connections[currPos])
	{
		if (visited.size() == 3)
		{
			if (c == startPos)
			{
				lanConnections.push_back(visited);
			}
			else
				continue;
		}
		if (!visited.contains(c))
		{
			auto cpy = visited;
			cpy.insert(c);
			interconnected(startPos, c, cpy);
		}
	}
}

std::string Day23::runPart1()
{
	std::string s;
	
	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, "-");
		connections[ss[0]].insert(ss[1]);
		connections[ss[1]].insert(ss[0]);
	}

	std::unordered_map<unsigned long long, std::unordered_set<std::string>> interConnMap;

	for (auto& m : connections)
	{
		interconnected(m.first, m.first, std::unordered_set<std::string>{m.first});
	}

	std::hash<std::string> hasher;

	for (auto& c : lanConnections)
	{
		if (!c.empty())
		{
			unsigned long long id = 0;

			bool containsT = false;
			std::vector<std::string> tmpV;
			for (auto& cc : c)
			{
				if (cc.front() == 't')
					containsT = true;
				tmpV.push_back(cc);
			}

			id = hashThreeStrings(tmpV[0], tmpV[1], tmpV[2]);

			if (containsT)
			{
				if (interConnMap.contains(id))
				{
					for (auto& tmp : c)
					{
						if (!interConnMap[id].contains(tmp))
						{
							std::cout << "WTF" << std::endl;
						}
					}
				}
				else
					interConnMap[id] = c;
			}
		}
	}


	return std::to_string(interConnMap.size());
}

size_t hashVectorOfStrings(const std::unordered_set<std::string>& strings, const std::string& currPos) {
	std::hash<std::string> hash_fn;

	// Create a copy of the input vector to sort it
	std::vector<std::string> sorted_strings{ currPos };
	for (auto& s : strings)
		sorted_strings.push_back(s);

	// Sort the strings to ensure order doesn't matter
	std::sort(sorted_strings.begin(), sorted_strings.end());

	// Combine the hashes of each string after sorting
	size_t final_hash = 0;
	for (const auto& str : sorted_strings) {
		final_hash ^= hash_fn(str) + 0x9e3779b9 + (final_hash << 6) + (final_hash >> 2); // XOR and shift
	}

	return final_hash;
}

size_t hash_vector_independent_of_order(const std::unordered_set<std::string>& vec, const std::string& s) {
	// Use an unordered_set to remove duplicates and eliminate the order dependency
	std::unordered_set<std::string> unique_strings = vec;
	unique_strings.insert(s);

	size_t hash_value = 0;

	// Combine the hashes of each string in the unordered set
	for (const auto& str : unique_strings) {
		hash_value ^= std::hash<std::string>{}(str)+0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
	}

	return hash_value;
}

std::unordered_map<size_t, std::vector<std::string>> memory;

std::vector<std::string> interconnected2(const std::string& currPos)
{
	auto& con = connections[currPos];

	//auto id = hash_vector_independent_of_order(visited, currPos);

	/*
	if (memory.contains(id))
	{
		return memory[id];
	}
	*/

	std::unordered_set<std::string> visited;
	visited.insert(currPos);

	std::vector<std::string> res{ currPos };

	for (auto& c : con)
	{
		bool fail = false;
		for (auto& cc : visited)
		{
			if (!connections[c].contains(cc))
			{
				fail = true;
				break;
			}
		}
		
		if (!fail)
		{
			visited.insert(c);
			res.push_back(c);
		}
	}

	//memory[id] = res;

	return res;
}

std::string Day23::runPart2()
{
	std::string s;

	while (std::getline(*input, s))
	{
		auto ss = Util::split(s, "-");
		connections[ss[0]].insert(ss[1]);
		connections[ss[1]].insert(ss[0]);
	}

	std::vector<std::string> res;


	for (auto& m : connections)
	{
		auto tmp = std::max(res, interconnected2(m.first));
		
		if (tmp.size() > res.size())
			res = tmp;

		if (tmp.size() == 13)
			break;
	}

	std::sort(res.begin(), res.end());

	std::string ret;
	for (auto& s : res)
	{
		ret += s + ",";
	}
	ret.pop_back();

	return ret;
}

