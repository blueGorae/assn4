#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "Object.h"
#include "Plane.h"
#include "glm/glm.hpp"

class Background : public Object
{
public:
	Background(unsigned int width, unsigned int depth, unsigned int height) {
		frontPlane = Plane(width, height);
		backPlane = Plane(width, height);
		leftPlane = Plane(depth, height);
		rightPlane = Plane(depth, height);
		upperPlane = Plane(width, depth);
		downPlane = Plane(width, depth);

		addChild(&frontPlane);
		addChild(&backPlane);
		addChild(&leftPlane);
		addChild(&rightPlane);
		addChild(&upperPlane);
		addChild(&downPlane);
	}
	~Background();

private:
	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upperPlane;
	Plane downPlane;

};

