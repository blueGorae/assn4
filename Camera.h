#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;


class Camera
{
private :
	bool zoom_out = true;
	bool pressed = false;
	bool init = true;
    GLint cameraMode = 3;
    GLfloat cameraLocationX = -0.f;
    GLfloat cameraLocationY = -0.f;
public:
	Camera() {}
	void KeyboardFunc(unsigned char key, int x, int y);
	glm::mat4 ProjectionMatrix() {
		return glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 100.0f);
	}
    glm::mat4 ModelViewMatrix() {
        switch (cameraMode) {
        case 1:
        case 2:
        case 3:
            return glm::lookAt(
				glm::vec3(cameraLocationX, cameraLocationY, 3),
                glm::vec3(0.f, 0.f, 0.f),
                glm::vec3(0, 1, 0)
			);
        }
		return glm::mat4(1.f);
    }
	virtual ~Camera(){}
};

