#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
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
		leftPlane = Plane(height, depth);
		rightPlane = Plane(height, depth);
		upperPlane = Plane(width, depth);
		downPlane = Plane(width, depth);

		frontPlane.setOriginalMatrix (glm::translate(glm::mat4(1.f), glm::vec3( 0.f,-(depth/20.0f), 0.f)) 
			* glm::rotate((float)M_PI_2, glm::vec3(1.f, 0.f, 0.f))* glm::translate(glm::mat4(1.f), glm::vec3(-frontPlane.getCenter()/10.f))) ;

		backPlane.setOriginalMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, (depth / 20.0f), 0.f))
			* glm::rotate((float)M_PI_2, glm::vec3(1.f, 0.f, 0.f))* glm::translate(glm::mat4(1.f), glm::vec3(-backPlane.getCenter() / 10.f)));

		leftPlane.setOriginalMatrix(glm::translate(glm::mat4(1.f), glm::vec3(-(width/20.f), 0.f, 0.f))
			* glm::rotate((float)M_PI_2, glm::vec3(0.f, 1.f, 0.f))* glm::translate(glm::mat4(1.f), glm::vec3(-leftPlane.getCenter() / 10.f)));

		rightPlane.setOriginalMatrix(glm::translate(glm::mat4(1.f), glm::vec3((width / 20.f), 0.f, 0.f))
			* glm::rotate((float)M_PI_2, glm::vec3(0.f, 1.f, 0.f))* glm::translate(glm::mat4(1.f), glm::vec3(-rightPlane.getCenter() / 10.f)));

		upperPlane.setOriginalMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, (height/20.f)))
			* glm::translate(glm::mat4(1.f), glm::vec3(-upperPlane.getCenter() / 10.f)));

		downPlane.setOriginalMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -(height / 20.f)))
			* glm::translate(glm::mat4(1.f), glm::vec3(-downPlane.getCenter() / 10.f)));

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

