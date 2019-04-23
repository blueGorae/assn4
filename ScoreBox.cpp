#include "ScoreBox.h"
#include <string>
#include <iostream>

void ScoreBox::draw()
{
	string score_str = to_string(this->score);
	unsigned char * score_ustr = new unsigned char[score_str.length()+1];
	strcpy_s((char *)score_ustr, sizeof(score_str.c_str()), score_str.c_str());
	
	unsigned length = glutBitmapLength(GLUT_BITMAP_9_BY_15, score_ustr);
	
	glColor3f(1.f, 1.f, 1.f);
	
	glRasterPos2f(this->x, this->y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)score_str.data()[i]);
	}

	
}
