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
void render_point(Point2D p, Color color);
void render_clear(Color color);
void render_present();
void render_triangle(Point2D p0, Point2D p1, Point2D p2, Color color);
