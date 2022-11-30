#include "vector.hpp"

#include <iostream>


void  func()
{
  system("leaks a.out");

}

int main ()
{
  // constructors used in the same order as described above:
  // ft::vector<int> first;                                // empty vector of ints
  ft::vector<int> second(19,100);
  ft::vector<int> third(second);
  std::cout << second.size() << std::endl;
  for (size_t i = 0; i < 19; i++)
  {
    std::cout << *(second.get_array()) <<std::endl;
  }
  std::cout << "-------------------" <<std::endl;
  std::cout << third.size() << std::endl;
  for (size_t i = 0; i < 19; i++)
  {
    std::cout << *(third.get_array()) <<std::endl;
  }
  
                     // four ints with value 100
  // ft::vector<int> third (second.begin(),second.end());  // iterating through second
// ft::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  // int myints[] = {16,2,77,29};
  // ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

//   std::cout << "The contents of fifth are:";
//   for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';
func();
  return 0;
}