#include "10.h"

#include <iostream>
#include <algorithm>
#include "../Helpers/Utilities.h"
#include <queue>
#include <unordered_set>

Day10::Day10(std::shared_ptr<IInput>& _input) : input(_input)
{}

namespace {
	class Machine 
	{
	public:


		unsigned long long buttonPresses;
		std::vector<bool> currentIndicatorLight;
	};

	struct VectorHash {
		std::size_t operator()(const std::vector<int>& v) const noexcept {
			std::size_t h = 0;
			for (int x : v) {
				// a simple but effective hash combiner
				h ^= std::hash<int>{}(x)+0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
			}
			return h;
		}
	};
}

std::string Day10::runPart1()
{
	std::string line;

	unsigned long long res = 0;

	while (std::getline(*input, line))
	{
		std::string indicatorLightsRes = "";

		std::vector<std::vector<int>> buttonWiring;

		auto parsed = Util::split(line, " ");

		for (auto c : parsed[0])
		{
			if (c == '[' || c == ']')
				continue;

			indicatorLightsRes.push_back(c == '#' ? '1' : '0');
		}

		for (int i = 1; i < parsed.size() - 1; i++)
		{
			auto button = Util::split(parsed[i], ",");

			std::vector<int> buttons;

			for (auto& s : button)
			{
				if (s.front() == '(')
					s.erase(0, 1);
				if (s.back() == ')')
					s.erase(s.size() - 1);
				buttons.push_back(std::stoi(s));

			}
			buttonWiring.push_back(buttons);
		}
		using wiringTuple = std::tuple<std::string, unsigned long long>;

		auto comp = [](const wiringTuple& t, const wiringTuple& t2)
			{
				return std::get<1>(t) > std::get<1>(t2);
			};
		
		std::string currLights(indicatorLightsRes.size(), '0');
		wiringTuple tuple{ currLights, 0 };
		std::priority_queue< wiringTuple,std::vector<wiringTuple>, decltype(comp)> q(comp);

		q.push(tuple);

		std::unordered_set<std::string> seen;

		while (!q.empty())
		{
			auto t = q.top();
			q.pop();

			if (seen.find(std::get<0>(t)) != seen.end())
				continue;

			seen.insert(std::get<0>(t));

			if (std::get<0>(t) == indicatorLightsRes)
			{
				res += std::get<1>(t);
				break;
			}

			for (auto& v : buttonWiring)
			{
				auto lights = std::get<0>(t);

				for (auto l : v)
				{
					bool b = lights.at(l) == '1';
					b = !b;
					lights.at(l) = b ? '1' : '0';
				}

				q.push({ lights, std::get<1>(t) + 1 });
			}
		}
	}

	return std::to_string(res);
}

std::string Day10::runPart2()
{
	std::string line;

	unsigned long long res = 0;

	while (std::getline(*input, line))
	{
		std::string indicatorLightsRes = "";

		std::vector<std::vector<int>> buttonWiring;

		auto parsed = Util::split(line, " ");

		for (int i = 1; i < parsed.size() - 1; i++)
		{
			auto button = Util::split(parsed[i], ",");

			std::vector<int> buttons;

			for (auto& s : button)
			{
				if (s.front() == '(')
					s.erase(0, 1);
				if (s.back() == ')')
					s.erase(s.size() - 1);
				buttons.push_back(std::stoi(s));

			}
			buttonWiring.push_back(buttons);
		}

		auto voltage = Util::split(parsed.back(), ",");

		std::vector<int> voltageRes;

		for (auto& s : voltage)
		{
			if (s.front() == '{')
				s.erase(0, 1);
			if (s.back() == '}')
				s.erase(s.size() - 1);

			voltageRes.push_back(std::stoi(s));

		}

		sort(buttonWiring.begin(), buttonWiring.end(), [](const auto& l1, const auto& l2)
			{
				return l1.size() > l2.size();
			});

		using wiringTuple = std::tuple<std::vector<int>, unsigned long long>;

		auto comp = [&voltageRes](const wiringTuple& t, const wiringTuple& t2)
			{
				if (std::get<1>(t) != std::get<1>(t2))
					return std::get<1>(t) > std::get<1>(t2);
				
				int res1 = 0;
				int res2 = 0;
				for (int i = 0; i < voltageRes.size(); i++)
				{
					res1 += voltageRes.at(i) - std::get<0>(t).at(i);
					res2 += voltageRes.at(i) - std::get<0>(t2).at(i);
				}

				return res1 > res2;
			};

		std::vector<int> currLights(voltageRes.size(), 0);
		wiringTuple tuple{ currLights, 0 };
		std::priority_queue< wiringTuple, std::vector<wiringTuple>, decltype(comp)> q(comp);

		q.push(tuple);

		std::unordered_set<std::vector<int>, VectorHash> seen;

		while (!q.empty())
		{
			auto t = q.top();
			q.pop();

			if (seen.find(std::get<0>(t)) != seen.end())
				continue;

			seen.insert(std::get<0>(t));

			if (std::get<0>(t) == voltageRes)
			{
				res += std::get<1>(t);
				break;
			}

			for (auto& v : buttonWiring)
			{
				auto lights = std::get<0>(t);

				bool validButtonPress = true;

				for (auto l : v)
				{
					lights.at(l)++;

					if (lights.at(l) > voltageRes.at(l))
					{
						validButtonPress = false;
						break;
					}
				}

				if (!validButtonPress)
					continue;

				q.push({ lights, std::get<1>(t) + 1 });
			}
		}
	}

	return std::to_string(res);
}

