#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include "Object.h"
#include "glm/glm.hpp"

using namespace std;


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

