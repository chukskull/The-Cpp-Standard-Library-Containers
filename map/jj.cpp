#include <iostream>
#include "map.hpp"
#include <string>

int main() {
    ft::map<int, int> my_map;
    my_map.insert(ft::make_pair(1, 1));
    my_map.insert(ft::make_pair(2, 2));
    my_map.insert(ft::make_pair(3, 3));
    my_map.insert(ft::make_pair(5, 4));
    my_map.insert(ft::make_pair(6, 6));
    
    ft::map<int, int>::iterator it = my_map.begin();
    while (it != my_map.end())
    {
        std::cout << it->first << it->second << std::endl;
        it++;
    }
    
    return 0;
}
