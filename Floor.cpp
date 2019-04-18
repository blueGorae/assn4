#include "Floor.h"



Floor::~Floor()
{
}

void Floor::buildVertices()
{
	for (int i = 0; i <= width; i++) {
		for (int j = 0; j <= depth; j++) {
			addVertices(vec3(float(i)/10.f, float(j)/10.f, 0.f), vec3(float(i + 1)/10.f, float(j)/10.f, 0.f), vec3(float(i)/10.f, float(j + 1)/10.f, 0.f));
		}
	}
	int index = 0;
	int i1, i2, i3, i4;
	vector<vec3> vertices = getVertices();
	int stride = depth+1;
	int maxIndex = width * (depth+1);

	while (index < maxIndex) {
		for (int i = 0; i < depth; i++) {
			i1 = index + i;
			i2 = index + i + 1;
			i3 = index + i + stride;
			i4 = index + i + stride + 1;
			addIndices(i1, i2, i3);
			addIndices(i2, i3, i4);
		}
		index += stride;
	}
	
}

