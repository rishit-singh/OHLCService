#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

namespace OHLCService::Util
{  
    /// @brief Splits a string on a character 
    /// @param str String to split
    /// @param c Character to split on
    std::vector<std::string> Split(std::string, char);   
}

#endif