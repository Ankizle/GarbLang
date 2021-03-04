#include <stdlib.h>

int main()
{

    void *a = malloc(1);

    for (int i = 0; i < 1000000;)
        a = realloc(a, ++i);
}