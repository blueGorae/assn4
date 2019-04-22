#include "Background.h"



Background::~Background()
{
}

void Background::drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix)
{
	glm::mat4 ctm = projectionMatrix * modelViewMatrix * originMatrix;
	glBindVertexArray(backgroundVAO);
	glUniformMatrix4fv(ctmLocation, 1, GL_TRUE, &ctm[0][0]);
	glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
}
