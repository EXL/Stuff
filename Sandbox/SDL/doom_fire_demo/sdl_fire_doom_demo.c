#include <SDL/SDL.h>

#include <time.h>

#include <stdint.h>
#include <stdlib.h>

#define G_SCREEN_WIDTH         (320)
#define G_SCREEN_HEIGHT        (168)
#define G_SCREEN_DEPTH         (16)
#define G_SCREEN_FPS           (27)  /* Default is ~27 FPS. */
#define G_Y_COORD_START        (440)

#define G_ATI_RGB_565(r, g, b) ((uint32_t) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b & 0xF8) >> 3))

static const uint16_t g_palette_rgb_table[] = {
	G_ATI_RGB_565(0x07, 0x07, 0x07), /*  0 */
	G_ATI_RGB_565(0x1F, 0x07, 0x07), /*  1 */
	G_ATI_RGB_565(0x2F, 0x0F, 0x07), /*  2 */
	G_ATI_RGB_565(0x47, 0x0F, 0x07), /*  3 */
	G_ATI_RGB_565(0x57, 0x17, 0x07), /*  4 */
	G_ATI_RGB_565(0x67, 0x1F, 0x07), /*  5 */
	G_ATI_RGB_565(0x77, 0x1F, 0x07), /*  6 */
	G_ATI_RGB_565(0x8F, 0x27, 0x07), /*  7 */
	G_ATI_RGB_565(0x9F, 0x2F, 0x07), /*  8 */
	G_ATI_RGB_565(0xAF, 0x3F, 0x07), /*  9 */
	G_ATI_RGB_565(0xBF, 0x47, 0x07), /* 10 */
	G_ATI_RGB_565(0xC7, 0x47, 0x07), /* 11 */
	G_ATI_RGB_565(0xDF, 0x4F, 0x07), /* 12 */
	G_ATI_RGB_565(0xDF, 0x57, 0x07), /* 13 */
	G_ATI_RGB_565(0xDF, 0x57, 0x07), /* 14 */
	G_ATI_RGB_565(0xD7, 0x5F, 0x07), /* 15 */
	G_ATI_RGB_565(0xD7, 0x5F, 0x07), /* 16 */
	G_ATI_RGB_565(0xD7, 0x67, 0x0F), /* 17 */
	G_ATI_RGB_565(0xCF, 0x6F, 0x0F), /* 18 */
	G_ATI_RGB_565(0xCF, 0x77, 0x0F), /* 19 */
	G_ATI_RGB_565(0xCF, 0x7F, 0x0F), /* 20 */
	G_ATI_RGB_565(0xCF, 0x87, 0x17), /* 21 */
	G_ATI_RGB_565(0xC7, 0x87, 0x17), /* 22 */
	G_ATI_RGB_565(0xC7, 0x8F, 0x17), /* 23 */
	G_ATI_RGB_565(0xC7, 0x97, 0x1F), /* 24 */
	G_ATI_RGB_565(0xBF, 0x9F, 0x1F), /* 25 */
	G_ATI_RGB_565(0xBF, 0x9F, 0x1F), /* 26 */
	G_ATI_RGB_565(0xBF, 0xA7, 0x27), /* 27 */
	G_ATI_RGB_565(0xBF, 0xA7, 0x27), /* 28 */
	G_ATI_RGB_565(0xBF, 0xAF, 0x2F), /* 29 */
	G_ATI_RGB_565(0xB7, 0xAF, 0x2F), /* 30 */
	G_ATI_RGB_565(0xB7, 0xB7, 0x2F), /* 31 */
	G_ATI_RGB_565(0xB7, 0xB7, 0x37), /* 32 */
	G_ATI_RGB_565(0xCF, 0xCF, 0x6F), /* 33 */
	G_ATI_RGB_565(0xDF, 0xDF, 0x9F), /* 34 */
	G_ATI_RGB_565(0xEF, 0xEF, 0xC7), /* 35 */
	G_ATI_RGB_565(0xFF, 0xFF, 0xFF)  /* 36 */
};

static int g_pixel_map_fire[G_SCREEN_WIDTH * G_SCREEN_HEIGHT];
static int g_y_coord_scrolling;

