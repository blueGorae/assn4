#include "Floor.h"



Floor::~Floor()
{
}

void Floor::buildVertices()
{
	int index = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			addVertices(vec3(float(i)/10.f, float(j)/10.f, 0.f), vec3(float(i + 1)/10.f, float(j)/10.f, 0.f), vec3(float(i)/10.f, float(j + 1)/10.f, 0.f));
			addIndices(index, index+1, index+2);
			index++;
		}
	}

}

