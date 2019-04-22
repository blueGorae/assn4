#include "Plane.h"



Plane::~Plane()
{
}

void Plane::buildVertices()
{
	vec3 v1, v2, v3;
	vec3 n;
	int index = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			v1 = vec3(float(i) / 10.f, float(j) / 10.f, 0.f);
			v2 = vec3(float(i + 1) / 10.f, float(j) / 10.f, 0.f);
			v3 = vec3(float(i) / 10.f, float(j + 1) / 10.f, 0.f);
			addVertices( v1, v2, v3);
			n = computeFaceNormal(v1, v2, v3);
			addNormals(n, n, n);
			addIndices(index, index + 1, index + 2);
			index += 3;
			if ((i == width - 1) || (j == depth - 1)) {
				v1 = vec3(float(i + 1) / 10.f, float(j) / 10.f, 0.f);
				v2 = vec3(float(i) / 10.f, float(j + 1) / 10.f, 0.f);
				v3 = vec3(float(i + 1) / 10.f, float(j + 1) / 10.f, 0.f);
				addVertices(v1, v2, v3);
				n = computeFaceNormal(v1, v2, v3);
				addNormals(n, n, n);
				addIndices( index + 1, index+2, index+2+ 3);
				index += 3;
			}

		}
	}
}

