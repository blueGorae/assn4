#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include "Object.h"
#include "glm/glm.hpp"

using namespace glm;
using namespace std;

extern GLint vertexLocation;
extern GLint ctmLocation;

extern GLuint verticesVBO;
extern GLuint indiciesVBO;

extern glm::mat4 ctm;


class Character : public Object
{
private:
	bool isAuto;
	GLfloat diffAngle = 10.f;
	GLfloat angle = 0.f;


protected:
	glm::vec3 translateVector(glm::vec3 direction);
	virtual void moveObject();

public:
	Character() {}
	Character(glm::vec3 position, bool isAuto = true) : Object(position, "Chiko", 0.18f, 0.3f, true), isAuto(isAuto)
	{
		glm::mat4 initMatrix = glm::scale(glm::vec3(1 / 2000.f, 1 / 2000.f, 1 / 2000.f));

		if (isAuto) {
			initMatrix = glm::rotate((float)M_PI_2, glm::vec3(1.f, 0.f, 0.f))
				* initMatrix;
		}
		else {
			initMatrix = glm::rotate((float)M_PI_2, glm::vec3(1.f, 0.f, 0.f))
				* glm::rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f))
				* initMatrix;
		}
		setCoordinateMatrix(initMatrix);
		translateOrigin(glm::vec3(0.f, 0.f, 0.275f));
	}
	void pressed(unsigned char key);
	virtual ~Character() {}
};

