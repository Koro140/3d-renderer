#include "point_math.h"
#include <math.h>


// Vector2 definitions
Vector2 ndc_to_screen(Vector2 v, int screen_width, int screen_height) {
	return (Vector2) {
		(v.x + 1) / 2 * screen_width,
		(v.y + 1) / 2 * screen_height
	};
}

Vector2 project(Vector3 v) {
	if (v.z == 0) {
		return (Vector2) { -2, -2 };
	}

	return (Vector2) {
		v.x / v.z,
		v.y / v.z
	};
}

// Vector3 definitions
Vector3 vec3(float v)
{
	return (Vector3) {v,v,v};
}

Vector3 vec3_from_vec4(Vector4 v) {
	return (Vector3) {v.x,v.y,v.z};
}

Vector3 vec3_translate(Vector3 v, Vector3 trans)
{
	return (Vector3) { v.x + trans.x, v.y + trans.y, v.z + trans.z };
}

Vector3 vec3_scale(Vector3 v, Vector3 scalar) {
	return (Vector3) {v.x * scalar.x,v.y * scalar.y,v.z * scalar.z};
}

Vector3 vec3_mul_mat3(Vector3 v, Mat3x3 m)
{
	Vector3 result;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;

	return result;
}


// Vector4 definitions
Vector4 vec4(float v)
{
	return (Vector4) { v, v, v, v };
}

Vector4 vec4_from_vec3(Vector3 v)
{
    return (Vector4) { v.x, v.y, v.z, 1 };
}

Vector4 vec4_translate(Vector4 v, Vector4 trans)
{
	return (Vector4) {v.x + trans.x, v.y + trans.y, v.z + trans.z, v.w + trans.w};
}

Vector4 vec4_scale(Vector4 v, Vector4 scalar) {
	return (Vector4) { v.x* scalar.x, v.y* scalar.y, v.z* scalar.z, v.w * scalar.w};
}

Vector4 vec4_mul_mat4(Vector4 v, Mat4x4 m)
{
	Vector4 result;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;

	return result;
}

// Mat3x3 definitions
Mat3x3 mat3x3_identity()
{
    Mat3x3 m = { {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    } };
    return m;
}

Mat3x3 mat3x3_scale(Vector3 s)
{
    Mat3x3 m = { {
        {s.x, 0, 0},
        {0, s.y, 0},
        {0, 0, s.z}
    } };
    return m;
}

Mat3x3 mat3x3_rotate_x(float angle)
{
    float c = cosf(angle), s = sinf(angle);
    Mat3x3 m = { {
        {1, 0, 0},
        {0, c,-s},
        {0, s, c}
    } };
    return m;
}

Mat3x3 mat3x3_rotate_y(float angle)
{
    float c = cosf(angle), s = sinf(angle);
    Mat3x3 m = { {
        { c, 0, s},
        { 0, 1, 0},
        {-s, 0, c}
    } };
    return m;
}

Mat3x3 mat3x3_rotate_z(float angle)
{
    float c = cosf(angle), s = sinf(angle);
    Mat3x3 m = { {
        {c,-s,0},
        {s, c,0},
        {0, 0,1}
    } };
    return m;
}

Mat3x3 mat3x3_mul(Mat3x3 a, Mat3x3 b)
{
    Mat3x3 r = { 0 };
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                r.m[i][j] += a.m[i][k] * b.m[k][j];
    return r;
}

// Mat4x4 definitions
Mat4x4 mat4x4_identity()
{
    Mat4x4 m = { {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    } };
    return m;
}

Mat4x4 mat4x4_projection(float fov,float f, float n) {
    const float DEG_TO_RAD = (atan(1) * 4) / 180;
    float s = 1 / tan((fov / 2) * DEG_TO_RAD);

    /*Mat4x4 m = { {
        {s,0,               0, 0},
        {0,s,               0, 0},
        {0,0,  -(f) / (f - n),-1},
        {0,0,-(f*n) / (f - n), 0}
    } };*/

    Mat4x4 m = mat4x4_identity();
    m.m[0][0] = m.m[1][1] = s;
    m.m[2][2] = -f / (f - n);
    m.m[2][3] = -1;
    m.m[3][2] = -f * n / (f - n);
    return m;
}

Mat4x4 mat4x4_translate(Vector3 t)
{
    Mat4x4 m = mat4x4_identity();
    m.m[0][3] = t.x;
    m.m[1][3] = t.y;
    m.m[2][3] = t.z;
    return m;
}

Mat4x4 mat4x4_scale(Vector3 s)
{
    Mat4x4 m = mat4x4_identity();
    m.m[0][0] = s.x;
    m.m[1][1] = s.y;
    m.m[2][2] = s.z;
    return m;
}

Mat4x4 mat4x4_rotate_x(float angle)
{
    float c = cosf(angle), s = sinf(angle);
    Mat4x4 m = mat4x4_identity();
    m.m[1][1] = c; m.m[1][2] = -s;
    m.m[2][1] = s; m.m[2][2] = c;
    return m;
}

Mat4x4 mat4x4_rotate_y(float angle)
{
    float c = cosf(angle), s = sinf(angle);
    Mat4x4 m = mat4x4_identity();
    m.m[0][0] = c;  m.m[0][2] = s;
    m.m[2][0] = -s; m.m[2][2] = c;
    return m;
}

Mat4x4 mat4x4_rotate_z(float angle)
{
    float c = cosf(angle), s = sinf(angle);
    Mat4x4 m = mat4x4_identity();
    m.m[0][0] = c;  m.m[0][1] = -s;
    m.m[1][0] = s;  m.m[1][1] = c;
    return m;
}

Mat4x4 mat4x4_mul(Mat4x4 a, Mat4x4 b)
{
    Mat4x4 r = { 0 };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                r.m[i][j] += a.m[i][k] * b.m[k][j];
    return r;
}