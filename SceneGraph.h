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
	SceneGraph() {};
	~SceneGraph();

	Object * getRoot() { return this->root; }

private:
	Object * root = new Object();
	mat4 projectionMat = Angel::identity();
	mat4 modelViewMat = Angel::identity();
	mat4 ctm = projectionMat * modelViewMat;



};

