#include "point_math.h"

typedef struct Face {
	int fi[3];
}Face;

typedef struct {
	Point3D* vertices;
	int vertices_count;
	int vertices_capacity;
}Vertex_Arr;

typedef struct {
	Face* faces;
	int faces_count;
	int faces_capacity;
}Face_Arr;

typedef struct {
	Vertex_Arr vertex_arr;
	Face_Arr face_arr;
}OBJ_object;

OBJ_object obj_parse(const char* filePath);
void obj_free(OBJ_object obj);