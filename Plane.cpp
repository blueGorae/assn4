#include "Plane.h"



Plane::~Plane()
{
}

void Plane::buildVertices()
{
	glm::vec3 v1, v2, v3, v4;
	glm::vec2 t1, t2, t3, t4;

	glm::vec3 n;
	unsigned int index = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			v1 = glm::vec3(float(i) , float(j) , 0.f);
			v2 = glm::vec3(float(i + 1) , float(j) , 0.f);
			v3 = glm::vec3(float(i) , float(j + 1) , 0.f);
			v4 = glm::vec3(float(i + 1), float(j + 1), 0.f);

			t1 = glm::vec2(float(i) / float(width - 1), float(j) / float(depth - 1));
			t2 = glm::vec2(float(i+1) / float(width - 1), float(j) / float(depth - 1));
			t3 = glm::vec2(float(i) / float(width - 1), float(j+1) / float(depth - 1));
			t4 = glm::vec2(float(i+1) / float(width - 1), float(j+1) / float(depth - 1));

			addVertices( v1, v2, v3);
			addVertices(v2, v3, v4);

			addTextures(t1, t2, t3);
			addTextures(t2, t3, t4);

			n = computeFaceNormal(v1, v2, v3);
			addNormals(n, n, n);
			n = computeFaceNormal(v2, v3, v4);
			addNormals(n, n, n);

			addIndices(index, index + 1, index + 2);
			addIndices(index + 3, index + 4, index + 5);
			index += 6;

		}
	}

}
