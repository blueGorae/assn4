#include "DirectionalLight.h"


void DirectionalLight::init()
{
	glUniform4f(lightPositionLocation, position[0], position[1], position[2], 1.f);
}

void DirectionalLight::move()
{
    angle += diffAngle;
    if (angle > 60) {
        angle = initAngle;
		isPM = !isPM;
    }
	glm::vec3 lightPosition = glm::rotate(glm::mat4(1.f),
		glm::radians((float)angle)*0.01f,
		pivot) * glm::vec4(position, 1.f);
    glUniform4f(lightPositionLocation, lightPosition[0], lightPosition[1], lightPosition[2], 1.f);
	GLfloat updateAmbient = isPM ? ambientStrength * .5f : ambientStrength;
	glUniform4f(ambientProductLocation, updateAmbient, updateAmbient, updateAmbient, 1.f);
}