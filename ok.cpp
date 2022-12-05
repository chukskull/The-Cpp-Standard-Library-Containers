#include <iostream>
namespace A
{
    namespace N
    {
        void f();// found 3rd (if 2nd is not present)
    }
     // found 4th (if 3rd is not present)
}
 
int i = 5;         // found 5th (if 4th is not present)
 
void A::N::f()
{     // found 2nd (if 1st is not present)
 
    while(true)
    {  // found 1st: lookup is done
       std::cout << i;
    }
}
 
// int i;          // not found
 
namespace A
{
    namespace N
    {
        // int i;  // not found
    }
}
int main()
{
    A::N::f();
}