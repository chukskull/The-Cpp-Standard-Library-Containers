#ifndef LEXICROPHICAL_HPP
# define LEXICROPHICAL_HPP

namespace ft
{
template<class iter, class iter2>
bool
lexicographical_compare(iter first1, iter last1, iter2 first2, iter2 last2)
{
    for(; first1 != last1; ++first1, ++first2)
    {
        if(first2 == last2 || *first2 < *first1)
            return false;
        else
            return true;
    }
    return first2 != last2;
}

}





#endif