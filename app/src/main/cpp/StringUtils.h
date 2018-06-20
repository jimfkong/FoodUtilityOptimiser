//
// Created by Jim on 30/05/2018.
//

#ifndef FOODUTILITYOPTIMISER_STRINGUTILS_H
#define FOODUTILITYOPTIMISER_STRINGUTILS_H

#include <string>
#include <sstream>
#include <vector>

class StringUtils
{
public:
    static std::vector<std::string> splitString(const std::string& string, const char delim)
    {
        std::vector<std::string> result;
        std::stringstream ssInput(string);
        std::string token;
        while (std::getline(ssInput, token, delim))
        {
            result.push_back(token);
        }

        return result;
    }
};
#endif //FOODUTILITYOPTIMISER_STRINGUTILS_H
