#include <cstdio>

enum iterable {
    BOXA_1, BOXA_2,
    BOXA_3, BOXA_4,
    BOXA_5, BOXA_6
};

const iterable Iterable[] = {
    BOXA_1, BOXA_2,
    BOXA_3, BOXA_4,
    BOXA_5, BOXA_6
};

int main(void) {
    for (iterable it : Iterable) {
        fprintf(stderr, "%d\n", it);
    }
    return 0;
}
