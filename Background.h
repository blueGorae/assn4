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

		frontPlane.setCoordinateMatrix(glm::translate(glm::mat4(1.f), glm::vec3( 0.f,-(depth/2.f), 0.f))
			* glm::rotate((float)M_PI_2, glm::vec3(1.f, 0.f, 0.f))* glm::translate(glm::mat4(1.f), glm::vec3(-frontPlane.getCenter()))) ;

		backPlane.setCoordinateMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, (depth / 2.f), 0.f))
			* glm::rotate((float)M_PI_2, glm::vec3(1.f, 0.f, 0.f))* glm::translate(glm::mat4(1.f), glm::vec3(-backPlane.getCenter())));

		leftPlane.setCoordinateMatrix(glm::translate(glm::mat4(1.f), glm::vec3(-(width/2.f), 0.f, 0.f))
			* glm::rotate((float)M_PI_2, glm::vec3(0.f, 1.f, 0.f))* glm::translate(glm::mat4(1.f), glm::vec3(-leftPlane.getCenter() )));

		rightPlane.setCoordinateMatrix(glm::translate(glm::mat4(1.f), glm::vec3((width / 2.f), 0.f, 0.f))
			* glm::rotate((float)M_PI_2, glm::vec3(0.f, 1.f, 0.f))* glm::translate(glm::mat4(1.f), glm::vec3(-rightPlane.getCenter() )));

		//upperPlane.setOriginalMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, (height/2.f)))
		//	* glm::translate(glm::mat4(1.f), glm::vec3(-upperPlane.getCenter())));

		downPlane.setCoordinateMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -(height / 2.f)))
			* glm::translate(glm::mat4(1.f), glm::vec3(-downPlane.getCenter() )));

		addChild(&frontPlane);
		addChild(&backPlane);
		addChild(&leftPlane);
		addChild(&rightPlane);
		//addChild(&upperPlane);
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

