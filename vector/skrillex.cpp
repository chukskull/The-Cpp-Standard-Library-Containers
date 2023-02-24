#include "vector.hpp"
#include <iostream>


int main()
{

        int range_array_one[] = {144, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        // std::vector<int>::iterator range_array_one(&(range_array_one[0]));
        // std::vector<int>::iterator range_array_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(range_array_one, range_array_one + 5);
        std::vector<int> stl_operator_two(range_array_two, range_array_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);
}
