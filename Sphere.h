#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include "GL/freeglut.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "Object.h"

using namespace glm;
using namespace std;

class Sphere : public Object
{
public:
	Sphere(GLfloat radius = 1.0f, GLint subDivision = 1);
	~Sphere();

	GLfloat getRadius() { return this->radius; }
	void setRadius(GLfloat radius) { this->radius = radius; }
	GLint getSubdivision() { return this->subdivision; }
	void setSubdivision(GLint subdivision) { this->subdivision = subdivision; }

private:

	vector<vec3> computeIcosahedronVertices();
	void buildVerticesFlat();

	GLfloat radius;
	GLint subdivision;

};

