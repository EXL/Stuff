#include <SDL2/SDL.h>

int main (int argc, char** argv)
{
    SDL_Window* window = NULL;
    window = SDL_CreateWindow(
        "SDL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor( renderer, 0, 200, 0, 255);

    SDL_RenderClear(renderer);

    SDL_Rect r[1];
    r[0].x =  90;
    r[0].y =  10;
    r[0].w = 460;
    r[0].h = 460;

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &r[0]);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

