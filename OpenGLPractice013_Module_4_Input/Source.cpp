//---------------------------------------------------
//
// Lawrence Artl
// CS-330 Comp Graphic and Viz
// Assignment 5-3
//
// TEXTURE A PYRAMID
//
//---------------------------------------------------


#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <camera.h>

// shader program macros
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif


using namespace std;

//window title
const char* const WINDOW_TITLE = "Module 3 Assignment: 3D Scene";

//window width, height
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//GL data for mesh
struct GLMesh
{
	//vertex array
	GLuint vao;
	//vertex buffer
	GLuint vbos[2];
	//indices of the mesh
	GLuint nIndices;

	

	

	glm::mat4 scale;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 model;

	
	
};

//main window
GLFWwindow* gWindow = nullptr;
//triangle mesh data
//GLMesh gMesh;
GLMesh pMesh;
GLMesh bMesh;
//shader program
GLuint gShaderProgram;

// scene vector for drawing shapes
vector<GLMesh> scene;

bool perspective = false;


// camera
Camera gCamera(glm::vec3(0.0f, 1.5f, 5.0f));
float gLastX = WINDOW_WIDTH / 2.0f;
float gLastY = WINDOW_HEIGHT / 2.0f;
bool gFirstMouse = true;


// timing
float gDeltaTime = 0.0f; // time between current frame and last frame
float gLastFrame = 0.0f;



//initialize program
bool UInitialize(int, char* [], GLFWwindow** window);
//set window size
void UResizeWindow(GLFWwindow* window, int width, int height);
//process user input
void UProcessInput(GLFWwindow* window);
//render graphics
void URender(vector<GLMesh> scene);
//compile shaders
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource,
	GLuint& programId);
//free up memory on close
void UDestroyMesh(GLMesh& mesh);
void UDestroyShaderProgram(GLuint programId);

// build shapes
void UBuildPyramid(GLMesh& mesh, vector<float> properties);
void UBuildCylinder(GLMesh& mesh, vector<float> properties, float radius, float length);
void UBuildCone(GLMesh& mesh, vector<float> properties, float radius, float length);
void UBuildPlane(GLMesh& mesh, vector<float> properties);


// keyboard and mouse input functions
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);


// Vertex Shader Source Code
const GLchar* vertex_shader_source = GLSL(440,
	layout(location = 0) in vec3 position; // Vertex data from Vertex Attrib Pointer 0
	layout(location = 1) in vec4 color;  // Color data from Vertex Attrib Pointer 1

	out vec4 vertexColor; // variable to transfer color data to the fragment shader

	//uniform mat4 shaderTransform; // 4x4 matrix variable for transforming vertex data
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main()
	{
		gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertex data using matrix
		vertexColor = color; // references incoming color data
	}
);

// Fragment Shader Source Code
const GLchar* fragment_shader_source = GLSL(440,
	in vec4 vertexColor; // Variable to hold incoming color data from vertex shader

	out vec4 fragmentColor;

	void main()
	{
		fragmentColor = vec4(vertexColor);
	}
);



