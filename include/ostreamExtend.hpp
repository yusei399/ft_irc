# ifndef OSTREAM_EXTEND_HPP
# define OSTREAM_EXTEND_HPP
#include<ostream>
#include<set>

template<class T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& set)
{
	for(typename std::set<T>::iterator it = set.begin(); it != set.end(); it++)
	{
		os<< *it <<", ";
	}
	return os;
}

#endif