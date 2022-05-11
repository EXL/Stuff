#include <stdio.h>

int foo(const char *s)
{
        int r = 0;
        while(*s) {
                r += ((r * 20891 + *s *200) | *s ^ 4 | *s ^ 3 ) ^ (r >> 1);
                s++;
        }
        return r & 0x7fffffff;
}
int foo2(int c)
{
        return c & 0x7fffffff;
}

int main()
{
        int result = foo("simple simple some words whatever");
        printf("result: %d %08x\n", result, result);
        result = foo2(-100);
        printf("result: %d %08x\n", result, result);
        return 0;
}

