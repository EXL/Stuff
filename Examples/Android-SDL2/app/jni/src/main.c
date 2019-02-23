// https://github.com/suikki/simpleSDL/blob/master/source/main.c
// (c) suikki

#include <SDL.h>

static int done = 0;
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static SDL_Texture* texture = NULL;

int init() {
    int width = 640;
    int height = 480;
    Uint32 flags = 0;

#if defined(__ANDROID__)
    flags |= SDL_WINDOW_FULLSCREEN;
#endif

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    window = SDL_CreateWindow("SimpleSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if (!window) {
        SDL_Log("Creating window failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Creating renderer failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    const char* fileName = "sdl.bmp";
    SDL_Surface* bitmap = SDL_LoadBMP(fileName);
    if (!bitmap) {
        SDL_Log("Loading bitmap '%s' failed: %s", fileName, SDL_GetError());
        SDL_ClearError();
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(renderer, bitmap);
    SDL_FreeSurface(bitmap);
    if (!texture) {
        SDL_Log("Creating texture failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    SDL_Log("Initialized.");
    return 1;
}

void release() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = 0;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = 0;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = 0;
    }

    SDL_Quit();
}

void renderFrame() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderPresent(renderer);
}

void mainLoop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_Log("Event: SDL_QUIT");
            done = 1;
        }
    }

    renderFrame();
    SDL_Delay(5);
}

int main(int argc, char* argv[]) {
    if (!init()) {
        SDL_Log("Initialization failed.");
        release();
        return 1;
    }

    while (!done) {
        mainLoop();
    }

    release();
    SDL_Log("All done.");
    return 0;
}
