// $ gcc -shared -fPIC libD.c -o libD.so -ldl

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

static int (*system_orig)(const char *__command) = NULL;
static int (*remove_orig)(const char *__filename) = NULL;

int system(const char *command) {
    if (system_orig == NULL) {
        system_orig = dlsym(RTLD_NEXT, "system");
    }
    printf("override system!\n");
    return 0;
//    return system_orig();
}

int remove(const char *filename) {
    if (remove_orig == NULL) {
        remove_orig = dlsym(RTLD_NEXT, "remove");
    }
    printf("override remove!\n");
    return 0;
//    return remove_orig();
}

