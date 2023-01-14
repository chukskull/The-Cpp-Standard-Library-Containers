
#include <iostream>
#include "vector.hpp"
#include <vector>

int main() {
    ft::vector<int> vec(12, 2);
    
    // insert value 6 at the end of the vector
    vec.insert(vec.begin() + 4, 4, 77);   
    // std::cerr << "here" << '\n';
    for (int i = 0; i  < vec.size(); i++)
    {
        std::cerr << vec[i] << std::endl;
    }
    // system("leaks a.out");
    // vec.insert(vec.end(), 6);
    // // insert value 7 at position 3
    // vec.insert(vec.begin() + 3, 7);

    // std::cout << "Vector contains: ";
    // for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
    //     std::cout << *it << " ";
    // }

    return 0;
}
