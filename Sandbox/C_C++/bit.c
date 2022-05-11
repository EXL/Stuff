#include <stdio.h>

int main() {
    printf("%lu\n", (sizeof(void *) << 3));
    return 0;
}
