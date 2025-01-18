#include "benchmark.h"
#include <stdio.h>

int main()
{
    int n1 = 1;
    int n3 = 1;
    int* ip;
    real_t s1,s2;

    init(&ip, &s1, &s2);
    
    time_function(&s000, NULL);
    return 0;
}
