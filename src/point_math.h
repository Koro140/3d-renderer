#pragma once

// TODO: Add "Read Math" support (Matrices, vectors, etc....)

typedef struct Vector2{
	float x;
	float y;
}Vector2;

typedef struct Vector3{
	float x;
	float y;
	float z;
}Vector3;

typedef struct Vector4{
	float x;
	float y;
	float z;
	float w;
}Vector4;

typedef struct Mat3x3{
	float m[3][3];
}Mat3x3;

typedef struct Mat4x4{
	float m[4][4];
}Mat4x4;

// Vector2 functions
Vector2 ndc_to_screen(Vector2 p, int screen_width, int screen_height);
Vector2 project(Vector3 p);

//
// Vector3 Functions
//
Vector3 vec3(float v);
Vector3 vec3_from_vec4(Vector4 v);

Vector3 vec3_scale(Vector3 v, Vector3 scalar);
Vector3 vec3_mul_mat3(Vector3 v, Mat3x3 m);
Vector3 vec3_translate(Vector3 v, Vector3 trans);
Vector3 vec3_mul_mat3(Vector3 v, Mat3x3 mat);

//
// Vector4 functions
//
Vector4 vec4(float v);
Vector4 vec4_from_vec3(Vector3 v);

Vector4 vec4_translate(Vector4 v, Vector4 trans);
Vector4 vec4_scale(Vector4 v, Vector4 scalar);
Vector4 vec4_mul_mat4(Vector4 v, Mat4x4 m);

//
// Mat3x3 functions
//
Mat3x3 mat3x3_identity();
Mat3x3 mat3x3_scale(Vector3 s);
Mat3x3 mat3x3_rotate_x(float angle);
Mat3x3 mat3x3_rotate_y(float angle);
Mat3x3 mat3x3_rotate_z(float angle);
Mat3x3 mat3x3_mul(Mat3x3 a, Mat3x3 b);

//
// Mat4x4 functions
//
Mat4x4 mat4x4_identity();
Mat4x4 mat4x4_projection(float fov, float f, float n);
Mat4x4 mat4x4_translate(Vector3 t);
Mat4x4 mat4x4_scale(Vector3 s);
Mat4x4 mat4x4_rotate_x(float angle);
Mat4x4 mat4x4_rotate_y(float angle);
Mat4x4 mat4x4_rotate_z(float angle);
Mat4x4 mat4x4_mul(Mat4x4 a, Mat4x4 b);