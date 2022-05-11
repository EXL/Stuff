#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef long long unsigned int uint64;

uint64 __rdtsc()
{
#ifdef _WIN64
    unsigned __int64 val1, val2;
#else
    uint64 val1, val2;
#endif
    __asm__ __volatile__ (
            "rdtsc"
            : "=a" (val1), "=d" (val2));
    return ((uint64)val1) | (((uint64)val2) << 32);
}

int main()
{
    clock_t _time;
    uint64 start = clock(); //__rdtsc();
    _time = clock();
    uint64 end = clock(); //__rdtsc();
    printf("%Lf ms\n", ((long double)end - start) / CLOCKS_PER_SEC);
    return 0;
}
