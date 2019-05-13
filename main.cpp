#define GLM_ENABLE_EXPERIMENTAL
#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

#include "GL/glew.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "SceneGraph.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "GL/freeglut.h"
#include "GL/glut.h"
#include "glm/gtx/transform.hpp"
#include "ScoreBox.h"

using namespace std;

bool isTextureOn = true;
bool isGouraudShading = true;
bool isNoLight = false;
bool isNormalMapping = true;
const unsigned endScore = 15;

glm::vec4 modelColor;
glm::vec4 backgroundColor;
glm::mat4 projectionMat;
glm::mat4 modelViewMat;

GLchar vertexShaderFile[] = "shader/vert.glsl";
GLchar fragShaderFile[] = "shader/frag.glsl";

GLuint myProgramObj;
GLint projectionMatrixLocation;
GLint viewMatrixLocation;
GLint modelMatrixLocation;
GLint isGouraudShadingLocation;
GLint isNoLightLocation;
GLint directionalLightCount;
GLint ambientProductLocation[DIRECTIONAL_LIGHTS];
GLint diffuseProductLocation[DIRECTIONAL_LIGHTS];
GLint specularProductLocation[DIRECTIONAL_LIGHTS];
GLint lightPositionLocation[DIRECTIONAL_LIGHTS];
GLint shininessLocation[DIRECTIONAL_LIGHTS];
GLint pointLightCount;
GLint pAmbientProductLocation[POINT_LIGHTS];
GLint pDiffuseProductLocation[POINT_LIGHTS];
GLint pSpecularProductLocation[POINT_LIGHTS];
GLint pLightPositionLocation[POINT_LIGHTS];
GLint pShininessLocation[POINT_LIGHTS];

GLint vertexLocation;
GLint colorLocation;
GLint textureLocation;
GLint normalLocation;

GLuint verticesVBO;
GLuint indiciesVBO;
GLuint texturesVBO;
GLuint normalsVBO;

SceneGraph sceneGraph;
Camera camera;

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
	modelColor= vec4(0.f, 1.f, 1.f, 1.f);
	backgroundColor = vec4(0.3f, 0.3f, 0.3f, 1.0f);

	//Load Shaders
	LoadShaders(vertexShaderFile, fragShaderFile);

	sceneGraph =  SceneGraph();


	sceneGraph.init();
	glUniform1i(isGouraudShadingLocation, isGouraudShading);
	glUniform1i(isNoLightLocation, isNoLight);
	glUniform4f(colorLocation, modelColor[0], modelColor[1], modelColor[2], modelColor[3]);

	return true;
}

void DisplayFunc(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
	sceneGraph.updateMatrix(
            camera.ProjectionMatrix(),
            camera.ModelViewMatrix());
	sceneGraph.DisplayFunc();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
} 

void IdleFunc(void) {
	sceneGraph.IdleFunc();
	glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
    case 'R':
    case 'r':
        sceneGraph.reset();
        break;
	case 'W':
	case 'w':
	case 'A':
	case 'a':
	case 'S':
	case 's':
	case 'D':
	case 'd':
	case 'T':
	case 't':
	case 'F':
	case 'f':
	case 'G':
	case 'g':
	case 'H':
	case 'h':
		sceneGraph.KeyboardFunc(key, x, y);
		break;
	case '4':
		isTextureOn = !isTextureOn;
		break;
    case '5':
		isGouraudShading = !isGouraudShading;
		glUniform1i(isGouraudShadingLocation, isGouraudShading);
        break;
	case '0':
		isNoLight = !isNoLight;
		glUniform1i(isNoLightLocation, isNoLight);
		break;
	case '1':
    case '2':
    case '3':
	case 'I':
	case 'i':
	case 'J':
    case 'j':
    case 'K':
    case 'k':
    case 'L':
    case 'l':
        camera.KeyboardFunc(key, x, y);
		break;
	default:
		return;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
	glutInitWindowPosition(100, 100);  
	glutInitWindowSize(720, 720);
	glutCreateWindow("Assignment4"); 
	glutKeyboardFunc(KeyboardFunc);
	glutDisplayFunc(DisplayFunc);
	glutIdleFunc(IdleFunc);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);  
	glewInit();  
	Init();
	glutMainLoop();
}


