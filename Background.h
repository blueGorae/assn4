#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "Object.h"
#include "Plane.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

extern GLuint backgroundVAO;

extern glm::mat4 ctm;

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

		frontPlane.setOriginalMatrix (glm::translate(glm::mat4(1.f), glm::vec3(0.5f, 0.f, 0.f)));
		//backPlane.setOriginalMatrix(glm::translate(glm::vec3(-frontPlane.getCenter().x, -frontPlane.getCenter().y, 0.f)));
		//leftPlane.setOriginalMatrix(glm::translate(glm::vec3(-frontPlane.getCenter().x, -frontPlane.getCenter().y, 0.f)));
		//rightPlane.setOriginalMatrix(glm::translate(glm::vec3(-frontPlane.getCenter().x, -frontPlane.getCenter().y, 0.f)));
		//upperPlane.setOriginalMatrix(glm::translate(glm::vec3(-frontPlane.getCenter().x, -frontPlane.getCenter().y, 0.f)));
		//downPlane.setOriginalMatrix(glm::translate(glm::vec3(-frontPlane.getCenter().x, -frontPlane.getCenter().y, 0.f)));

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

