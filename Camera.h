#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include "Object.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

extern glm::vec3 player1Location;
extern glm::vec3 player3Location;
extern glm::vec3 playerDirection;
extern GLint cameraMode;

class Camera
{
private :
	bool zoom_out = true;
	bool pressed = false;
	bool init = true;
    GLfloat cameraLocationX = -0.f;
    GLfloat cameraLocationY = -DEPTH / 2;
public:
	Camera() {}
	void KeyboardFunc(unsigned char key, int x, int y);
	glm::mat4 ProjectionMatrix() {
		return glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 100.0f);
	}
    glm::mat4 ModelViewMatrix() {
        switch (cameraMode) {
        case 1:
			return glm::lookAt(
				player1Location,
				playerDirection,
				glm::vec3(0, 0, 1)
			);
        case 2:
			return glm::lookAt(
				player3Location,
				playerDirection,
				glm::vec3(0, 0, 1)
			);
        case 3:
            return glm::lookAt(
				glm::vec3(cameraLocationX, cameraLocationY, 2 * HEIGHT),
                glm::vec3(0.f, 0.f, 0.f),
                glm::vec3(0, 1, 0)
			);
        }
		return glm::mat4(1.f);
    }
	virtual ~Camera(){}
};

