#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

extern GLint pointLightCount;
extern GLint pAmbientProductLocation[POINT_LIGHTS];
extern GLint pDiffuseProductLocation[POINT_LIGHTS];
extern GLint pSpecularProductLocation[POINT_LIGHTS];
extern GLint pLightPositionLocation[POINT_LIGHTS];
extern GLint pShininessLocation[POINT_LIGHTS];

class PointLight : public Object
{
private :
    GLint id;
    GLfloat ambientStrength;
    glm::vec3 diffuseStrength;
    glm::vec3 specularStrength;
    GLfloat shininess;
public:
    PointLight(glm::vec3 position,
               GLfloat ambientStrength = 1.f,
               glm::vec3 diffuseStrength = glm::vec3(0.6f),
               glm::vec3 specularStrength = glm::vec3(0.4f),
               GLfloat shininess = 32)
            : Object(position), disableDraw(true), pivot(pivot), color(color),
              ambientStrength(ambientStrength), diffuseStrength(diffuseStrength),
              specularStrength(specularStrength), shininess(shininess) {
        id = pointLightCount;
        pointLightCount += 1;
    }

    void draw();

    virtual ~DirectionalLight() {}
};