//main
int main(int argc, char* argv[])
{
	//check if initialized correctly
	if (!UInitialize(argc, argv, &gWindow))
		return EXIT_FAILURE;

	//create mesh, create vbo

	
	// build shape meshes
	// build purple pyramid
	GLMesh gMesh01;
	vector<float> properties = {
		 0.5f,  0.0f,  0.8f,  1.0f,
		 2.0f,  2.0f,  2.0f,
		 0.8f,  0.0f,  1.0f,  0.0f,
		-0.5f,  1.0f,  -2.0
	};
	UBuildPyramid(gMesh01, properties);
	scene.push_back(gMesh01);

	// build aqua pyramid
	GLMesh gMesh02;
	properties.clear();
	properties = {
		 0.0f,  1.0f,  1.0f,  1.0f,		// color
		 1.5f,  1.5f,  1.5f,			// scale
		 0.8f,  0.0f,  1.0f,  0.0f,		// angle - x, y, z axis rotate
		 -2.5f,  0.75f,  -1.0				// translate x, y, z axis
	};
	UBuildPyramid(gMesh02, properties);
	scene.push_back(gMesh02);

	// build pink cylinder
	GLMesh gMesh03;
	properties.clear();
	properties = {
		  1.0f,  0.0f,  1.0f,  1.0f,		// color
		  1.0f,  1.0f,  1.0f,			// scale
		  -1.6f,  0.0f,  1.0f,  0.0f,		// angle - x, y, z axis rotate
		  -1.4f,  0.4f,  2.0				// translate x, y, z axis
	};
	UBuildCylinder(gMesh03, properties, 0.4f, 6.0f);
	scene.push_back(gMesh03);

	// build pink cone to top of cylinder
	GLMesh gMesh04;
	properties.clear();
	properties = {
		  1.0f,  0.2f,  1.0f,  1.0f,		// color
		  1.0f,  1.0f,  1.0f,			// scale
		  -4.8f,  0.0f,  1.0f,  0.0f,		// angle - x, y, z axis rotate
		  -1.4f,  0.4f,  2.0				// translate x, y, z axis
	};
	UBuildCone(gMesh04, properties, 0.4f, 1.0f);
	scene.push_back(gMesh04);

	// build plane for objects
	GLMesh gMesh05;
	properties.clear();
	properties = {
		 0.2f,  0.6f,  0.2f,  1.0f,		// color
		 1.0f,  1.0f,  1.0f,			// scale
		 0.0f,  0.0f,  1.0f,  0.0f,		// angle - x, y, z axis rotate
		 0.0f,  0.0f,  0.0				// translate x, y, z axis
	};
	UBuildPlane(gMesh05, properties);
	scene.push_back(gMesh05);

	// build green cone to top of cylinder
	GLMesh gMesh06;
	properties.clear();
	properties = {
		  0.1f,  1.0f,  0.4f,  1.0f,		// color
		  1.0f,  1.0f,  1.0f,			// scale
		  1.6f,  1.0f,  0.0f,  0.0f,		// angle - x, y, z axis rotate
		  2.3f,  0.0f,  -1.6				// translate x, y, z axis
	};
	UBuildCone(gMesh06, properties, 0.7f, 2.8f);
	scene.push_back(gMesh06);


	//build shader programs
	if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source,
		gShaderProgram))
		return EXIT_FAILURE;

	//bg color of window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//rendering loop
	//keep checking if window has closed
	while (!glfwWindowShouldClose(gWindow))
	{
		float currentFrame = glfwGetTime();
		gDeltaTime = currentFrame - gLastFrame;
		gLastFrame = currentFrame;



		//process user input
		UProcessInput(gWindow);

		//render frame
		URender(scene);

		glfwPollEvents();
	}


	//clean up
	scene.clear();
	properties.clear();

	UDestroyMesh(gMesh01);
	UDestroyMesh(gMesh02);
	UDestroyMesh(gMesh03);
	UDestroyMesh(gMesh04);


	

	UDestroyShaderProgram(gShaderProgram);

	//exit with success!
	exit(EXIT_SUCCESS);

}


// functions
// initialize and build shaders
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
	//initialize GLFW, GLEW, create window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	//use constants for vars
	*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	//window fails to be created
	if (*window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, UResizeWindow);
	glfwSetCursorPosCallback(*window, UMousePositionCallback);
	glfwSetScrollCallback(*window, UMouseScrollCallback);
	glfwSetMouseButtonCallback(*window, UMouseButtonCallback);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult)
	{
		std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}

	return true;
}
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
	//error reporting
	int success = 0;
	char infoLog[512];

	//create shader program object
	programId = glCreateProgram();

	//create vertex and frag shader obj
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	//get shader source
	glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
	glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

	//compile vertex shader
	glCompileShader(vertexShaderId);

	//check for errors
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	//compile frag shader
	glCompileShader(fragmentShaderId);

	//check for errors
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	//shaders compiled, attach to shader program object from above
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	//link the program object
	glLinkProgram(programId);

	//check for linking errors
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		return false;
	}

	glUseProgram(programId);

	return true;
}

