//////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <map>
#include <chrono>
#include <iostream>
#include <stdlib.h>

typedef int (*genf)();

std::map<void *, std::vector<void *>> links;

void gfree(void *p)
{

    std::vector<void *> b = links[p];

    for (void *i : b)
        free(i);
}

void gbind(void *p0, void *p1)
{

    if (links.find(p1) == links.end())
    {
        std::vector<void *> v = std::vector<void *>();
        links[p1] = v;
    }

    links[p1].push_back(p0);
}
//////////////////////////////////////////////////////////////////////////////////////////////
long long *v0();
long long *v2;
long long *v3;
long long *v4;
long long *v0()
{
    v2 = (long long *)calloc(1, 1);
    v3 = (long long *)calloc(1, 1);
    v4 = (long long *)calloc(1, 1);
    v3[0] = -100000;
    v4[0] = 1;
l1:;
    *v3 += *v4;
    if (*v3 < 0)
        goto l1;
    gfree(v3);
    gfree(v4);
    gbind(v2, v2);
    return (long long *)v2;
}
int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    v0();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Execution Speed: " << duration.count() << " microseconds" << std::endl;
}