/*
 * This class handles all mesh data and algorithms to build shapes
 * It is called from the SceneBuilder class where properties for the
 * shape's location are passed as well as texture data using the
 * GMesh class struct
 */

#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>


#include "ShapeBuilder.h"

using namespace std;

void ShapeBuilder::UBuildPyramid(GLMesh& mesh)
{
	// build a pyramid

	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };
	
	float h = mesh.height;
	mesh.v = {
		// Vertex Positions    // color coords					// Texture coords
		 0.0f,	h,		0.0f,	c[0],	c[1],	c[2],	c[3],	0.625f, 1.0f,		//back side
		 0.5f, -0.0f, -0.5f,	c[0],	c[1],	c[2],	c[3],	0.50f, 0.0f,
		-0.5f, -0.0f, -0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f, 0.0f,

		 0.0f,  h,		0.0f,	c[0],	c[1],	c[2],	c[3],	0.875f, 1.0f,		//left side
		-0.5f, -0.0f, -0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f, 0.0f,
		-0.5f, -0.0f,  0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f, 0.0f,

		 0.0f,  h,		0.0f,	c[0],	c[1],	c[2],	c[3],	0.125f, 1.0f,		//front
		-0.5f, -0.0f,  0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f, 0.0f,
		 0.5f, -0.0f,  0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f, 0.0f,

		 0.0f,  h,		0.0f,	c[0],	c[1],	c[2],	c[3],	0.375f, 1.0f,		//right side
		 0.5f, -0.0f,  0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f, 0.0f,
		 0.5f, -0.0f, -0.5f,	c[0],	c[1],	c[2],	c[3],	0.50f, 0.0f,

		-0.5f, -0.0f, -0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f, 1.0f,		//bottom back
		 0.5f, -0.0f, -0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f, 1.0f,
		-0.5f, -0.0f,  0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f, 1.0f,

		 0.5f, -0.0f, -0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f, 1.0f,		//bottom front
		-0.5f, -0.0f,  0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f, 1.0f,
		 0.5f, -0.0f,  0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f, 1.0f
	};
		
	UTranslator(mesh);

}
void ShapeBuilder::UBuildRainbowPyramid(GLMesh& mesh, float seed)
{
	// build a multi-colored pyramid with random colors
	// use the seed that is passed in to re-seed rand()

	// seed the srand function
	srand(seed);
	
	
	float h = mesh.height;

	// generate a random value for each color coordinate;
	// find a random value between 0.1 and 1.0
	mesh.v = {
		// Vertex Positions		// color coords																				// Texture coords
		 0.0f,	h,		0.0f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.5f, 1.0f,		//back side
		 0.5f, -0.0f, -0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f, 0.0f,
		 -0.5f, -0.0f, -0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f, 0.0f,

		 0.0f,  h,		0.0f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.5f, 1.0f,		//left side
		-0.5f, -0.0f, -0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f, 0.0f,
		-0.5f, -0.0f,  0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f, 0.0f,

		 0.0f,  h,		0.0f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.5f, 1.0f,		//front
		-0.5f, -0.0f,  0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f, 0.0f,
		 0.5f, -0.0f,  0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f, 0.0f,

		 0.0f,  h,		0.0f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.5f, 1.0f,		//right side
		 0.5f, -0.0f, -0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f, 0.0f,
		 0.5f, -0.0f,  0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f, 0.0f,

		-0.5f, -0.0f, -0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f, 0.0f,		//bottom back
		 0.5f, -0.0f, -0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f, 1.0f,
		-0.5f, -0.0f,  0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f, 0.0f,

		 0.5f, -0.0f, -0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f, 1.0f,		//bottom front
		-0.5f, -0.0f,  0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f, 0.0f,
		 0.5f, -0.0f,  0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f, 1.0f
	};

	UTranslator(mesh);
	

}

