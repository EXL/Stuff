// $ gcc -shared -fPIC libB.c -o libB.so -ldl

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

static void (*something_orig)(void) = NULL;

void something(void) {
    if (something_orig == NULL) {
        something_orig = dlsym(RTLD_NEXT, "something");
    }
    printf("something from libB library\n");
    dlopen("libC.so", 258);
    return something_orig();
}
