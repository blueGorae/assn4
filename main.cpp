#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Background.h"
#include "Sphere.h"
#include "Floor.h"

#include "mat.h"
#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

using namespace Angel;
using namespace std;

mat4 projectionMat;
mat4 modelViewMat;
mat4 ctm;

GLchar vertexShaderFile[] = "shader/vert.glsl";
GLchar fragShaderFile[] = "shader/frag.glsl";
GLchar geometryShaderFile[] = "shader/geometry.glsl";

GLuint myProgramObj;


GLint ctmLocation;

GLint vertexLocation;

GLuint verticesVBO;
GLuint indiciesVBO;

GLuint ballVAO;
GLuint bachgroundVAO;

Sphere sphere(0.2f, 2);
Floor myfloor(4, 8);

bool LoadShaders(const char * vertexShaderFile, const char * fragShaderFile, const char * geometryShaderFile) {
	GLuint myVertexObj = glCreateShader(GL_VERTEX_SHADER);
	GLuint myFragObj = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint myGeoObj = glCreateShader(GL_GEOMETRY_SHADER);

	//Read Vertex File
	string vertexShaderCode;
	ifstream vertexShaderStream;

	vertexShaderStream.open(vertexShaderFile, ifstream::in);

	if (vertexShaderStream.is_open()) {
		stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
	else {
		cout << "File does not open" << endl;
		getchar();
		return false;
	}

	//Read Frag File
	string fragShaderCode;
	ifstream fragShaderStream;

	fragShaderStream.open(fragShaderFile, ifstream::in);

	if (fragShaderStream.is_open()) {
		stringstream sstr;
		sstr << fragShaderStream.rdbuf();
		fragShaderCode = sstr.str();
		fragShaderStream.close();
	}
	else {
		cout << "File does not open" << endl;
		getchar();
		return false;
	}

	//Read Geometry File
	string geometryShaderCode;
	ifstream geometryShaderStream;

	geometryShaderStream.open(geometryShaderFile, ifstream::in);

	if (geometryShaderStream.is_open()) {
		stringstream sstr;
		sstr << geometryShaderStream.rdbuf();
		geometryShaderCode = sstr.str();
		geometryShaderStream.close();
	}
	else {
		cout << "File does not open" << endl;
		getchar();
		return false;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertexShaderFile);
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(myVertexObj, 1, &vertexSourcePointer, NULL);
	glCompileShader(myVertexObj);

	// Check Vertex Shader
	glGetShaderiv(myVertexObj, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(myVertexObj, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(myVertexObj, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragShaderFile);
	char const * fragSourcePointer = fragShaderCode.c_str();
	glShaderSource(myFragObj, 1, &fragSourcePointer, NULL);
	glCompileShader(myFragObj);

	// Check Fragment Shader
	glGetShaderiv(myFragObj, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(myFragObj, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(myFragObj, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Compile Geometry Shader
	printf("Compiling shader : %s\n", geometryShaderFile);
	char const * geometrySourcePointer = geometryShaderCode.c_str();
	glShaderSource(myGeoObj, 1, &geometrySourcePointer, NULL);
	glCompileShader(myGeoObj);

	// Check Fragment Shader
	glGetShaderiv(myGeoObj, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(myGeoObj, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vector<char> GeometryShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(myGeoObj, InfoLogLength, NULL, &GeometryShaderErrorMessage[0]);
		printf("%s\n", &GeometryShaderErrorMessage[0]);
	}


	// Link program
	printf("Linking program\n");
	myProgramObj = glCreateProgram();
	glAttachShader(myProgramObj, myVertexObj);
	//glAttachShader(myProgramObj, myGeoObj);
	glAttachShader(myProgramObj, myFragObj);
	glLinkProgram(myProgramObj);

	// Check Program
	glGetProgramiv(myProgramObj, GL_LINK_STATUS, &Result);
	glGetProgramiv(myProgramObj, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0) {
		vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(myProgramObj, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
		glDeleteShader(myVertexObj);
		glDeleteShader(myFragObj);
		glDeleteShader(myGeoObj);
		glDeleteProgram(myProgramObj);
		return false;
	}

	glUseProgram(myProgramObj);

	glDeleteShader(myVertexObj);
	glDeleteShader(myGeoObj);
	glDeleteShader(myFragObj);

	return true;
}

bool Init() {

	//Load Shaders
	LoadShaders(vertexShaderFile, fragShaderFile, geometryShaderFile);

	vertexLocation = glGetAttribLocation(myProgramObj, "vPosition");
	ctmLocation = glGetUniformLocation(myProgramObj, "ctm");

	//Init Buffer
	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sphere.getVerticesSize(), &sphere.getVertices()[0].x, GL_STATIC_DRAW);

	glGenBuffers(1, &indiciesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere.getIndiciesSize(), &sphere.getIndices()[0], GL_STATIC_DRAW);

	// Use the program.
	glUseProgram(myProgramObj);

	// Create the ballVAO for the program.
	glGenVertexArrays(1, &ballVAO);
	glBindVertexArray(ballVAO);

	// Bind for VBO 
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vertexLocation);


	projectionMat = Angel::identity();
	modelViewMat = Angel::identity();

	ctm = projectionMat * modelViewMat;
	glUniformMatrix4fv(ctmLocation, 1, GL_TRUE, &ctm[0][0]);

	return true;

}

void display(void) { 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	modelViewMat = RotateY(0.1f) * modelViewMat;
	ctm = projectionMat * modelViewMat;
	glUniformMatrix4fv(ctmLocation, 1, GL_TRUE, &ctm[0][0]);
	glDrawElements(GL_LINE_LOOP, sphere.getIndexCount(), GL_UNSIGNED_INT, 0);
	glutSwapBuffers();
} 

void Idle(void) {
	glutPostRedisplay();
}

int main(int argc, char **argv) {

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
	glutInitWindowPosition(100, 100);  
	glutInitWindowSize(720, 720);
	glutCreateWindow("Hello OpenGL"); 
	glutDisplayFunc(display);
	glutIdleFunc(Idle);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);  
	glewInit();  
	Init();
	glutMainLoop();
}


