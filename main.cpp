#include <stdio.h>
#include <stdlib.h>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "GL/glut.h"


#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

template <typename T, size_t N> char(*RtlpNumberOf(T(&)[N]))[N];
#define ARRAYSIZE(A) (sizeof(*RtlpNumberOf(A)))

using namespace std;
using namespace glm;

mat4 projectionMat;
mat4 modelViewMat;

GLchar vertexShaderFile[] = "shader/my.vert.glsl";
GLchar fragShaderFile[] = "shader/my.frag.glsl";
GLuint myProgramObj;


GLint modelViewMatLocation;
GLint projectionMatLocation;

GLint vertexLocation;

GLuint verticesVBO;

GLuint VAO;



vec4 points[] = { vec4(-0.5f, 0.0f, 0.0f, 1.0f), vec4(0.5f, 0.0f, 0.0f, 1.0f) , vec4(-0.5f, 0.5f, 0.0f, 1.0f)};

bool LoadShaders(const char * vertexShaderFile, const char * fragShaderFile) {
	GLuint myVertexObj = glCreateShader(GL_VERTEX_SHADER);
	GLuint myFragObj = glCreateShader(GL_FRAGMENT_SHADER);


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

	// Link program
	printf("Linking program\n");
	myProgramObj = glCreateProgram();
	glAttachShader(myProgramObj, myVertexObj);
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
		glDeleteProgram(myProgramObj);
		return false;
	}

	glUseProgram(myProgramObj);

	glDeleteShader(myVertexObj);
	glDeleteShader(myFragObj);

	return true;
}

bool Init() {
	LoadShaders(vertexShaderFile, fragShaderFile);

	vertexLocation = glGetAttribLocation(myProgramObj, "vPosition");

	projectionMatLocation = glGetUniformLocation(myProgramObj, "projection");
	modelViewMatLocation = glGetUniformLocation(myProgramObj, "modelView");


	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, ARRAYSIZE(points) * 4 * sizeof(GL_FLOAT), points, GL_STATIC_DRAW);
	
	// Use the program.
	glUseProgram(myProgramObj);

	// Create the VAO for the program.
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Bind the only used VBO in this example.
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vertexLocation);


	projectionMat = mat4(1.0f);
	modelViewMat = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	
	glUniformMatrix4fv(projectionMatLocation, 1, GL_TRUE, &projectionMat[0][0]);
	glUniformMatrix4fv(modelViewMatLocation, 1, GL_TRUE, &modelViewMat[0][0]);
	
	return true;

}

void display(void) { 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glutSwapBuffers();
} 

int main(int argc, char **argv) {

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
	glutInitWindowPosition(100, 100);  
	glutInitWindowSize(320, 320); 
	glutCreateWindow("Hello OpenGL"); 
	glutDisplayFunc(display);  
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);  
	glewInit();  
	Init();
	glutMainLoop();
}


