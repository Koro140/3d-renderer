#include "obj_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_ARR_SIZE 60

void append_faces_arr(Face_Arr* farr, Face f) {
	if (farr->faces_count >= farr->faces_capacity)
	{
		// resize
		if (farr->faces_capacity == 0)
		{
			farr->faces_capacity = INITIAL_ARR_SIZE;
			farr->faces = malloc(sizeof(Face) * INITIAL_ARR_SIZE);
			if (farr->faces == NULL)
			{
				printf("Memory Error : can't allocate memory\n");
				exit(1);
			}
		}
		else
		{
			farr->faces_capacity *= 2;
			Face* newMem = realloc(farr->faces, sizeof(Face) * farr->faces_capacity);

			if (newMem == NULL)
			{
				printf("Memory Error : can't reallocate more memory\n");
				exit(1);
			}

			farr->faces = newMem;
		}
	}

	farr->faces[farr->faces_count] = f;
	farr->faces_count++;
}

void append_points_arr(Vertex_Arr* parr, Vector3 p) {
	if (parr->vertices_count >= parr->vertices_capacity)
	{
		// resize
		if (parr->vertices_count == 0)
		{
			parr->vertices_capacity = INITIAL_ARR_SIZE;
			parr->vertices = malloc(sizeof(Vector3) * INITIAL_ARR_SIZE);
			if (parr->vertices == NULL)
			{
				printf("Memory Error : can't allocate memory\n");
				exit(1);
			}
		}
		else
		{
			parr->vertices_capacity *= 2;
			Vector3* newMem = realloc(parr->vertices, sizeof(Vector3) * parr->vertices_capacity);

			if (newMem == NULL)
			{
				printf("Memory Error : can't reallocate more memory\n");
				exit(1);
			}

			parr->vertices = newMem;
		}
	}

	parr->vertices[parr->vertices_count] = p;
	parr->vertices_count++;
}

OBJ_object obj_parse(const char* filePath) {
	
	Face_Arr faces_arr = {
		.faces = NULL,
		.faces_capacity = 0,
		.faces_count = 0
	};

	Vertex_Arr vertices_arr = {
		.vertices = NULL,
		.vertices_capacity = 0,
		.vertices_count = 0
	};

	FILE* f = fopen(filePath, "r");

	if (f == NULL)
	{
		printf("Obj Parser Error: couldn't open file %s\n", filePath);
		return (OBJ_object) {
			.face_arr = faces_arr,
			.vertex_arr = vertices_arr
		};
	}

	char line[256];
	Vector3 vertex;
	int face[3];

	while (fgets(line, sizeof(line), f)) 
	{
		// vertex
		if (line[0] == 'v' && line[1] == ' ') 
		{ 
			sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			append_points_arr(&vertices_arr, vertex);
		}
		else if (line[0] == 'v' && line[1] == 't') { 
			//TODO: texture
		}
		else if (line[0] == 'v' && line[1] == 'n') { 
			//TODO: normal
		}
		else if (line[0] == 'f') { // face
			
			char* token = strtok(line + 2, " \n"); // skip 'f '
			Face face = {0};

			for (int i = 0; i < 3 && token; i++) 
			{
				int v = 0, vt = 0, vn = 0;

				if (sscanf(token, "%d/%d/%d", &v, &vt, &vn) == 3) {
					// v/vt/vn
				}
				else if (sscanf(token, "%d//%d", &v, &vn) == 2) {
					vt = 0; // no texture
				}
				else if (sscanf(token, "%d/%d", &v, &vt) == 2) {
					vn = 0; // no normal
				}
				else if (sscanf(token, "%d", &v) == 1) {
					vt = vn = 0; // only vertex
				}

				// TODO: Do vt, vn
				face.fi[i] = v ? v - 1 : -1;

				token = strtok(NULL, " \n");
			}
			append_faces_arr(&faces_arr, face);
		}
	}

	fclose(f);

	return (OBJ_object) {
		.face_arr = faces_arr,
		.vertex_arr = vertices_arr
	};
}

void obj_free(OBJ_object obj) {
	if (obj.face_arr.faces != NULL)
	{
		free(obj.face_arr.faces);
	}
	
	if (obj.vertex_arr.vertices != NULL)
	{
		free(obj.vertex_arr.vertices);
	}
}

Vector3 obj_vertex_index(OBJ_object* obj, int face, int point) {
	return (obj->vertex_arr.vertices[obj->face_arr.faces[face].fi[point]]);
}