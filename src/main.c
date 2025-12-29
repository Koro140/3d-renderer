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
	Vector3 scalar_vec = { 5.0f, 5.0f, 5.0f };
	Vector3 translation_vec = { 0, -10.0f, 30.0f };
	Mat3x3 rotY = mat3x3_rotate_y(angle);

	Mat4x4 projection_mat = mat4x4_projection(90, 10000, 0.01);
	
	OBJ_object obj = obj_parse(ASSETS_FOLDER "teapot.obj");
	
	app_init(500, 500, "Game");
	while (!app_should_close()) {

		// Update here
		angle += 0.001f;
		rotY = mat3x3_rotate_y(angle);

		// Do rendering here:
		render_clear(BLACK);

		for (int i = 0; i < obj.face_arr.faces_count; i++) {

			Vector2 projected_triangle[3];
			for (int j = 0; j < 3; j++) {

				// Complexity to look cool
				Vector3 transformed_point = vec3_translate(
					vec3_mul_mat3(vec3_scale(obj_vertex_index(&obj, i, j), scalar_vec), rotY),
					translation_vec);

				Vector4 projected_point = vec4_mul_mat4(vec4_from_vec3(transformed_point), projection_mat);
				Vector2 ndc_point = project(vec3_from_vec4(projected_point));

				projected_triangle[j] = ndc_to_screen(ndc_point, screen_width, screen_height);
			}

			render_triangle(
				projected_triangle[0],
				projected_triangle[1],
				projected_triangle[2],
				RED
			);
		}

		render_present();
	}
	obj_free(obj);
	app_quit();
	return 0;
}
