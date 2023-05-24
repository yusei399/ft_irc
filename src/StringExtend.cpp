#include "../include/StringExtend.hpp"

std::vector<std::string> split(const std::string& s, const std::vector<std::string>& t)
{
    std::vector<std::string> splited;
    size_t word_l = 0;

    while(word_l < s.size())
    {
        size_t word_r = s.size();
        size_t delim_len = 0;
        for(size_t j = 0; j < t.size(); j++)
        {
            size_t r = s.find(t[j], word_l);
            if (r != std::string::npos && word_r > r)
            {
                word_r = r;
                delim_len = t[j].size();
            }
        }
        if (word_l < word_r)
            splited.push_back(s.substr(word_l, word_r - word_l));
        word_l = word_r + delim_len;
    }
    return splited;
}

std::vector<std::string> split(const std::string& s, const std::string& t)
{
    return split(s, std::vector<std::string>(1, t));
}

std::vector<std::string> split_lines(const std::string& s)
{
    std::vector<std::string> delims;
    delims.push_back(std::string("\r\n"));
    delims.push_back(std::string("\n"));
    return split(s, delims);
}
