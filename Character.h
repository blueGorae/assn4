#pragma once
#include "Object.h"

class Character : public Object
{
private:
	bool isAuto;

protected:
	virtual void drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix);
	virtual void moveObject();

public:
	Character() {}
	Character(glm::vec3 position, bool isAuto = true) : Object(position, "PICKCKCKCK"), isAuto(isAuto)
	{

	}
	void pressed(unsigned char key);
	virtual ~Character() {}
};

