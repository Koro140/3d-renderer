#pragma once

#include <inttypes.h>
#include "point_math.h"

typedef struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
}Color;

#define RED (Color){255,0,0,255}
#define BLACK (Color){0,0,0,0}
#define BLUE (Color){0,0,255,255}

void render_init(void* renderer);

void render_set_color(Color color);
void render_point(Vector2 p, Color color);
void render_clear(Color color);
void render_present();
void render_triangle(Vector2 p0, Vector2 p1, Vector2 p2, Color color);
