#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

#define DIRECTIONAL_LIGHTS 1
#define POINT_LIGHTS 1

extern GLint directionalLightCount;
extern GLint ambientProductLocation[DIRECTIONAL_LIGHTS];
extern GLint diffuseProductLocation[DIRECTIONAL_LIGHTS];
extern GLint specularProductLocation[DIRECTIONAL_LIGHTS];
extern GLint lightPositionLocation[DIRECTIONAL_LIGHTS];
extern GLint shininessLocation[DIRECTIONAL_LIGHTS];

class DirectionalLight {
private :
    GLint id;
    glm::vec3 position;
    glm::vec3 pivot;
    GLfloat diffAngle = 0.05f;
    GLfloat initAngle = -60.f;
    GLfloat angle = initAngle;
    bool isPM = false;
    GLfloat ambientStrength;
    glm::vec3 diffuseStrength;
    glm::vec3 specularStrength;
    GLfloat shininess;
public:
    DirectionalLight(glm::vec3 position,
                     glm::vec3 pivot,
                     GLfloat ambientStrength = 1.f,
                     glm::vec3 diffuseStrength = glm::vec3(0.7f),
                     glm::vec3 specularStrength = glm::vec3(0.3f),
                     GLfloat shininess = 128)
            : position(position), pivot(pivot),
              ambientStrength(ambientStrength), diffuseStrength(diffuseStrength),
              specularStrength(specularStrength), shininess(shininess) {
        id = directionalLightCount;
        directionalLightCount += 1;
    }

    void init();

    void move();

    virtual ~DirectionalLight() {}
};