void ShapeBuilder::UBuildCube(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	mesh.v = {
		0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,	// front left
		-0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		-0.5f,	1.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	1.0f,

		0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,	// front right
		0.5f,	1.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	1.0f,
		-0.5f,	1.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	1.0f,


		0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,	// right front
		0.5f,	1.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	1.0f,
		0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,

		0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,	// right back
		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,


		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,	// back left
		-0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	0.5f,
		-0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,	// back right
		0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,
		-0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,


		-0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f,	0.5f,	// left back
		-0.5f,	1.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f,	1.0f,
		-0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	1.0f,	0.5f,	// left front
		-0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	0.5f,
		-0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,




		-0.5f,	1.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.0f,	// top left
		-0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	1.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,

		-0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,	// top right
		0.5f,	1.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,
		0.5f,	1.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,

		-0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.0f,	// bottom left
		-0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,

		-0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,	// bottom right
		0.5f,	0.0f,	0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,
		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,




	};

	UTranslator(mesh);
}
void ShapeBuilder::UBuildRainbowCube(GLMesh& mesh, float seed)
{
	srand(seed);

	mesh.v = {
		0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,	// front left
		-0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	0.0f,
		-0.5f,	1.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,

		0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,	// front right
		0.5f,	1.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	1.0f,
		-0.5f,	1.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,

		0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	0.0f,	// right front
		0.5f,	1.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,
		0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	1.0f,

		0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	0.0f,	// right back
		0.5f,	0.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,
		0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	1.0f,

		-0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,	// left front
		-0.5f,	1.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	1.0f,
		-0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,

		-0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,	// left back
		-0.5f,	0.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	0.0f,
		-0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,

		0.5f,	0.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,	// front left
		-0.5f,	0.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	0.0f,
		-0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,

		0.5f,	0.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,	// front right
		0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	1.0f,
		-0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,

		-0.5f,	1.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	0.0f,	// top left
		-0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,
		0.5f,	1.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,

		-0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,	// top right
		0.5f,	1.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,
		0.5f,	1.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	1.0f,

		-0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	0.0f,	// bottom left
		-0.5f,	0.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,
		0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,

		-0.5f,	0.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	0.0f,	1.0f,	// bottom right
		0.5f,	0.0f,	0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	0.0f,
		0.5f,	0.0f,	-0.5f,	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	1.0f,	1.0f,	1.0f,




	};

	UTranslator(mesh);
}

void ShapeBuilder::UBuildCone(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;
	const float textStep = 1.0f / s;
	float textureXLoc = 0.0f;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++) {

		
		// triangle fan, bottom
		v.insert(v.end(), {0.0f, 0.0f, 0.0f, c[0], c[1], c[2], c[3], 0.5f, 0.5f});		// center point; x, y, z, r, g, b, a, texture x, texture y
		v.insert(v.end(), { r * cos(i * sectorStep) , 
										r * sin(i * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],
										/*textureXLoc,
										0.0f*/
										0.5f + (r * cos((i)*sectorStep)) ,	// texture x; adding the origin for proper alignment
										0.5f + (r * sin((i)*sectorStep))
										});										// first outer point
		v.insert(v.end(), { r * cos((i + 1) * sectorStep) , 
										r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],
										/*textureXLoc + textStep,
										0.0f*/
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.5f + (r * sin((i + 1) * sectorStep))
										});								// second outer point
		
		// side triangle + point
		v.insert(v.end(), { r * cos(i * sectorStep) , 
										r * sin(i * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],
										textureXLoc ,
										0.0f});
		v.insert(v.end(), { r * cos((i + 1) * sectorStep) , 
										r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],
										textureXLoc + textStep,
										0.0f	});
		v.insert(v.end(), {0.0f , 0.0f , l , c[0], c[1], c[2], c[3], textureXLoc + (textStep / 2), 1.0f});		// origin, peak

		textureXLoc += textStep;
		
	}

	mesh.v = v;
	v.clear();	// clear the local vector
	
	UTranslator(mesh);
}
void ShapeBuilder::UBuildRainbowCone(GLMesh& mesh, float seed)
{
	srand(seed);

	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;
	const float textStep = 1.0f / s;
	float textureXLoc = 0.0f;



	vector<float> c;
	c.insert(c.end(), { ((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f) });


	vector<float> v;

	for (auto i = 1; i < s + 1; i++) {


		// triangle fan, bottom
		// center point
		v.insert(v.end(), { 0.5f,	0.5f,	0.0f,	0.3f,	0.7f,	1.0f,	1.0f,	0.5f,	0.5f });

		// first outer point
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										0.0f ,
										// generate random colors for vertex
										c[0],	c[1],	c[2],	1.0f,
										0.5f + (r * cos((i)*sectorStep)) ,
										0.5f + (r * sin((i)*sectorStep))
										});

		// second outer point
		c.clear();
		c.insert(c.end(), { ((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0],	c[1],	c[2], 1.0f,
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.5f + (r * sin((i + 1) * sectorStep))
			});

	}

	for (auto i = 1; i < s + 1; i++)
	{

		// side triangle + point
		// center of bottom
		v.insert(v.end(), { 0.5f,	0.5f,	l,	0.3f,	0.7f,	1.0f,	1.0f,	0.5f,	1.0f });		// origin, peak

		// outer point
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										0.0f ,
										c[0],	c[1],	c[2],	1.0f,
										textureXLoc ,
										0.0f });
		c.clear();
		c.insert(c.end(), { ((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f) });
		// outer point
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0],	c[1],	c[2],	1.0f,
										textureXLoc + textStep,
										0.0f });

		textureXLoc += textStep;

	}


	mesh.v = v;
	v.clear();	// clear the local vector
	c.clear();	// clear color vector

	UTranslator(mesh);
}

