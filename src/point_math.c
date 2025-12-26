#include "point_math.h"
#include <math.h>

Point2D ndc_to_screen(Point2D p, int screen_width, int screen_height) {
	return (Point2D){
		.x = (p.x + 1)/2 * screen_width,
		.y = (p.y + 1)/2 * screen_height
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
		.y = (p.y),
		.z = (p.x * st) + (p.z * ct)
	};
}

Point3D rotate_yz(Point3D p, float theta) {
	float st = sin(theta);
	float ct = cos(theta);
	return (Point3D) {	
		.x = (p.x),
		.y = (p.y * ct) - (p.z * st),
		.z = (p.y * st) + (p.z * ct)
	};
}

Point3D translate_z(Point3D p, float value) {
  return (Point3D){
    .x = p.x,
    .y = p.y,
    .z = p.z + value
  };
}
