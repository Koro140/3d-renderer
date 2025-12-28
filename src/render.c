#include "render.h"
#include <SDL3/SDL.h>

static SDL_Renderer* global_renderer = NULL;

void render_init(void* renderer) {
	global_renderer = (SDL_Renderer*)renderer;
}

void render_set_color(Color color) {
	SDL_SetRenderDrawColor(global_renderer, color.r, color.g, color.b, color.a);
}

void render_clear(Color color) {
	render_set_color(color);
	SDL_RenderClear(global_renderer);
}

void render_point(Vector2 p, Color color) {
	const float width = 10;
	const float height = 10;

	render_set_color(color);
	SDL_FRect rect = { p.x - width / 2,p.y - height / 2, width, height };

	SDL_RenderFillRect(global_renderer, &rect);
}

void render_triangle(Vector2 p0, Vector2 p1, Vector2 p2, Color color) {
	render_set_color(color);
	SDL_RenderLine(global_renderer, p0.x, p0.y, p1.x, p1.y);
	SDL_RenderLine(global_renderer, p1.x, p1.y, p2.x, p2.y);
	SDL_RenderLine(global_renderer, p2.x, p2.y, p0.x, p0.y);
}

void render_present() {
	SDL_RenderPresent(global_renderer);
}
