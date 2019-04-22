#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

#include "GL/glew.h"
#include <iostream>
#include <vector>
#include <math.h>
#include "Object.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "Sphere.h"
#include "Background.h"
#include "glm/glm.hpp"
#include "GL/freeglut.h"
#include "GL/glut.h"
#include "Character.h"

using namespace std;

extern glm::mat4 projectionMat;
extern glm::mat4 modelViewMat;
extern glm::mat4 ctm;


extern GLuint myProgramObj;

extern GLint ctmLocation;

extern GLint vertexLocation;

extern GLuint verticesVBO;
extern GLuint indiciesVBO;


class SceneGraph
{
private:
	Object * root = new Object();
	glm::mat4 projectionMatrix;
	glm::mat4 modelViewMatrix;

public:
	SceneGraph() {};
	~SceneGraph() {};

	void init();
	void updateMatrix(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix) {
		this->projectionMatrix = projectionMatrix;
		this->modelViewMatrix = modelViewMatrix;
	}

	Object* getRoot() { return root; }

    void KeyboardFunc(unsigned char key, int x, int y);
	void DisplayFunc();
	void IdleFunc();
};