static void DrawFireDemo(SDL_Surface *surface, SDL_Surface *bmp, SDL_Surface *screen) {
	int x;
	int y;
	SDL_Rect rect;

	for (x = 0; x < G_SCREEN_WIDTH; ++x) {
		for (y = 1; y < G_SCREEN_HEIGHT; ++y) {
			const int pixel = g_pixel_map_fire[y * G_SCREEN_WIDTH + x];
			if (pixel == 0) {
				g_pixel_map_fire[(y * G_SCREEN_WIDTH + x) - G_SCREEN_WIDTH] = 0;
			} else {
				const int randIdx = rand() % 4;
				const int dst = (y * G_SCREEN_WIDTH + x) - randIdx + 1;
				g_pixel_map_fire[dst - G_SCREEN_WIDTH] = pixel - (randIdx & 1);
			}
		}
	}

	rect.x = G_SCREEN_WIDTH / 2 - bmp->w / 2;
	rect.y = g_y_coord_scrolling;
	rect.w = bmp->w;
	rect.h = bmp->h;

	SDL_FillRect(surface, NULL, 0x0000);
	SDL_BlitSurface(bmp, NULL, surface, &rect);

	for (y = 0; y < G_SCREEN_HEIGHT; ++y) {
		for (x = 0; x < G_SCREEN_WIDTH; ++x) {
			const uint16_t pixel = g_palette_rgb_table[g_pixel_map_fire[y * G_SCREEN_WIDTH + x]];
			if (pixel != G_ATI_RGB_565(0x07, 0x07, 0x07)) {
				* ((uint16_t *)((uint8_t *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel)) =
					pixel;
			}
		}
	}

	if (g_y_coord_scrolling != G_SCREEN_HEIGHT / 4) {
		g_y_coord_scrolling -= 2;
	} else {
		for(y = G_SCREEN_HEIGHT - 1; y > G_SCREEN_HEIGHT - 8; --y) {
			for(x = 0; x < G_SCREEN_WIDTH; ++x) {
				if (g_pixel_map_fire[y * G_SCREEN_WIDTH + x] > 0) {
					g_pixel_map_fire[y * G_SCREEN_WIDTH + x] -= ((rand() % 2) & 3);
				}
			}
		}
	}

	rect.x = 0;
	rect.y = 0;
	rect.w = G_SCREEN_WIDTH;
	rect.h = G_SCREEN_HEIGHT;
	SDL_BlitSurface(surface, &rect, screen, &rect);
}

static void InitFireDemo(void) {
	int i;

	for (i = 0; i < G_SCREEN_WIDTH * G_SCREEN_HEIGHT; ++i) {
		g_pixel_map_fire[i] = 0; /* 0x07, 0x07, 0x07 */
	}

	for (i = 0; i < G_SCREEN_WIDTH; ++i) {
		g_pixel_map_fire[(G_SCREEN_HEIGHT - 1) * G_SCREEN_WIDTH + i] = 36; /* 0xFF, 0xFF, 0xFF */
	}

	g_y_coord_scrolling = G_Y_COORD_START;
}

int main(int argc, char *argv[]) {
	int exit;
	SDL_Surface *screen;
	SDL_Surface *surface;
	SDL_Surface *bmp;
	SDL_Event event;

	exit = 0;

	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode(G_SCREEN_WIDTH, G_SCREEN_HEIGHT, G_SCREEN_DEPTH, SDL_HWSURFACE);
	surface = SDL_CreateRGBSurface(SDL_HWSURFACE, G_SCREEN_WIDTH, G_SCREEN_HEIGHT, G_SCREEN_DEPTH,
		0xFC00, 0x07E0, 0x001F, 0x0000); /* RGB565 */
	bmp = SDL_LoadBMP("doom_logo.bmp");

	SDL_SetColorKey(bmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));

	SDL_WM_SetCaption("Fire Effect Demo", NULL);

	InitFireDemo();

	while (!exit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
				case SDL_QUIT:
					exit = 1;
					break;
			}
		}
		DrawFireDemo(surface, bmp, screen);
		SDL_Flip(screen);
		SDL_Delay(1000 / G_SCREEN_FPS);
	}

	SDL_FreeSurface(bmp);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(screen);

	SDL_Quit();
	return 0;
}
