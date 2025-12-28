#include "point_math.h"
#include <math.h>

Vector2 ndc_to_screen(Vector2 p, int screen_width, int screen_height) {
	return (Vector2) {
		.x = (p.x + 1) / 2 * screen_width,
		.y = (p.y + 1) / 2 * screen_height
	};
}

Vector2 project(Vector3 p) {
	if (p.z == 0) {
		return (Vector2) { -2, -2 };
	}

	return (Vector2) {
		.x = p.x / p.z,
		.y = p.y / p.z
	};
}

Vector3 rotate_xz(Vector3 p, float theta) {
	float st = sin(theta);
	float ct = cos(theta);
	return (Vector3) {
		.x = (p.x * ct) - (p.z * st),
		.y = (p.y),
		.z = (p.x * st) + (p.z * ct)
	};
}

Vector3 rotate_yz(Vector3 p, float theta) {
	float st = sin(theta);
	float ct = cos(theta);
	return (Vector3) {
		.x = (p.x),
		.y = (p.y * ct) - (p.z * st),
		.z = (p.y * st) + (p.z * ct)
	};
}

Vector3 translate_z(Vector3 p, float value) {
	return (Vector3) {
		.x = p.x,
		.y = p.y,
		.z = p.z + value
	};
}

Vector3 scale(Vector3 p, float value) {
	return (Vector3) {
		.x = p.x * value,
		.y = p.y * value,
		.z = p.z * value
	};
}