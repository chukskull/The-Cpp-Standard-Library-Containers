#include <iostream>
#include "vector.hpp"

int main ()
{
  int arr[] = {1, 2,3,4,5,6,7,8,9,19};
  ft::vector<int> vector(5, 69);

  ft::vector<int>  snagat;
  snagat.assign(arr,  arr + sizeof(arr) / sizeof(arr[0]));


  for(size_t i =0; i < snagat.size(); i++)
  {
    std::cout << snagat[i] << std::endl;
  }
  std::cout << snagat.size() << std::endl;
  snagat.assign(vector.begin(), vector.end());

  std::cout << " ------------" << std::endl;

  for(size_t i =0; i < snagat.size(); i++)
  {
    std::cout << snagat[i] << std::endl;
  }
  std::cout << snagat.size() << std::endl;
  return 0;
}
