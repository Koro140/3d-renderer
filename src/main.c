#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <math.h>

#include "render.h"
#include "app.h"

Point3D vertices[] = {
	{ 1, 1, 1},
	{ 1,-1, 1},
	{-1,-1, 1},
	{-1, 1, 1},

	{ 1, 1,-1},
	{ 1,-1,-1},
	{-1,-1,-1},
	{-1, 1,-1}
};

// triangles
// triangles (12 total)
int indices[][3] = {
    // front (+Z)
    {0, 1, 2},
    {2, 3, 0},

    // back (-Z)
    {4, 6, 5},
    {6, 4, 7},

    // right (+X)
    {0, 4, 5},
    {5, 1, 0},

    // left (-X)
    {3, 2, 6},
    {6, 7, 3},

    // top (+Y)
    {0, 3, 7},
    {7, 4, 0},

    // bottom (-Y)
    {1, 5, 6},
    {6, 2, 1}
};


int main(void) {


  app_init(500,500, "Game");

  const int triangles_count = sizeof(indices)/sizeof(int)/3;
  float dz = 0;

  while (!app_should_close()) {
			
    // Update here
    dz += 0.001f;
			
    // Do rendering here:
    render_clear(BLACK);

    for (int i = 0; i < triangles_count; i++) {
			
      Point2D projectedTriangle[3];

      for (int j = 0; j < 3; j++) {
	Point3D transformedPoint = translate_z(rotate_xz(rotate_yz(vertices[indices[i][j]], dz), dz),10.0f);
        Point2D projectedPoint = project(transformedPoint);
	
	projectedTriangle[j] = ndc_to_screen(projectedPoint,500,500);
      }

      render_triangle(
		      projectedTriangle[0],
		      projectedTriangle[1],
		      projectedTriangle[2],
		      RED
		      );
    }
    
    render_present();
  }
  app_quit();
  return 0;
}
