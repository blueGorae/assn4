#include "PointLight.h"


void PointLight::init()
{
    glUniform4f(pLightPositionLocation[id], position[0], position[1], position[2], 1.f);
}

void PointLight::draw()
{
	glm::vec3 lightPosition = glm::vec3(
		parent->finalPosition().x + finalPositions[0].x,
		parent->finalPosition().y + finalPositions[0].y,
		parent->finalPosition().z + finalPositions[0].z
	);
    glUniform4f(pLightPositionLocation[id],	lightPosition.x, lightPosition.y, lightPosition.z, 1.f);
    glUniform4f(pAmbientProductLocation[id], ambientStrength, ambientStrength, ambientStrength, 1.f);
    glUniform4f(pDiffuseProductLocation[id], diffuseStrength[0], diffuseStrength[1], diffuseStrength[2],1.f);
    glUniform4f(pSpecularProductLocation[id], specularStrength[0], specularStrength[1], specularStrength[2],1.f);
    glUniform1f(pShininessLocation[id], shininess);
}