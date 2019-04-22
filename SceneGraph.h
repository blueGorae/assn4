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
	glm::mat4 Projection;
	glm::mat4 View;

public:
	SceneGraph() {};
	~SceneGraph();

	Object * getRoot() { return this->root; }
	void updateMatrix(glm::mat4 projection, glm::mat4 view) {
		this->Projection = projection;
		this->View = view;
	}

	void draw() {
		root->draw();
	}
};

