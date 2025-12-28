#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <math.h>

#include "render.h"
#include "app.h"
#include "obj_parser.h"

int main(void) {
	const int screen_width = 500;
	const int screen_height = 500;
	float dz = 0;
	OBJ_object obj = obj_parse(ASSETS_FOLDER "teapot.obj");
	
	app_init(500, 500, "Game");
	while (!app_should_close()) {

		// Update here
		dz += 0.001f;

		// Do rendering here:
		render_clear(BLACK);

		for (int i = 0; i < obj.face_arr.faces_count; i++) {

			Vector2 projectedTriangle[3];
			for (int j = 0; j < 3; j++) {
				Vector3 transformedPoint = translate_z(rotate_yz(rotate_xz(rotate_yz(scale(*obj_vertex_index(&obj, i,j), 5.0f), dz), dz), -1), 30.0f);
				Vector2 projectedPoint = project(transformedPoint);

				projectedTriangle[j] = ndc_to_screen(projectedPoint, screen_width, screen_height);
			}

			render_triangle(
				projectedTriangle[0],
				projectedTriangle[1],
				projectedTriangle[2],
				RED
			);
		}

		render_present();
	}
	obj_free(obj);
	app_quit();
	return 0;
}
