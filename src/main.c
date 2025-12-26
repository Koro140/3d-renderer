#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <math.h>
#include <SDL3/SDL.h>

#define WIDTH 500
#define HEIGHT 500

typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
}Color;

typedef struct {
	float x;
	float y;
}Point2D;

typedef struct {
	float x;
	float y;
	float z;
}Point3D;

#define RED (Color){255,0,0,255}
#define BLACK (Color){0,0,0,0}
#define BLUE (Color){0,0,255,255}

Point3D vertices[] = {
	{ 1, 1, 1},
	{ 1,-1, 1},
	{-1,-1, 1},
	{-1, 1, 1},

	{ 1, 1,-1},
	{ 1,-1,-1},
	{-1,-1,-1},
	{-1, 1,-1}
};

// triangles
// triangles (12 total)
int indices[][3] = {
    // front (+Z)
    {0, 1, 2},
    {2, 3, 0},

    // back (-Z)
    {4, 6, 5},
    {6, 4, 7},

    // right (+X)
    {0, 4, 5},
    {5, 1, 0},

    // left (-X)
    {3, 2, 6},
    {6, 7, 3},

    // top (+Y)
    {0, 3, 7},
    {7, 4, 0},

    // bottom (-Y)
    {1, 5, 6},
    {6, 2, 1}
};


SDL_Renderer* global_renderer = NULL;

void set_render_color(Color color) {
	SDL_SetRenderDrawColor(global_renderer, color.r, color.g, color.b, color.a);
}

void render_point(Point2D p) {
	const float width = 20;
	const float height = 20;
	
	set_render_color(RED);
	SDL_FRect rect = {p.x - width/2,p.y - height/2, width, height};
	
	SDL_RenderFillRect(global_renderer, &rect);
}

Point2D ndc_to_screen(Point2D p) {
	return (Point2D){
		.x = (p.x + 1)/2 * WIDTH,
		.y = (p.y + 1)/2 * HEIGHT
	};
}

Point2D project(Point3D p) {
	if (p.z == 0) {
		return (Point2D){-2,-2};
	}

	return (Point2D){
		.x = p.x / p.z,
		.y = p.y / p.z
	};
}

Point3D rotate_xz(Point3D p, float theta) {
	float st = sin(theta);
	float ct = cos(theta);
	return (Point3D) {
		.x = (p.x * ct) - (p.z * st),
		.y = p.y,
		.z = (p.x * st) + (p.z * ct)
	};
}

Point3D rotate_yz(Point3D p, float theta) {
	float st = sin(theta);
	float ct = cos(theta);
	return (Point3D) {
		.x = p.x,
		.y = (p.y * ct) - (p.z * st),
		.z = (p.y * st) + (p.z * ct)
	};
}

Point3D translate_z(Point3D p, float z) {
	return (Point3D) {
		.x = p.x,
		.y = p.y,
		.z = p.z + z
	};
}

void draw_triangle(SDL_Renderer* renderer,Point2D p0, Point2D p1, Point2D p2) {
	set_render_color(BLUE);
	SDL_RenderLine(renderer, p0.x, p0.y, p1.x, p1.y);
	SDL_RenderLine(renderer, p1.x, p1.y, p2.x, p2.y);
	SDL_RenderLine(renderer, p2.x, p2.y, p0.x, p0.y);
}

int main(void) {

	assert(sizeof(indices)/sizeof(int) % 3 == 0);
	const int triangles_count = sizeof(indices)/sizeof(int)/3;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_Window* window =  SDL_CreateWindow("Hello window", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	global_renderer = renderer;

	bool game_is_running = true;
	SDL_Event e;
	float dz = 0;
	while (game_is_running) {
	
		SDL_PollEvent(&e);
		switch(e.type) {
			case SDL_EVENT_QUIT:
				game_is_running = false;
				break;
		}
		
		// Update here
		dz += 0.001f;
		

		set_render_color(BLACK);
		SDL_RenderClear(renderer);
		
		// Do rendering here:
		for (int i = 0; i < triangles_count; i++) {
			
			Point2D projectedTriangle[3];

			for (int j = 0; j < 3; j++) {
					projectedTriangle[j] = ndc_to_screen(project(
						translate_z(rotate_yz(rotate_xz(vertices[indices[i][j]], dz), dz),dz)
					));
			}

			draw_triangle(renderer,
				projectedTriangle[0],
				projectedTriangle[1],
				projectedTriangle[2]
			);
		}

		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
