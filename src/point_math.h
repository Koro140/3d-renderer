#pragma once

typedef struct {
	float x;
	float y;
}Point2D;

typedef struct {
	float x;
	float y;
	float z;
}Point3D;

Point2D ndc_to_screen(Point2D p, int screen_width, int screen_height);
Point2D project(Point3D p);

Point3D rotate_xz(Point3D p, float theta);
Point3D rotate_yz(Point3D p, float theta);
Point3D translate_z(Point3D p, float value);
