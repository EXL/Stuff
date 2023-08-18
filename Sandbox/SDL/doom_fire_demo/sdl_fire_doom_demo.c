#include <SDL/SDL.h>

#include <time.h>

#include <stdint.h>
#include <stdlib.h>

#define SCREEN_WIDTH         (320)
#define SCREEN_HEIGHT        (168)
#define SCREEN_DEPTH         (16)
#define SCREEN_FPS           (27)  /* Default is ~27 FPS. */
#define Y_COORD_START        (440)

typedef struct {
	SDL_Surface *screen;
	SDL_Surface *surface;
	SDL_Surface *bmp;

	uint8_t *pixels;
	int y_coord;
} FireDemo_t;

static const SDL_Color fire_palette[] = {
	{ 0x07, 0x07, 0x07 }, /*  0 */
	{ 0x1F, 0x07, 0x07 }, /*  1 */
	{ 0x2F, 0x0F, 0x07 }, /*  2 */
	{ 0x47, 0x0F, 0x07 }, /*  3 */
	{ 0x57, 0x17, 0x07 }, /*  4 */
	{ 0x67, 0x1F, 0x07 }, /*  5 */
	{ 0x77, 0x1F, 0x07 }, /*  6 */
	{ 0x8F, 0x27, 0x07 }, /*  7 */
	{ 0x9F, 0x2F, 0x07 }, /*  8 */
	{ 0xAF, 0x3F, 0x07 }, /*  9 */
	{ 0xBF, 0x47, 0x07 }, /* 10 */
	{ 0xC7, 0x47, 0x07 }, /* 11 */
	{ 0xDF, 0x4F, 0x07 }, /* 12 */
	{ 0xDF, 0x57, 0x07 }, /* 13 */
	{ 0xDF, 0x57, 0x07 }, /* 14 */
	{ 0xD7, 0x5F, 0x07 }, /* 15 */
	{ 0xD7, 0x5F, 0x07 }, /* 16 */
	{ 0xD7, 0x67, 0x0F }, /* 17 */
	{ 0xCF, 0x6F, 0x0F }, /* 18 */
	{ 0xCF, 0x77, 0x0F }, /* 19 */
	{ 0xCF, 0x7F, 0x0F }, /* 20 */
	{ 0xCF, 0x87, 0x17 }, /* 21 */
	{ 0xC7, 0x87, 0x17 }, /* 22 */
	{ 0xC7, 0x8F, 0x17 }, /* 23 */
	{ 0xC7, 0x97, 0x1F }, /* 24 */
	{ 0xBF, 0x9F, 0x1F }, /* 25 */
	{ 0xBF, 0x9F, 0x1F }, /* 26 */
	{ 0xBF, 0xA7, 0x27 }, /* 27 */
	{ 0xBF, 0xA7, 0x27 }, /* 28 */
	{ 0xBF, 0xAF, 0x2F }, /* 29 */
	{ 0xB7, 0xAF, 0x2F }, /* 30 */
	{ 0xB7, 0xB7, 0x2F }, /* 31 */
	{ 0xB7, 0xB7, 0x37 }, /* 32 */
	{ 0xCF, 0xCF, 0x6F }, /* 33 */
	{ 0xDF, 0xDF, 0x9F }, /* 34 */
	{ 0xEF, 0xEF, 0xC7 }, /* 35 */
	{ 0xFF, 0xFF, 0xFF }  /* 36 */
};

static void InitFireDemo(FireDemo_t *fire) {
	fire->y_coord = Y_COORD_START;
	fire->pixels = (uint8_t *) fire->surface->pixels;

	/* Fill all screen to RGB(0x07, 0x07, 0x07) except last line. */
	memset(fire->pixels, 0, SCREEN_WIDTH * (SCREEN_HEIGHT - 1));

	/* Fill last line to RGB(0xFF, 0xFF, 0xFF) except last line. */
	memset(fire->pixels + (SCREEN_HEIGHT - 1) * SCREEN_WIDTH, 36, SCREEN_WIDTH);
}

static void DrawFireDemo(FireDemo_t *fire) {
	int x;
	int y;
	SDL_Rect bmp_rect = { SCREEN_WIDTH / 2 - fire->bmp->w / 2, fire->y_coord, fire->bmp->w, fire->bmp->h };

	for (x = 0; x < SCREEN_WIDTH; ++x) {
		for (y = 1; y < SCREEN_HEIGHT; ++y) {
			const uint8_t pixel = fire->pixels[y * SCREEN_WIDTH + x];
			if (pixel == 0) {
				fire->pixels[(y * SCREEN_WIDTH + x) - SCREEN_WIDTH] = 0;
			} else {
				const uint8_t rand_idx = rand() % 4;
				const int destination = (y * SCREEN_WIDTH + x) - rand_idx + 1;
				fire->pixels[destination - SCREEN_WIDTH] = pixel - (rand_idx & 1);
			}
		}
	}

	if (fire->y_coord != SCREEN_HEIGHT / 4) {
		fire->y_coord -= 2;
	} else {
		for(y = SCREEN_HEIGHT - 1; y > SCREEN_HEIGHT - 8; --y) {
			for(x = 0; x < SCREEN_WIDTH; ++x) {
				if (fire->pixels[y * SCREEN_WIDTH + x] > 0) {
					fire->pixels[y * SCREEN_WIDTH + x] -= ((rand() % 2) & 3);
				}
			}
		}
	}

	SDL_FillRect(fire->screen, NULL, 0);
	SDL_BlitSurface(fire->bmp, NULL, fire->screen, &bmp_rect);
	SDL_BlitSurface(fire->surface, NULL, fire->screen, NULL);
}

int main(int argc, char *argv[]) {
	int exit;
	FireDemo_t fire;
	SDL_Event event;

	exit = 0;

	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);

	fire.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_HWSURFACE);

	fire.surface = SDL_CreateRGBSurface(SDL_HWPALETTE, SCREEN_WIDTH, SCREEN_HEIGHT, 8, 0x00, 0x00, 0x00, 0x00);
	SDL_SetPalette(fire.surface, SDL_LOGPAL | SDL_PHYSPAL, (SDL_Color *) fire_palette, 0, sizeof(fire_palette));
	SDL_SetColorKey(fire.surface, SDL_SRCCOLORKEY, 0);

	fire.bmp = SDL_LoadBMP("doom_logo.bmp");
	SDL_SetColorKey(fire.bmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(fire.bmp->format, 0xFF, 0xFF, 0xFF));

	SDL_WM_SetCaption("Fire Effect Demo", NULL);

	InitFireDemo(&fire);

	while (!exit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
				case SDL_QUIT:
					exit = 1;
					break;
			}
		}
		DrawFireDemo(&fire);
		SDL_Flip(fire.screen);
		SDL_Delay(1000 / SCREEN_FPS);
	}

	SDL_FreeSurface(fire.bmp);
	SDL_FreeSurface(fire.surface);
	SDL_FreeSurface(fire.screen);

	SDL_Quit();
	return 0;
}
