#include "Camera.h"
#include <iostream>

GLint cameraMode = 3;

void Camera::KeyboardFunc(unsigned char key, int x, int y)
{
    switch (key) {
        case '1':
            cameraMode = 1;
            break;
        case '2':
            cameraMode = 2;
            break;
        case '3':
            cameraMode = 3;
            break;
        case 'I':
        case 'i':
			if (cameraMode != 3) {
				break;
			}
            cameraLocationY = glm::min(cameraLocationY + 0.05f, 0.f);
            break;
        case 'J':
        case 'j':
			if (cameraMode != 3) {
				break;
			}
			cameraLocationX = glm::max(cameraLocationX - 0.05f, -WIDTH / 2);
            break;
        case 'K':
        case 'k':
			if (cameraMode != 3) {
				break;
			}
			cameraLocationY = glm::max(cameraLocationY - 0.05f, -DEPTH / 2);
            break;
        case 'L':
        case 'l':
			if (cameraMode != 3) {
				break;
			}
			cameraLocationX = glm::min(cameraLocationX + 0.05f, WIDTH / 2);
            break;
    }
}

