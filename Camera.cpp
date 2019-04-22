#include "Camera.h"
#include <iostream>

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
            cameraLocationY = glm::min(cameraLocationY + 0.01f, 0.f);
            break;
        case 'J':
        case 'j':
            cameraLocationX = glm::max(cameraLocationX - 0.01f, -1.f);
            break;
        case 'K':
        case 'k':
            cameraLocationY = glm::max(cameraLocationY - 0.01f, -1.f);
            break;
        case 'L':
        case 'l':
            cameraLocationX = glm::min(cameraLocationX + 0.01f, 1.f);
            break;
    }
}

