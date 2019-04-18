#include "Floor.h"



Floor::~Floor()
{
}

void Floor::buildVertices()
{
	for (int i = 0; i <= width; i++) {
		for (int j = 0; j <= depth; j++) {
			addVertices(vec3(float(i), float(j), 0.f), vec3(float(i + 1), float(j), 0.f), vec3(float(i), float(j + 1), 0.f));
		}
	}	
}

