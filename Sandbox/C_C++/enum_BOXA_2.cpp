#include <cstdio>

enum iterable {
    BOXA_1, BOXA_2,
    BOXA_3, BOXA_4,
    BOXA_5, BOXA_6,
    BOXA_7, BOXA_8
};
const int E_SIZE = 8;

inline iterable operator++ (iterable &i) {
    i = static_cast<iterable>((static_cast<int>(i) + 1) % E_SIZE);
    return i;
}

int main(void) {
    iterable s = BOXA_1;
    for (int i = 0; i < 16; ++i) {
        fprintf(stderr, "%d\n", s);
        ++s;
    }
}

