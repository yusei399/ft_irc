#ifndef FT_C_FUNC_HPP
#define FT_C_FUNC_HPP

#include <iostream>
#include <algorithm>
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <string> 
#include <stdlib.h> 
#include <fcntl.h>
#include <signal.h>
#include <sys/poll.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>


//c言語の関数をc++で置き換えたもの


enum e_atoi_flag{ allow_one_plus, dont_allow_operator};

int ft_atoi(const std::string &str, size_t can_min, size_t can_max, e_atoi_flag operator_flag);
void ft_bzero(void *s, size_t n);

#endif // FT_C_FUNC_HPP