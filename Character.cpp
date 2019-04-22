#include "Character.h"



void Character::localInit()
{

}

void Character::pressed(unsigned char key)
{
	if (!isAuto) {
		switch (key)
		{
		case 'W':
		case 'w':
			translateOrigin(0.f, 0.01f);
			break;
		case 'A':
		case 'a':
			rotateOrigin(0.1f);
			break;
		case 'S':
		case 's':
			translateOrigin(0.f, -0.01f);
			break;
		case 'D':
		case 'd':
			rotateOrigin(-0.1f);
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