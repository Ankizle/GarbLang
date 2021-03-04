#include <stdlib.h>
#include <stdio.h>

typedef int (*f)();

void *shared;

int ret()
{
    return (int)shared;
}

f test()
{
    shared = malloc(5);
    return ret;
}

int main()
{

    for (int i = 0; i < 1000000; i++)
        test()();
    free(shared);
}