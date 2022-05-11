#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

char *e_tmpname = "/tmp/perl-eXXXXXX";

int main(void) {
    char buff[NAME_MAX];
    strncpy(buff, e_tmpname, strlen(e_tmpname) + 1);
    mkstemp(buff);
    fprintf(stderr, "%s\n", buff);
}
