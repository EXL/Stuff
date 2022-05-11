#include <stdlib.h>
#include <SDL/SDL.h>

#define MAX_STARS 2000

int left = 0;

unsigned char *keys;

typedef struct
{
    int x, y, speed;
} star_type;

star_type stars[MAX_STARS];

int main()
{
    int i;
    Uint8 *p;
    SDL_Surface *screen;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event ev;

    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
    for (i = 0; i < MAX_STARS; ++i) {
        stars[i].x = rand() % 640;
        stars[i].y = rand() % 480;
        stars[i].speed = 1 + rand() % 16;
    }

    for (i = 0; i < SDL_NUMEVENTS; ++i) {
        if (i != SDL_QUIT) {
           SDL_EventState(i, SDL_IGNORE);
        }
    }

    while (SDL_PollEvent(NULL) == 0) {

        keys = SDL_GetKeyState(NULL);

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        for (i = 0; i < MAX_STARS; ++i) {

            switch (left) {
                case 0:
                    stars[i].x += stars[i].speed;
                    if (stars[i].x >= 640) {
                        stars[i].x = 0;
                    }
                    break;
                case 1:
                    stars[i].x -= stars[i].speed;
                    if (stars[i].x <= 0) {
                        stars[i].x = 640;
                    }
                    break;
                case 2:
                    stars[i].y -= stars[i].speed;
                    if (stars[i].y <= 0) {
                        stars[i].y = 480 - 1;
                    }
                    break;
                case 3:
                    stars[i].y += stars[i].speed;
                    if (stars[i].y >= 480) {
                        stars[i].y = 0;
                    }
                    break;

            }

            p = (Uint8 *) screen->pixels + stars[i].y * screen->pitch + stars[i].x * screen->format->BytesPerPixel;
            *p = 255;
        }
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_Delay(30);

        if (keys[SDLK_LEFT] == SDL_PRESSED) {
            left = 1;
        } else if (keys[SDLK_RIGHT] == SDL_PRESSED) {
            left = 0;
        } else if (keys[SDLK_DOWN] == SDL_PRESSED) {
            left = 2;
        } else if (keys[SDLK_UP] == SDL_PRESSED) {
            left = 3;
        } else if (keys[SDLK_ESCAPE] == SDL_PRESSED) {
            break;
        }
    }

    return 0;
}
