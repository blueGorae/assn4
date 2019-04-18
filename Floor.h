#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include "Object.h"
#include "mat.h"

using namespace Angel;
using namespace std;

class Floor : public Object
{
public:
	Floor(unsigned int width, unsigned int depth) : width(width), depth(depth) {
		buildVertices();
	};
	~Floor();

	vec3 getCenter() { return vec3(width / 2.0f, depth / 2.0f, 0.f); }
private:
	unsigned int width;
	unsigned int depth;
	void buildVertices();
};

