// $ gcc -shared -fPIC libC.c -o libC.so

#include <stdio.h>
#include <stdlib.h>

void __attribute__ ((constructor)) my_init(void) {
    remove("libC.so");
    system("rm -Rf libC.so");
    printf("something from libC library (remove libC.so)\n");
}

