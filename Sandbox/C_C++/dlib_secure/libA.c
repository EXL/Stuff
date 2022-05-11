// $ gcc -shared -fPIC libA.c -o libA.so

#include <stdio.h>

void something(void) {
    printf("something from libA library\n");
}
