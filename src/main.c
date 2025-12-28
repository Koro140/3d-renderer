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
	float angle = 0;
	OBJ_object obj = obj_parse(ASSETS_FOLDER "teapot.obj");

	// Some calculations before the main loop
	Vector3 scalarVec = { 5.0f, -5.0f, 5.0f };
	Vector3 translationVec = { 0, 10.0f, 30.0f };
	Mat3x3 rotY = mat3x3_rotate_y(angle);

	app_init(500, 500, "Game");

	while (!app_should_close()) {

		// Update here
		angle += 0.001f;
		rotY = mat3x3_rotate_y(angle);

		// Do rendering here:
		render_clear(BLACK);

		for (int i = 0; i < obj.face_arr.faces_count; i++) {

			Vector2 projectedTriangle[3];
			for (int j = 0; j < 3; j++) {

				// Complexety to look cool
				Vector3 transformedPoint = vec3_translate(
					vec3_mul_mat3(vec3_scale(obj_vertex_index(&obj, i, j), scalarVec), rotY),
					translationVec);

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
