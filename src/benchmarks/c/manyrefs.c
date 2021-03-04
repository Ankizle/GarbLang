#include <stdlib.h>

typedef int (*f)();

void *shared;

int ret()
{
    return (int)shared;
}

f test()
{
    void *local1 = malloc(4);
    void *local2 = malloc(4);
    void *local3 = malloc(4);
    void *local4 = malloc(4);
    void *local5 = malloc(4);
    void *local6 = malloc(4);
    void *local7 = malloc(4);
    void *local8 = malloc(4);
    void *local9 = malloc(4);

    shared = malloc(1);

    free(local1);
    free(local2);
    free(local3);
    free(local4);
    free(local5);
    free(local6);
    free(local7);
    free(local8);
    free(local9);
    return ret;
}

int main()
{
    for (int i = 0; i < 1000000; i++)
        test()();
    free(shared);
}