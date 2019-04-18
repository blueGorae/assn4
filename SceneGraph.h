#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include "mat.h"
#include "Object.h"

using namespace std;
using namespace Angel;


class SceneGraph
{

public:
	SceneGraph() {
		root->setParent(NULL);
	};
	~SceneGraph();

	Object * getRoot() { return this->root; }

private:
	Object * root;
	mat4 projectionMat = Angel::identity();
	mat4 modelViewMat = Angel::identity();
	mat4 ctm = projectionMat * modelViewMat;



};

