#include <stdlib.h>
#include <stdio.h>

typedef int (*f)();

void **shared;

int ret()
{
    return (int)shared;
}

f test()
{
    shared = calloc(100, 5);
    for (int i = 0; i < 100; i++)
        shared[i] = malloc(5);
    return ret;
}

int main()
{

    for (int i = 0; i < 100000; i++)
        test()();
    free(shared);
}