void ShapeBuilder::UBuildCylinder(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };
	
	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;
	float h = mesh.height;
	

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan, bottom
		v.insert(v.end(), { 0.5f, 0.5f, 0.0f, c[0],	c[1], c[2],	c[3], 0.5f, 0.5f });			// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,			// x
										0.5f + r * sin(i * sectorStep) ,			// y
										0.0f ,										// z
										c[0], c[1], c[2], c[3],					// color data r g b a
										0.5f + (r * cos((i)*sectorStep)) ,		// texture x; adding the origin for proper alignment
										0.5f + (r * sin((i)*sectorStep))  });	// texture y
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.5f + (r * sin((i + 1) * sectorStep))  });
	}

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan, top
		v.insert(v.end(), { 0.5f, 0.5f, l, c[0], c[1], c[2], c[3], 0.5f, 0.5f });			// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) , 
										0.5f + r * sin(i * sectorStep) ,
										l ,										// build this fan the 'l' value away from the other fan
										c[0], c[1], c[2], c[3],					// color data r g b a
										0.5f + (r * cos((i)*sectorStep)) ,
										0.5f + (r * sin((i)*sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 
										0.5f + r * sin((i + 1) * sectorStep) ,
										l ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.5f + (r * sin((i + 1) * sectorStep)) });
	}

	// since all side triangles have the same points as the fans above, the same calculations are used
	// to wrap the texture around the cylinder, the calculated points are used to determine which section of
	// the texture to clamp to the corresponding point.
	constexpr float x = 3.0f;
	float j = 1.0f / (s / x);	// for calculating texture location; change 'x' to increase or decrease how many times the texture wraps around the cylinder
	float k = 0.0f;				// for texture clamping

	// sides
	for (auto i = 1; i < s + 1; i++)
	{
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) , 
										0.5f + r * sin(i * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k ,
										0 });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) , 
										0.5f + r * sin(i * sectorStep) ,
										l ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k ,
										1.0f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 
										0.5f + r * sin((i + 1) * sectorStep) ,
										l ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k + j ,
										1.0f });

		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 
										0.5f + r * sin((i + 1) * sectorStep) ,
										l ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k + j ,
										1.0f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k + j ,
										0.0f });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) , 
										0.5f + r * sin(i * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k,
										0.0f });
		k += j;
	}

	mesh.v = v;
	v.clear();
	UTranslator(mesh);
	
}
void ShapeBuilder::UBuildRainbowCylinder(GLMesh& mesh, float seed)
{
	srand(seed);
	vector<float> c;
	c.insert(c.end(), { ((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f) });


	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;
	float h = mesh.height;


	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan, bottom
		v.insert(v.end(), { 0.5f, 0.5f, 0.0f, c[0],	c[1], c[2],	1.0f, 0.5f, 0.5f });			// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,			// x
										0.5f + r * sin(i * sectorStep) ,			// y
										0.0f ,										// z
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										0.5f + (r * cos((i)*sectorStep)) ,		// texture x; adding the origin for proper alignment
										0.5f + (r * sin((i)*sectorStep)) });	// texture y

		c.clear();
		c.insert(c.end(), { ((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f) });

		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.5f + (r * sin((i + 1) * sectorStep)) });
	}

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan, top
		v.insert(v.end(), { 0.5f, 0.5f, l, c[0], c[1], c[2], 1.0f, 0.5f, 0.5f });			// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										l ,										// build this fan the 'l' value away from the other fan
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										0.5f + (r * cos((i)*sectorStep)) ,
										0.5f + (r * sin((i)*sectorStep)) });

		c.clear();
		c.insert(c.end(), { ((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										l ,
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.5f + (r * sin((i + 1) * sectorStep)) });
	}

	// since all side triangles have the same points as the fans above, the same calculations are used
	// to wrap the texture around the cylinder, the calculated points are used to determine which section of
	// the texture to clamp to the corresponding point.
	constexpr float x = 3.0f;
	float j = 1.0f / (s / x);	// for calculating texture location; change 'x' to increase or decrease how many times the texture wraps around the cylinder
	float k = 0.0f;				// for texture clamping

	// sides
	for (auto i = 1; i < s + 1; i++)
	{
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										k ,
										0 });
		c.clear();
		c.insert(c.end(), { ((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f) });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										l ,
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										k ,
										1.0f });


		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										l ,
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										k + j ,
										1.0f });

		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										l ,
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										k + j ,
										1.0f });
		c.clear();
		c.insert(c.end(), { ((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f),	((rand() % 10 + 1) * 0.1f) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										k + j ,
										0.0f });


		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], 1.0f,					// color data r g b a
										k,
										0.0f });
		k += j;
	}

	mesh.v = v;
	v.clear();
	UTranslator(mesh);

}

