#include "SceneBuilder.h"
#include "ShapeBuilder.h"
#include "Mesh.h"

using namespace std;

void SceneBuilder::UBuildScene(vector<GLMesh>& scene)
{
	float height;
	float length;
	float radius;
	float number_of_sides;
	vector<float> properties;


	// SHAPE 1: PYRAMID
	GLMesh gMesh01;
	properties = {
		0.5f, 0.0f, 0.8f, 1.0f,				// color r, g, b a	
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
	height = 1.7f;
	gMesh01.texFilename = "bricks.png";
	ShapeBuilder::UBuildPyramid(gMesh01, properties, height);
	scene.push_back(gMesh01);
		

	// SHAPE 2: CONE
	GLMesh gMesh02;
	properties = {
		0.0f,	0.0f,	0.0f,	1.0f,		// color r, g, b, a
		1.0f,	1.0f,	1.0f,				// scale x, y z
		270.0f,	1.0f,	0.0f,	0.0f,		// x amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		0.0f,	0.0f,	1.0f,	0.0f,		// y amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		0.0f,	0.0f,	0.0f,	1.0f,		// z amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		2.0f,	0.0f,	0.0f,				// translate x, y, z
		1.0f,	1.0f						// texture scaling
	};
	radius = 1.0f;
	length = 1.7f;
	number_of_sides = 12.0f;
	gMesh02.texFilename = "pyramid_tex.jpg";
	ShapeBuilder::UBuildCone(gMesh02, properties, radius, length, number_of_sides);
	scene.push_back(gMesh02);


	// SHAPE 3: Triangle Trial
	GLMesh gMesh03;
	properties = {
		0.5f, 0.0f, 0.8f, 1.0f,				// color r, g, b a	
		1.0f, 2.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-2.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
	radius = 1.0;
	height = 1.7f;
	gMesh03.texFilename = "angelina.png";
	ShapeBuilder::UBuildTriangles(gMesh03, properties);
	scene.push_back(gMesh03);



}

