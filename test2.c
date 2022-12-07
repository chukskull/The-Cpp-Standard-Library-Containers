#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *m = malloc(sizeof(char *) * 12+ 1);
    char *lol = malloc(sizeof(char *) * 18 + 1);
    char *ptr;
    lol = "aiisdominating";
    m = "salehnagato";
    ptr = m;
    m = malloc(sizeof(char *) * 17 + 1);
    m = "anpther";
    

    printf("%s\n", m);
    printf("%s\n", ptr);
}