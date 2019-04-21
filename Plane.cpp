#include "Plane.h"



Plane::~Plane()
{
}

void Plane::buildVertices()
{
	int index = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			addVertices(vec3(float(i) / 10.f, float(j) / 10.f, 0.f), vec3(float(i + 1) / 10.f, float(j) / 10.f, 0.f), vec3(float(i) / 10.f, float(j + 1) / 10.f, 0.f));
			addIndices(index, index + 1, index + 2);
			index += 3;
			if ((i == width -1) || (j == depth - 1)) {
				addVertices(vec3(float(i+1) / 10.f, float(j) / 10.f, 0.f), vec3(float(i) / 10.f, float(j+1) / 10.f, 0.f), vec3(float(i+1) / 10.f, float(j + 1) / 10.f, 0.f));
				addIndices( index + 1, index+2, index+2+ 3);
				index += 3;
			}

		}
	}
}

