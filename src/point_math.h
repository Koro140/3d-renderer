#pragma once

// TODO: Add "Read Math" support (Matrices, vectors, etc....)

typedef struct {
	float x;
	float y;
}Vector2;

typedef struct {
	float x;
	float y;
	float z;
}Vector3;

Vector2 ndc_to_screen(Vector2 p, int screen_width, int screen_height);
Vector2 project(Vector3 p);

Vector3 rotate_xz(Vector3 p, float theta);
Vector3 rotate_yz(Vector3 p, float theta);
Vector3 translate_z(Vector3 p, float value);

Vector3 scale(Vector3 p, float value);