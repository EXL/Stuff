#include <SDL2/SDL.h>

#include <time.h>

static struct timeval start_tv;

int main() {

    gettimeofday(&start_tv, NULL);

    while (1) {
        struct timeval now;

        gettimeofday(&now, NULL);

        //printf("%u\n", SDL_GetTicks());
        printf("%u\n", (unsigned) ((now.tv_sec - start_tv.tv_sec) * 1000 + (now.tv_usec - start_tv.tv_usec) / 1000));

        usleep(50000);
    }
    return 0;
}
