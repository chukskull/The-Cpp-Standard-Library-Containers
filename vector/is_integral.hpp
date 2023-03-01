#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP


#include <iostream>


namespace ft
{
template<class T>
struct is_integral
{
    static const bool value;

};

template <class T>
const bool is_integral<T>::value = std::numeric_limits<T>::is_integer;

};


#endif