#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

int rwgetc(SDL_RWops *rw)
{
    unsigned char c;
    return SDL_RWread(rw, &c, 1, 1) == 1 ? c : EOF;
}

int file_size(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    rewind(fp);
    return sz;
}

int main(void)
{
    FILE *fp = NULL;
    fp = fopen("donothexedit.me", "rb");
    if (fp == NULL) { printf("WTF?"); }
    int i = 0, j = file_size(fp);
    for (int i = 0; i < j; ++i) {
        printf("%d ", fgetc(fp));
    }
    printf("\n");
    fclose(fp);

    SDL_RWops *rw = SDL_RWFromFile("donothexedit.me", "rb");
    int size = SDL_RWsize(rw);
    for (int i = 0; i < size; ++i) {
        printf("%d ", rwgetc(rw));
    }
    printf("\n");
    SDL_RWclose(rw);

    exit(0);
}
