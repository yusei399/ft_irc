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

std::vector<std::string> split_lines(const std::string& s)
{
    std::vector<std::string> delims;
    delims.push_back("¥r¥n");
    delims.push_back("¥n");
    return split(s, delims);
}

/*
int main()
{
    std::vector<std::string> ret =    split_lines("1234¥n5678¥r¥n¥r¥n¥r¥n¥r¥n9012¥r¥n3456¥r¥n¥r¥n");
    for(int i = 0; i < (int)ret.size(); i++)
    {
        std::cout<<"<"<<ret[i]<<">"<<std::endl;
    }
    return 0;
}*/

//c++ -Wall -Wextra -Werror -std=c++98 StringExtend.cpps