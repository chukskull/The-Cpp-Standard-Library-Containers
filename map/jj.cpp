#include <map>
#include "map.hpp"
#include <iostream>



int main()

{
    //-942, -657, -8,66, 325
   const int range_int[] = {325, -657, -942, -8, 66};
        const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

        std::map<int, std::string> stl_map;
        ft::map<int, std::string> ft_map;

        for (int i = 0; i < 5; i++)
        {
            stl_map.insert(std::make_pair(range_int[i], range_str[i]));
            ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
        }


        std::map<int, std::string>::reverse_iterator stl_it = stl_map.rend();
        ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rend();
        stl_it--;
        ft_it--;

        std::cerr <<  stl_it->first << std::endl;
}
// #include <map>
// #include "map.hpp"
// #include <iostream>



// int main()

// {
//     const int range_int[] = {478, 952, 12, -96, -9};
//     const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
//     ft::map<int, std::string> ft_map;
//      for (int i = 0; i < 5; i++)
//     {
//         ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
//     }
   
//     ft::map<int, std::string>::iterator ft_it = ft_map.begin();
//     for(; ft_it != ft_map.end(); ft_it++)
//     {
//         puts("follow me follow me i can show you what you supposed to see");
//         std::cout << (*ft_it).first;
//         std::cout << " " << (*ft_it).second << std::endl;
//         getchar();
//     }

// }