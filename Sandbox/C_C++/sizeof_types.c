#include <stdio.h>

int main (int argc, char *argv[])
{
    char *a; long *b; int *c; void *d;
    char e; long f; int g; short i;
    printf("Bitness:\t%u\n\n"
           "char\t*a:\t%u\n"
           "long\t*b:\t%u\n"
           "int\t*c:\t%u\n"
           "void\t*d:\t%u\n\n"
           "char\te:\t%u\n"
           "long\tf:\t%u\n"
           "int\tg:\t%u\n"
           "short\ti:\t%u\n",
           (unsigned int)(sizeof(void *)<<3),
           (unsigned int)sizeof(a),
           (unsigned int)sizeof(b),
           (unsigned int)sizeof(c),
           (unsigned int)sizeof(d),
           (unsigned int)sizeof(e),
           (unsigned int)sizeof(f),
           (unsigned int)sizeof(g),
           (unsigned int)sizeof(i));
    return 0;
}

