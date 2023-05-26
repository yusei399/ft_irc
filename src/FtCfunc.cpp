#include "FtCfunc.hpp"

/// @brief 正の値のみに対応、基本的に+-を許さない
/// @param str
/// @param can_min 変換の下限値。
/// @param can_max 変換の上限値。
/// @param e_atoi_flag allow_one_plusなら先頭に+を一つまで許す
/// @return 成功したらatoiの結果を返し、失敗したら-1を返す。
int ft_atoi(const std::string &str, size_t can_min, size_t can_max, e_atoi_flag operator_flag)
{
    assert(can_min < can_max && can_max <= INT_MAX);
    unsigned long i = 0;
    size_t val = 0;
    bool valid = false;
    if (operator_flag == allow_one_plus && str[0] == '+')
        i++;
    val = 0;
    for (; i < str.size(); i++)
    {
        if (!('0' <= str[i] && str[i] <= '9'))
            return -1;
        val = val * 10 + (str[i] - '0');
        if (val > can_max)
            return -1;
        valid = true;
    }
    if (!valid)
        return -1;
    if (val < can_min)
        return -1;
    return (int)val;
}

void ft_bzero(void *s, size_t n)
{
    char *p = (char *)s;
    while (n > 0)
    {
        *p = 0;
        p++;
        n--;
    }
}