// process user input and windows changes
void UProcessInput(GLFWwindow* window)
{
	

	// exit program
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// draw lines
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// fill shapes
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		gCamera.ProcessKeyboard(LEFT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		gCamera.ProcessKeyboard(UP, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		gCamera.ProcessKeyboard(DOWN, gDeltaTime);


	// I originally had this as a single key (P) toggle, but the key press registers
	// so quickly that it took several presses to get it to land on the desired output
	// separating the statement allowed me to toggle when I wanted
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		perspective = false;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		perspective = true;

	// original statement below 
	/*if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		if (!perspective)
		{
			perspective = true;
		}
		else
			perspective = false;
	}*/



	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		if (gCamera.MovementSpeed < 10.0f)
		{
			gCamera.MovementSpeed += 0.01f;
		}
		else
			gCamera.MovementSpeed = 10.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		if (gCamera.MovementSpeed > 0.01f)
		{
			gCamera.MovementSpeed -= 0.01f;
		}
		else
			gCamera.MovementSpeed = 0.01f;
	}
		
}
void UResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (gFirstMouse)
	{
		gLastX = xpos;
		gLastY = ypos;
		gFirstMouse = false;
	}

	float xoffset = xpos - gLastX;
	float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

	gLastX = xpos;
	gLastY = ypos;

	gCamera.ProcessMouseMovement(xoffset, yoffset);
}
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	//gCamera.ProcessMouseScroll(gCamera.MovementSpeed);

	//gCamera.ProcessMouseScroll(gDeltaTime--);
	
	gCamera.ProcessMouseScroll(gCamera.MovementSpeed);
}
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		if (action == GLFW_PRESS)
			cout << "Left mouse button pressed" << endl;
		else
			cout << "Left mouse button released" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (action == GLFW_PRESS)
			cout << "Middle mouse button pressed" << endl;
		else
			cout << "Middle mouse button released" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		if (action == GLFW_PRESS)
			cout << "Right mouse button pressed" << endl;
		else
			cout << "Right mouse button released" << endl;
	}
	break;

	default:
		cout << "Unhandled mouse button event" << endl;
		break;
	}
}

// render the scene
void URender(vector<GLMesh> scene)
{
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	//clear background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// transform the camera (x, y, z)
	glm::mat4 view = gCamera.GetViewMatrix();

	// create perspective projection (fov, aspect ratio, near plane, far plane)
	glm::mat4 projection;
	if (!perspective)
	{
		projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	}
	else
		projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);

	/*glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);*/

	// set shader
	glUseProgram(gShaderProgram);

	// gets and passes transform matrices to shader prgm
	GLint modelLocation = glGetUniformLocation(gShaderProgram, "model");
	GLint viewLocation = glGetUniformLocation(gShaderProgram, "view");
	GLint projLocation = glGetUniformLocation(gShaderProgram, "projection");


	for(auto i = 0; i < scene.size(); ++i)
	{
		auto mesh = scene[i];

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mesh.model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

		// activate vbo's within mesh's vao
		glBindVertexArray(mesh.vao);

		//draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}

	// deactivate vao
	glBindVertexArray(0);

	// swap front and back buffers
	glfwSwapBuffers(gWindow);

}


// clean-up methods
void UDestroyMesh(GLMesh& mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(2, mesh.vbos);
}
void UDestroyShaderProgram(GLuint programId)
{
	glDeleteProgram(programId);
}


