#include "PointLight.h"


void PointLight::init()
{
    glUniform4f(pLightPositionLocation[id], position[0], position[1], position[2], 1.f);
}

void PointLight::draw()
{
    glm::vec3 lightPosition = glm::rotate(glm::mat4(1.f),
                                          glm::radians(angle),
                                          pivot) * glm::vec4(position, 1.f);
    glUniform4f(pLlightPositionLocation[id], lightPosition[0], lightPosition[1], lightPosition[2], 1.f);
    glUniform4f(pAmbientProductLocation[id], ambientStrength, ambientStrength, ambientStrength, 1.f);
    glUniform4f(pDiffuseProductLocation[id], diffuseStrength[0], diffuseStrength[1], diffuseStrength[2],1.f);
    glUniform4f(pSpecularProductLocation[id], specularStrength[0], specularStrength[1], specularStrength[2],1.f);
    glUniform1f(pShininessLocation[id], shininess);
}