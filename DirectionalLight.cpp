#include "DirectionalLight.h"


void DirectionalLight::init()
{
    glUniform4fv(lightPositionLocation, 1, position)
}

void DirectionalLight::move()
{
    angle += diffAngle;
    if (angle > 60) {
        angle = initAngle;
    }
    glUniform4fv(lightPositionLocation, 1, glm::rotate(glm::mat4(1.f),
                                                       glm::radians((float)-diffAngle),
                                                       pivot)
                                           * position);
    glUniform4fv(ambientProductLocation, 1, glm::vec4(ambientStrength,ambientStrength,ambientStrength,1.f));
}