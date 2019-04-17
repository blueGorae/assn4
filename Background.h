#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include "Object.h"
#include "mat.h"

using namespace Angel;
using namespace std;

class Background : public Object
{
public:
	Background(unsigned int width = 4, unsigned int depth = 8, unsigned int height = 4) : width(width), depth(depth), height(height) {};
	~Background();

private:
	unsigned int width;
	unsigned int depth;
	unsigned int height;

	void buildVertices();

};

