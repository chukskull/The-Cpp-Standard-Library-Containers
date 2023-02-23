#include "vector.hpp"


int main()
{
    int range_array[] = {547, 98, -6, 0, 47};
    ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));
    ft::vector<int> ft_assign;
    ft_assign.assign(ft_iterator_beg, ft_iterator_beg + 5);
    std::cout << ft_assign.size() << std::endl;
    getchar();
    for(;ft_iterator_beg != ft_assign.end(); ft_iterator_beg++)
    {
        std::cout << *ft_iterator_beg << std::endl;
    }
}