#include "point_math.h"

typedef struct Face {
	int fi[3];
}Face;

typedef struct {
	Vector3* vertices;
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

// Return index of current (Every face has 3 points ... for now)
Vector3 obj_vertex_index(OBJ_object* obj, int face, int point);