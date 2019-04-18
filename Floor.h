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

private:
	unsigned int width;
	unsigned int depth;
	void buildVertices();
};

