#include "Character.h"



void Character::pressed(unsigned char key)
{
	GLfloat x = finalPositions[0].x;
	GLfloat y = finalPositions[0].y;
	if (!isAuto) {
		switch (key)
		{
		case 'W':
		case 'w':
			glm::vec3 translateW = glm::rotate(glm::mat4(1.f), glm::radians(angle), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(0.f, 0.01f, 0.f, 1.f);
			translateOrigin(translateW);
			break;
		case 'A':
		case 'a':
			translateOrigin(-x, -y);
			angle += diffAngle;
			rotateOrigin(glm::radians(diffAngle), glm::vec3(0.f, 0.f, 1.f));
			translateOrigin(x, y);
			break;
		case 'S':
		case 's':
			glm::vec3 translateS = glm::rotate(glm::mat4(1.f), glm::radians(angle), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(0.f, -0.01f, 0.f, 1.f);
			translateOrigin(translateS);
			break;
		case 'D':
		case 'd':
			translateOrigin(-x, -y);
			angle -= diffAngle;
			rotateOrigin(glm::radians(-diffAngle), glm::vec3(0.f, 0.f, 1.f));
			translateOrigin(x, y);
			break;
		}
	}
}

void Character::drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix)
{

}

void Character::moveObject()
{

}