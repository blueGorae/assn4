#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
using namespace std;

void renderScene(void) { 
	glClear(GL_COLOR_BUFFER_BIT); 
	glFlush(); 
} 

void main(int argc, char **argv) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
	glutInitWindowPosition(100, 100);  
	glutInitWindowSize(320, 320); 
	glutCreateWindow("Hello OpenGL"); 
	glutDisplayFunc(renderScene);  
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);  
	glewInit();  
	glutMainLoop();
}
