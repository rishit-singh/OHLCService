#include <util.hpp>

std::vector<std::string> OHLCService::Util::Split(std::string str, char c)
{
    std::vector<std::string> split;
        
    auto start = str.begin();

    for (auto it = str.begin(); it != str.end(); it++)
        if (*it == c)
        {
            split.push_back(std::string(start, it));
            
            start = it + 1;
        }
        else if (it == str.end() - 1)
        {
            split.push_back(std::string(start, it + 1));
        }
    
    return split;

}