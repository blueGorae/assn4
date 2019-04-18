#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include "Object.h"
#include "mat.h"

using namespace Angel;
using namespace std;

class Sphere : public Object
{
public:
	Sphere(GLfloat radius = 1.0f, GLint subDivision = 1, vec3 position = vec3(0.f, 0.f, 0.f));
	~Sphere();

	GLfloat getRadius() { return this->radius; }
	void setRadius(GLfloat radius) { this->radius = radius; }
	GLint getSubdivision() { return this->subdivision; }
	void setSubdivision(GLint subdivision) { this->subdivision = subdivision; }

private:

	vector<vec3> computeIcosahedronVertices();
	vec3 computeHalfVertex(vec3 v1, vec3 v2, float length);
	float computeScaleForLength(vec3 v, float length);
	void subdivideVerticesFlat();
	void buildVerticesFlat();

	GLfloat radius;
	GLint subdivision;

};