void ShapeBuilder::UBuildPlane(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	mesh.v = {
		-1.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.0f, 1.0f,	// 0
		 0.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 0.5f, 0.0f,	// 1
		-1.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 0.0f, 0.0f,	// 2

		-1.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.0f, 1.0f,	// 0
		 0.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 0.5f, 0.0f,	// 2
		 0.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.5f, 1.0f,	// 3

		 0.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.5f, 1.0f,	// 3
		 0.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 0.5f, 0.0f,	// 2
		 1.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 1.0f, 0.0f,	// 5

		 0.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.5f, 1.0f,	// 3
		 1.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 1.0f, 0.0f,	// 5
		 1.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 1.0f, 1.0f,	// 4

	};
	
	UTranslator(mesh);
	
}

void ShapeBuilder::UBuildCircle(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };


	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;
	float h = mesh.height;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan
		v.insert(v.end(), { 0.5f, 0.5f, 0.0f, c[0],	c[1], c[2],	c[3], 0.5f, 0.5f });		// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,		// x
										0.5f + r * sin(i * sectorStep) ,		// y
										0.0f ,									// z
										c[0],	c[1], c[2],	c[3],				// color data r g b a
										0.5f + (r * cos((i)*sectorStep)) ,	// texture x; adding the origin for proper alignment
										0.5f + (r * sin((i)*sectorStep)) });	// texture y
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0],	c[1], c[2],	c[3],				// color data r g b a
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.5f + (r * sin((i + 1) * sectorStep)) });
	}
	mesh.v = v;
	v.clear();
	UTranslator(mesh);
}




void ShapeBuilder::UTranslator(GLMesh& mesh)
{
	// build the mesh

	constexpr GLuint floatsPerVertex = 3;
	constexpr GLuint floatsPerColor = 4;
	constexpr GLuint floatsPerUV = 2;

	mesh.nIndices = mesh.v.size() / (floatsPerVertex + floatsPerUV + floatsPerColor);

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	// Create VBO
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer

	// use vector instead of array
	glBufferData(
		GL_ARRAY_BUFFER,
		mesh.v.size() * sizeof(float),
		&mesh.v.front(),
		GL_STATIC_DRAW
	); // Sends vertex or coordinate data to the GPU

	// Strides between vertex coordinates
	constexpr GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV + floatsPerColor);

	// Create Vertex Attribute Pointers
	// location
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture
	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);



	// scale the object
	mesh.scale = glm::scale(glm::vec3(mesh.p[4], mesh.p[5], mesh.p[6]));

	const glm::mat4 rot = glm::mat4(1.0f);

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.xrotation = glm::rotate(rot, glm::radians(mesh.p[7]), glm::vec3(mesh.p[8], mesh.p[9], mesh.p[10]));
	mesh.yrotation = glm::rotate(rot, glm::radians(mesh.p[11]), glm::vec3(mesh.p[12], mesh.p[13], mesh.p[14]));
	mesh.zrotation = glm::rotate(rot, glm::radians(mesh.p[15]), glm::vec3(mesh.p[16], mesh.p[17], mesh.p[18]));


	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(mesh.p[19], mesh.p[20], mesh.p[21]));

	mesh.model = mesh.translation * mesh.xrotation * mesh.zrotation * mesh.yrotation * mesh.scale;

	//mesh.gUVScale = glm::vec2(mesh.p[22], mesh.p[23]);		// scales the texture
	mesh.gUVScale = glm::vec2(2.0f, 2.0f);		// scales the texture

}

