#include "Character.h"

glm::vec3 playerLocation;
glm::vec3 player3Location;
glm::vec3 playerDirection;

glm::vec3 Character::translateVector(glm::vec3 direction) {
	GLfloat x = finalPositions[0].x;
	GLfloat y = finalPositions[0].y;
	glm::vec3 translate = glm::rotate(glm::mat4(1.f), glm::radians((float)angle), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(direction, 1.f);
	translate.x = glm::clamp(x + translate.x, -1.f, 1.f) - x;
	translate.y = glm::clamp(y + translate.y, -1.f, 0.f) - y;
	return translate;
}

void Character::updatedCurrentTransformationMatrix() {
	if (!isAuto) {
		playerLocation = finalPositions[0];
		playerDirection = glm::rotate(glm::radians((float)angle), glm::vec3(0.f, 0.f, 1.f)) 
			* glm::vec4(0.f, 1.f, finalPositions[0].z, 1.f);
		player3Location = glm::vec3(
			playerLocation.x - playerDirection.x,
			playerLocation.y - playerDirection.y,
			playerLocation.z + 2*playerDirection.z
		);
	}
}

void Character::pressed(unsigned char key)
{
	GLfloat x = finalPositions[0].x;
	GLfloat y = finalPositions[0].y;
	if (!isAuto) {
		switch (key)
		{
		case 'W':
		case 'w':
			translateOrigin(translateVector(glm::vec3(0.f, 0.01f, 0.f)));
			break;
		case 'A':
		case 'a':
			translateOrigin(-x, -y);
			angle += diffAngle;
			angle %= 360;
			rotateOrigin(glm::radians((float)diffAngle), glm::vec3(0.f, 0.f, 1.f));
			translateOrigin(x, y);
			break;
		case 'S':
		case 's':
			translateOrigin(translateVector(glm::vec3(0.f, -0.01f, 0.f)));
			break;
		case 'D':
		case 'd':
			translateOrigin(-x, -y);
			angle -= diffAngle;
			angle %= 360;
			rotateOrigin(glm::radians((float)-diffAngle), glm::vec3(0.f, 0.f, 1.f));
			translateOrigin(x, y);
			break;
		}
	}
	updateCurrentTransformationMatrix();
}


void Character::moveObject()
{

}
