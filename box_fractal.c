/*
 * Recursive box fractal programme.
 */
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480

void fractal(SDL_Renderer *r, int x, int y, int w, int h, int order);
SDL_Renderer *init(SDL_Window *window, SDL_Renderer *rend1);
void close_all(SDL_Window *window, SDL_Renderer *renderer);

int main (void)
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if ((renderer = init(window, renderer)) == NULL) {
		printf("error: init failed.");
		goto equit;
	}

	SDL_Event e;

	while (1)
	{
		while (SDL_PollEvent(&e) != 0)
			if ((e.type == SDL_QUIT) || (e.type == SDL_KEYUP))
				goto equit;

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		fractal(renderer, WIDTH/4, HEIGHT/4, WIDTH/2, HEIGHT/2, 7);
		SDL_RenderPresent(renderer);
		SDL_Delay(64);
	}

equit:
	close_all(window, renderer);
	return 0;
}

/*
 * fractal: This is a recursive function that draws whatever depth of boxes
 * is given by the order parameter.
 */
void fractal(SDL_Renderer *renderer, int x, int y, int w, int h, int order)
{
	SDL_Rect fillRect = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

	if (order >= 0) {
		fractal(renderer, x-w/4, y-h/4, w/2, h/2, order-1);
		fractal(renderer, x+w-w/4, y+h-h/4, w/2, h/2, order-1);
		fractal(renderer, x+w-w/4, y-h/4, w/2, h/2, order-1);
		fractal(renderer, x-w/4, y+h-h/4, w/2, h/2, order-1);
		SDL_RenderFillRect(renderer, &fillRect);
	}
}

SDL_Renderer *init(SDL_Window *window, SDL_Renderer *renderer)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("%s: %s.", __func__, SDL_GetError());
		return NULL;
	}

	window = SDL_CreateWindow(
					"Box fractal",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					WIDTH, HEIGHT,
					SDL_WINDOW_SHOWN);

	if (window == NULL) {
		SDL_Log("%s: %s.", __func__, SDL_GetError());
		return NULL;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_Log("%s: %s.", __func__, SDL_GetError());
		return NULL;
	}
	return renderer;
}

void close_all(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
}

