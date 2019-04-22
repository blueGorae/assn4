#pragma once
#include "SceneGraph.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class Camera
{
private :
	bool zoom_out = true;
	bool pressed = false;
	bool init = true;
    GLint cameraMode = 3;
    GLfloat cameraLocationX = -0.5f;
    GLfloat cameraLocationY = -0.5f;
public:
	Camera() {}
	void KeyboardFunc(unsigned char key, int x, int y);
	glm::mat4 ProjectionMatrix() {
	    return glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 100.0f);
	}
    glm::mat4 ModelViewMatrix() {
        switch (cameraMode) {
        case 1:
            // ĳ���� 1��Ī
        case 2:
            // ĳ���� 3��Ī
        case 3:
            return glm::lookAt(
                    glm::vec3(cameraLocationX, cameraLocationY, 2),
                    glm::vec3(0.f, 0.f, 0.f),
                    glm::vec3(0, 1, 0)
            );
        }
    }
	virtual ~Camera(){}
};

