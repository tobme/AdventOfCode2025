#include "InputTransformer.h"

#include "Utilities.h"

template<typename T>
std::vector<std::vector<T>> ToMatrix(std::shared_ptr<IInput>& input, std::function<T(std::string)> func, const std::string& delimeter)
{
    input->resetStream();

    std::vector<std::vector<T>> matrix;

    std::string s;

    while (std::getline(*input, s))
    {
        auto line = Util::split(s, delimeter);
        std::vector<T> row{};

        for (const std::string& c : line)
        {
            row.push_back(func(c));
        }

        matrix.push_back(row);
    }

    return matrix;
}

template<>
std::vector<std::vector<char>> ToMatrix(std::shared_ptr<IInput>& input, std::function<char(std::string)> func, const std::string& delimeter)
{
    input->resetStream();

    std::vector<std::vector<char>> matrix;

    std::string s;

    while (std::getline(*input, s))
    {
        std::vector<char> row{};

        for (char c : s)
        {
            row.push_back(c);
        }

        matrix.push_back(row);
    }

    return matrix;
}

template std::vector<std::vector<int>> ToMatrix<int>(std::shared_ptr<IInput>& input, std::function<int(std::string)> func, const std::string& delimeter);
template std::vector<std::vector<double>> ToMatrix<double>(std::shared_ptr<IInput>& input, std::function<double(std::string)> func, const std::string& delimeter);
template std::vector<std::vector<char>> ToMatrix<char>(std::shared_ptr<IInput>& input, std::function<char(std::string)> func, const std::string& delimeter);
template std::vector<std::vector<unsigned long long>> ToMatrix<unsigned long long>(std::shared_ptr<IInput>& input, std::function<unsigned long long(std::string)> func, const std::string& delimeter);