// shape builders
void UBuildPyramid(GLMesh& mesh, vector<float> properties)
{

	//coordinates and colors for triangles
	//normalized to window
	// Specifies normalized device coordinates (x,y,z) and color for square vertices
	GLfloat verts[] =
	{
		// Vertex Positions    // Colors
		 0.0f,  0.5f,  0.0f,   properties[0], properties[1], properties[2], properties[3], // top of pyramid, red
		-0.5f, -0.5f, -0.5f,   properties[0], properties[1], properties[2], properties[3], // bottom left front
		 0.5f, -0.5f, -0.5f,   properties[0], properties[1], properties[2], properties[3], // bottom right front

		-0.5f, -0.5f,  0.5f,   properties[0], properties[1], properties[2], properties[3], // bottom left back
		 0.5f, -0.5f,  0.5f,   properties[0], properties[1], properties[2], properties[3], // bottom right back

	};

	const GLushort indices[] = {
		0, 1, 2,
		0, 1, 3,
		0, 3, 4,
		0, 2, 4,
		1, 2, 3,
		2, 3, 4
	};

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	//create 2 buffers
	glGenBuffers(2, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	mesh.nIndices = std::size(indices);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//tells how many values for a vertex
	const GLuint floatsPerVertex = 3;
	//tells how many values for a color
	const GLuint floatsPerColor = 4;

	//(2 + 4) * 1 = 6 strides
	//tells program that it'll need to hit 6 numbers before starting to draw the
	//next vertex
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);

	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);



	// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;

}
void UBuildCylinder(GLMesh& mesh, vector<float> properties, float radius, float length)
{
	// change "STEP" to increase / decrease resolution of cylinder
	const float PI = 3.14f;
	const float STEP = 36;
	float sectorStep = 2.0f * PI / STEP;

	// track which vertex is being added, add origin index when appropriate (every two)
	int step = 0;
	int vert = 2;


	// origin vertex of top and bottom of cylinder (center point)
	vector<float> vertices = {
								0.0f, 0.0f, 0.0f, properties[0], properties[1], properties[2], properties[3],	// top origin
								0.0f, 0.0f, length * -1, properties[0], properties[1], properties[2], properties[3]	// bottom origin
	};

	// vectors for indices, sides of cylinder
	vector<int> index = { 0 };
	vector<int> sides;
	
	// build the top of the cylinder
	// used vectors so I could use "pushback" and have control over where points went
	for (int i = 0; i <= STEP * 2; ++i)
	{
		float sectorAngle = i * sectorStep;
		// vertex
		vertices.push_back(radius * cos(sectorAngle)); // x
		vertices.push_back(radius * sin(sectorAngle)); // y
		vertices.push_back(0.0f);						// z

		// color
		vertices.push_back(properties[0]);
		vertices.push_back(properties[1]);
		vertices.push_back(properties[2]);
		vertices.push_back(properties[3]);

		// track the vertices to draw, track the sides to draw
		index.push_back(vert);
		sides.push_back(vert + 1);

		// some maths to keep indices in proper order
		vert++;
		step++;

		// add in the origin index every two  vertices so that it connects them
		if(step == 2)
		{
			step = 0;
			vert--;
			index.push_back(0);

			// more maths to keep the indices in proper order
			sides.pop_back();
		}

	}

	// more maths to keep indices in proper order
	vert*=2;
	step = 0;

	// set origin of bottom disk triangle fan
	index.push_back(1);
	
	// build bottom triangle fan of cylinder
	// same algorithm as above for top
	for (int i = 0; i <= STEP * 2; ++i)
	{
		float sectorAngle = i * sectorStep;
		vertices.push_back(radius * cos(sectorAngle)); // x
		vertices.push_back(radius * sin(sectorAngle)); // y
		vertices.push_back(length * -1);						// z

		// color
		vertices.push_back(properties[0]);
		vertices.push_back(properties[1]);
		vertices.push_back(properties[2]);
		vertices.push_back(properties[3]);
		index.push_back(vert);
		sides.push_back(vert - 1);

		// maths
		vert++;
		step++;
		if (step == 2)
		{
			step = 0;
			vert--;
			index.push_back(1);
			sides.pop_back();
		}
	}

	// remove the very last entry from the index array, tis' not needed
	index.pop_back();

	// list the indexes to draw the sides
	for (auto i = 0; i < sides.size() / 2 - 1; i++)
	{
		// lots of weird locations to find the given indices
		index.push_back(sides[i]);
		index.push_back(sides[i + 1]);
		index.push_back(sides[sides.size() / 2 + i]);

		index.push_back(sides[sides.size() / 2 + i]);
		index.push_back(sides[sides.size() / 2 + i + 1]);
		index.push_back(sides[i + 1]);


	}

	// okay all done! whew!
	// make an array of vertices
	// there doesn't seem to be an efficient way to convert from a vector to an array :(

	GLfloat verts[10000];
	for (int i = 0; i < vertices.size(); i++)
	{
		verts[i] = vertices[i];
	}

	// make an array for the indices
	GLushort indices[10000];
	for (int i = 0; i < index.size(); i++)
	{
		indices[i] = index[i];
	}

	// compile all that nonesense
	

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	//create 2 buffers
	glGenBuffers(2, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);

	

	// can this function take any other type of input? array's aren't very good imo
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	mesh.nIndices = std::size(indices);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//tells how many values for a vertex
	const GLuint floatsPerVertex = 3;
	//tells how many values for a color
	const GLuint floatsPerColor = 4;

	//(2 + 4) * 1 = 6 strides
	//tells program that it'll need to hit 6 numbers before starting to draw the
	//next vertex
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);

	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);


	// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;
}
void UBuildCone(GLMesh& mesh, vector<float> properties, float radius, float length)
{
	// this is the same algorithm as the cylinder
	// i plain run out of time to tweak it :(
	// so it's a little rough and big on memory

	const float PI = 3.14f;
	const float STEP = 36;
	float sectorStep = 2.0f * PI / STEP;

	// track which vertex is being added, add origin index when appropriate (every two)
	int step = 0;
	int vert = 2;

	vector<float> vertices = {
								0.0f, 0.0f, 0.0f, properties[0], properties[1], properties[2], properties[3],	// top origin
								0.0f, 0.0f, length * -1, properties[0], properties[1], properties[2], properties[3]	// bottom origin
	};

	vector<int> index = { 0, 1 };
	vector<int> sides;

	 //build the top of the cylinder
	for (int i = 0; i <= STEP * 2; ++i)
	{
		float sectorAngle = i * sectorStep;
		// vertex
		vertices.push_back(radius * cos(sectorAngle)); // x
		vertices.push_back(radius * sin(sectorAngle)); // y
		vertices.push_back(0.0f);						// z

		// color
		vertices.push_back(properties[0]);
		vertices.push_back(properties[1]);
		vertices.push_back(properties[2]);
		vertices.push_back(properties[3]);
		index.push_back(vert);
		sides.push_back(vert + 1);

		vert++;
		step++;
		if (step == 2)
		{
			step = 0;
			vert--;
			index.push_back(0);
			sides.pop_back();
		}

	}

	// skip ahead to the next set of vertices
	vert *= 2;
	step = 0;
	// set origin of bottom disk triangle fan
	index.push_back(1);

	// build bottom triangle fan of cylinder
	for (int i = 0; i <= STEP * 2; ++i)
	{
		float sectorAngle = i * sectorStep;
		vertices.push_back(radius * cos(sectorAngle)); // x
		vertices.push_back(radius * sin(sectorAngle)); // y
		vertices.push_back(0.0f);						// z

		// color
		vertices.push_back(properties[0]);
		vertices.push_back(properties[1]);
		vertices.push_back(properties[2]);
		vertices.push_back(properties[3]);
		index.push_back(vert);
		sides.push_back(vert - 1);
		//sides.push_back(vert);

		vert++;
		step++;
		if (step == 2)
		{
			step = 0;
			vert--;
			index.push_back(1);
			sides.pop_back();
		}
	}
	// remove the very last entry from the index array, tis' not needed
	index.pop_back();

	

	GLfloat verts[10000];

	for (int i = 0; i < vertices.size(); i++)
	{
		verts[i] = vertices[i];
	}

	GLushort indices[10000];

	for (int i = 0; i < index.size(); i++)
	{
		indices[i] = index[i];
	}



	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	//create 2 buffers
	glGenBuffers(2, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	mesh.nIndices = std::size(indices);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//tells how many values for a vertex
	const GLuint floatsPerVertex = 3;
	//tells how many values for a color
	const GLuint floatsPerColor = 4;

	//(2 + 4) * 1 = 6 strides
	//tells program that it'll need to hit 6 numbers before starting to draw the
	//next vertex
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);

	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);



	// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;
}
void UBuildPlane(GLMesh& mesh, vector<float> properties)
{

	//coordinates and colors for triangles
	//normalized to window
	// Specifies normalized device coordinates (x,y,z) and color for square vertices
	GLfloat verts[] =
	{
		// Vertex Positions    // Colors
		 5.0f,  0.0f,  5.0f,   properties[0], properties[1], properties[2], properties[3], 
		 5.0f,  0.0f, -5.0f,   properties[0], properties[1], properties[2], properties[3], 
		-5.0f,  0.0f,  5.0f,   properties[0], properties[1], properties[2], properties[3], 
		-5.0f,  0.0f, -5.0f,   properties[0], properties[1], properties[2], properties[3] 

	};

	const GLushort indices[] = {
		0, 1, 2, 1, 2, 3
	};

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	//create 2 buffers
	glGenBuffers(2, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	mesh.nIndices = std::size(indices);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//tells how many values for a vertex
	const GLuint floatsPerVertex = 3;
	//tells how many values for a color
	const GLuint floatsPerColor = 4;

	//(2 + 4) * 1 = 6 strides
	//tells program that it'll need to hit 6 numbers before starting to draw the
	//next vertex
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);

	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);



	// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;

}