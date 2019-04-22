#include "Plane.h"



Plane::~Plane()
{
}

void Plane::buildVertices()
{
	glm::vec3 v1, v2, v3;
	glm::vec3 n;
	int index = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			v1 = glm::vec3(float(i) / 10.f, float(j) / 10.f, 0.f);
			v2 = glm::vec3(float(i + 1) / 10.f, float(j) / 10.f, 0.f);
			v3 = glm::vec3(float(i) / 10.f, float(j + 1) / 10.f, 0.f);
			addVertices( v1, v2, v3);
			n = computeFaceNormal(v1, v2, v3);
			addNormals(n, n, n);
			addIndices(index, index + 1, index + 2);
			index += 3;
			if ((i == width - 1) || (j == depth - 1)) {
				v1 = glm::vec3(float(i + 1) / 10.f, float(j) / 10.f, 0.f);
				v2 = glm::vec3(float(i) / 10.f, float(j + 1) / 10.f, 0.f);
				v3 = glm::vec3(float(i + 1) / 10.f, float(j + 1) / 10.f, 0.f);
				addVertices(v1, v2, v3);
				n = computeFaceNormal(v1, v2, v3);
				addNormals(n, n, n);
				addIndices( index + 1, index+2, index+2+ 3);
				index += 3;
			}

		}
	}
}

void Plane::drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix) {
	glm::mat4 ctm = projectionMatrix * modelViewMatrix * originMatrix;
	glBindVertexArray(VAO);
	glUniformMatrix4fv(ctmLocation, 1, GL_TRUE, &ctm[0][0]);
	glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
}
