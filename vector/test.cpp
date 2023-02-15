#include <iostream>
#include "vector.hpp"


int main(){
    ft::vector<int> a(5, 4);

    ft::vector<int>::const_iterator it = a.begin();

    *it = 1;
    while (it != a.end())
    {
       std::cout << *it << std::endl;
       it++;
    }
    
    
}