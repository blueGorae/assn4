#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

extern GLint ambientProductLocation;
extern GLint diffuseProductLocation;
extern GLint specularProductLocation;
extern GLint lightPositionLocation;
extern GLint shininessLocation;

class DirectionalLight
{
private :
    glm::vec3 position;
    glm::vec3 pivot;
    glm::vec3 color;
    GLfloat diffAngle = 0.05f;
    GLfloat initAngle = -60.f;
    GLfloat angle = initAngle;
	bool isPM = false;
    GLfloat ambientStrength;
public:
    DirectionalLight(glm::vec3 position,
                     glm::vec3 pivot,
                     glm::vec3 color,
                     GLfloat ambientStrength = 1.f)
    : position(position), pivot(pivot), color(color), ambientStrength(ambientStrength) {}
    void init();
    void move();
	virtual ~DirectionalLight(){}
};

