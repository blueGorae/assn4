#include "DirectionalLight.h"


void DirectionalLight::init()
{
	glUniform4f(lightPositionLocation[id], position[0], position[1], position[2], 1.f);
}

void DirectionalLight::move()
{
    angle += diffAngle;
    if (angle > 60) {
        angle = initAngle;
		isPM = !isPM;
    }
	glm::vec3 lightPosition = glm::rotate(glm::mat4(1.f),
		glm::radians(angle),
		pivot) * glm::vec4(position, 1.f);
    glUniform4f(lightPositionLocation[id], lightPosition[0], lightPosition[1], lightPosition[2], 1.f);
	GLfloat updateAmbient = isPM ? ambientStrength * .25f : ambientStrength;
	glUniform4f(ambientProductLocation[id], updateAmbient, updateAmbient, updateAmbient, 1.f);
    glUniform4f(diffuseProductLocation[id], diffuseStrength[0], diffuseStrength[1], diffuseStrength[2],1.f);
    glUniform4f(specularProductLocation[id], specularStrength[0], specularStrength[1], specularStrength[2],1.f);
    glUniform1f(shininessLocation[id], shininess);
}