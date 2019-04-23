#include "Character.h"

glm::vec3 player1Location;
glm::vec3 player3Location;
glm::vec3 playerDirection;
extern GLint cameraMode;

glm::vec3 Character::translateVector(glm::vec3 direction) {
	GLfloat x = finalPositions[0].x;
	GLfloat y = finalPositions[0].y;
	glm::vec3 translate = glm::rotate(glm::mat4(1.f), glm::radians((float)angle), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(direction, 1.f);
	float HALF_W = WIDTH / 2;
	float HALF_D = DEPTH / 2;
	if (!isAuto) {
		translate.x = glm::clamp(x + translate.x, -HALF_W, HALF_W) - x;
		translate.y = glm::clamp(y + translate.y, -HALF_D, 0.f) - y;
	}
	else {
		translate.x = glm::clamp(x + translate.x, -HALF_W, HALF_W) - x;
		translate.y = glm::clamp(y + translate.y, 0.f, HALF_D) - y;
	}
	return translate;
}

void Character::updatedCurrentTransformationMatrix() {
	if (!isAuto) {
		player1Location = finalPositions[0];
		glm::vec4 normalizedPlayerDirection = glm::rotate(glm::radians((float)angle), glm::vec3(0.f, 0.f, 1.f)) 
			* glm::vec4(0.f, 1.f, finalPositions[0].z, 1.f);
		playerDirection = glm::scale(glm::vec3(10.f, 10.f, 1.f)) * normalizedPlayerDirection;
		player3Location = glm::vec3(
			finalPositions[0].x - normalizedPlayerDirection.x,
			finalPositions[0].y - normalizedPlayerDirection.y,
			finalPositions[0].z + 2* normalizedPlayerDirection.z
		);
		//player1Location = glm::vec3(
		//	finalPositions[0].x + playerDirection.x,
		//	finalPositions[0].y + playerDirection.y,
		//	finalPositions[0].z + 2 * playerDirection.z
		//);
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
	if (isAuto) {
		srand((unsigned int)time(NULL));
		switch (rand() % 2)
		{
		case 0:
			translateOrigin(translateVector(glm::vec3(0.f, 0.0001f, 0.f)));
			break;
		case 1:
			translateOrigin(translateVector(glm::vec3(0.f, -0.0001f, 0.f)));
			break;
		}
	}
	else {
		disableDraw = cameraMode == 1;
	}
}
