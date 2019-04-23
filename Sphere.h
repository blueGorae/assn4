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
private:
	vector<glm::vec3> computeIcosahedronVertices();
	glm::vec3 computeHalfVertex(glm::vec3 v1, glm::vec3 v2, float length);
	float computeScaleForLength(glm::vec3 v, float length);
	void subdivideVerticesFlat();
	void buildVerticesFlat();

	GLfloat radius;
	GLint subdivision;
	GLint angle = 19;

protected:
	glm::vec3 translateVector(glm::vec3 direction = glm::vec3(0.f, 1.f, 0.f));
	virtual void moveObject();

public:
	Sphere(GLfloat radius = 1.0f, GLint subDivision = 1) 
		: Object(glm::vec3(0.f, 0.f, radius), "", 2 * radius, 2 * radius, 0.5f, 0.5f, true), radius(radius), subdivision(subDivision) {
		buildVerticesFlat();
	};
	~Sphere() {};

	GLfloat getRadius() { return this->radius; }
	void setRadius(GLfloat radius) { this->radius = radius; }
	GLint getSubdivision() { return this->subdivision; }
	void setSubdivision(GLint subdivision) { this->subdivision = subdivision; }
	void pressed(unsigned char key);
	virtual Object* actionCollision(Collision* collision);
};

