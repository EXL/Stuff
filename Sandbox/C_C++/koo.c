// koo.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    if (argc != 3) {
        fprintf(stdout, "Usage:\n\t./koo 100 c\n");
        return 1;
    }
    int it = atoi(argv[1]);
    if (it <= 0)
        it = 100 * 1000;
    else
        it *= 1000;
    while(1) {
        fprintf(stdout, "%s\n", argv[2]);
        usleep(it);
    }
    return 0;
}
