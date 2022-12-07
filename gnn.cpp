#include <iostream>
#include "vector.hpp"
#include <vector>


#include <iostream>
#include <vector>


void  func()
{
  system("leaks a.out");
}

int main ()
{
  ft::vector<int> myvector;

  // set some initial content:
  for (int i = 1;i < 10;i++)
     myvector.push_back(i);

  
  myvector.assign(5, 10);

  std::cout << "myvector contains:";
  for (int i=0;i<myvector.size();i++)
  {
    std::cout << " am here " << myvector[i];
  }
  std::cout << '\n';
    std::cout << myvector.capacity() << std::endl;
    std::cout << myvector.size() << std::endl;
  func();
  // while(1);
  return 0;
}

