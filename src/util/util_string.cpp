#include <string>
#include <vector>
#include <regex>

namespace ns {
std::string strip(std::string s){
  size_t n = s.find_last_not_of(" \r\n\t");
    if (n != std::string::npos){
        s.erase(n + 1, s.size() - n);
    }
    n = s.find_first_not_of(" \r\n\t");
    if (n != std::string::npos){
        s.erase(0, n);
    }
    return s;
}

std::string remove_surplus_spaces(const std::string& src)
{
    std::string result = "";
    for(std::size_t i = 0; i < src.size(); i++)
    {
        if(src[i] != ' ' )
            result.append(1,src[i]);
        else
            if(src[i+1] != ' ')
                result.append(1,src[i]);
    }
    return result;
}

std::vector<std::string> split(const std::string& input, const std::string& c=",")
{
    std::regex re(c);
    std::sregex_token_iterator p(input.begin(), input.end(), re, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> vec;
    while (p != end)
        vec.emplace_back(*p++);
    return vec;
}

std::string getDir(const std::string& input)
{
    std::size_t pos = input.find_last_of("/");
    return input.substr(0,pos);
}

}
