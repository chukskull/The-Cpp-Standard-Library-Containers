#include <map>
#include "map/map.hpp"
#include <iostream>



int main(void)
{

    std::map<int, char> my_map;
    std::map<int, char> my_map2;


    for (int i = -200 ; i < -1; i++)
    {
        my_map2.insert(std::make_pair(i, 'a'));
    }

    for(int i = 1; i < 10000; i++)
    {
        my_map.insert(std::make_pair(i, i));
    }
    
    std::map<int , char>::iterator it = my_map.begin();
    while (it != my_map.end())
    {
        std::cerr << it->first << std::endl;
        it++;
    }
    std::map<int, char>::iterator it_2 = my_map.begin();
    my_map.insert(my_map.begin(), my_map.end());
    my_map.erase(my_map2.begin(), my_map2.end());

    return 0;
}