#include <stdio.h>

int main(void) {
    short high = 0x447A;
    short low = 0x2000;

    int combined = (high << 16) | low;
    float z = *((float*) &combined);
    printf("%f\n", z);
    return 0;
}
