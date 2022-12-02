#include <unistd.h>
#include <stdio.h>



int main()
{
    int d = 19;
    int p = 0;

    if (d >= 0)
        while(d--)
        {
            ++p;
            write(1, "c", 1);   
        }
    else
        while(d++)
            --p;
    printf("%d\n", p);
    return 0;
}