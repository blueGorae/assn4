#include "Plane.h"



Plane::~Plane()
{
}

void Plane::buildVertices()
{
	glm::vec3 v1, v2, v3, v4;
	glm::vec3 n;
	int index = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			v1 = glm::vec3(float(i) , float(j) , 0.f);
			v2 = glm::vec3(float(i + 1) , float(j) , 0.f);
			v3 = glm::vec3(float(i) , float(j + 1) , 0.f);
			v4 = glm::vec3(float(i + 1), float(j + 1), 0.f);

			addVertices( v1, v2, v3);
			addVertices(v2, v3, v4);
			n = computeFaceNormal(v1, v2, v3);
			addNormals(n, n, n);

			n = computeFaceNormal(v2, v3, v4);
			addNormals(n, n, n);

			addIndices(index, index + 1, index + 2);
			addIndices(index + 1, index + 2, index + 3);
			index += 3;
			//if ((i == width - 1) || (j == depth - 1)) {
			//	v1 = glm::vec3(float(i + 1) , float(j) , 0.f);
			//	v2 = glm::vec3(float(i) , float(j + 1) , 0.f);
			//	v3 = glm::vec3(float(i + 1) , float(j + 1) , 0.f);
			//	addVertices(v1, v2, v3);
			//	n = computeFaceNormal(v1, v2, v3);
			//	addNormals(n, n, n);
			//	addIndices( index + 1, index+2, index+2+ 3);
			//	index += 3;
			//}

		}
	}
}
