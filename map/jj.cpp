#include <iostream>
#include "map.hpp"
#include <string>

int main() {
    ft::map<int, std::string, std::greater<int> > my_map;
    my_map.insert(ft::make_pair(6, "betcha"));
    my_map.insert(ft::make_pair(1, "skrillex"));
    my_map.insert(ft::make_pair(3, "getter"));
    my_map.insert(ft::make_pair(5, "arctic mnkys"));
    my_map.insert(ft::make_pair(2, "lanadelrey"));

    // std::cout << my_map.size() << std::endl;
    // std::cout << my_map[3] << std::endl;
    // // std::cerr << " astder " << std::endl;
    my_map.erase(3);
    ft::map<int, std::string,std::greater<int> >::iterator it = my_map.begin();
    // std::cout << "end " <<my_map.end()->first << std::endl;
    while (it != my_map.end())
    {
        std::cout << it->first<< " " << it->second << std::endl;
        it++;
    }
    ft::map<int, std::string, std::greater<int> >::iterator np = my_map.find(15);

    std::cout << np->first << std::endl;
    // my_map.clear();
    // std::cout << my_map.empty() << std::endl;
    // std::cout << my_map.size() << std::endl;
    // std::cout << my_map[2] << std::endl;
    return 0;
}
