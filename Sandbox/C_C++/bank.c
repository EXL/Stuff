#include <stdio.h>

#define SIZE 4

char sins[] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    2, 2, 2, 2,
    3, 3, 3, 3,
};

int bank = 0;

void print() {
    int s = bank * SIZE;
    int i = s;
    for (; i < s + SIZE; ++i) {
        printf("%d ", sins[i]);
    }
    printf("\n");
}

int main() {
    print();
    bank = 3;
    print();
    bank = 1;
    print();
}
