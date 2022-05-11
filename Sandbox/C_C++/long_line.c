#include <string.h>
#include <stdio.h>

const char *test_string = "aaa\nbbbb\nccccc\nddddddd";

int main(int argc, char *argv[])
{
    int i = 0, c = 0, f = 0;
    for (; i < strlen(test_string); ++i) {
        c++;
        if (test_string[i] == '\n') {
            c = 0;
        }
        if (c > f)
            f = c;
    }
    printf("%s %d\n", test_string, f);
    return 0;
}
