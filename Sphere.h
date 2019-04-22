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

class Sphere : public Object
{
public:
	Sphere(GLfloat radius = 1.0f, GLint subDivision = 1, glm::vec3 position = glm::vec3(0.f, 0.f, 0.f));
	~Sphere();

	GLfloat getRadius() { return this->radius; }
	void setRadius(GLfloat radius) { this->radius = radius; }
	GLint getSubdivision() { return this->subdivision; }
	void setSubdivision(GLint subdivision) { this->subdivision = subdivision; }

private:
	vector<glm::vec3> computeIcosahedronVertices();
	glm::vec3 computeHalfVertex(glm::vec3 v1, glm::vec3 v2, float length);
	float computeScaleForLength(glm::vec3 v, float length);
	void subdivideVerticesFlat();
	void buildVerticesFlat();

	GLfloat radius;
	GLint subdivision;

};

