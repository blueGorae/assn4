#pragma once
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GL/glut.h"
#include <string>

extern const unsigned endScore;
using namespace std;

class ScoreBox 
{
private :
	GLfloat x, y;
	int score = 0;
public:
	ScoreBox(GLfloat x = 0.f, GLfloat y = 0.f){
		this->x = x;
		this->y = y;
	}

	virtual void draw();

	virtual void resetPosition() { this->score = 0; };

	void addScore() {
		score += 1;
	}


	int getScore() { return score; };
	virtual ~ScoreBox() {}
};