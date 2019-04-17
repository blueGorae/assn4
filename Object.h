#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include "GL/freeglut.h"
#include "GL/glut.h"
#include "glm/glm.hpp"

using namespace glm;
using namespace std;

class Object
{
public:
	Object();
	~Object();

	unsigned int getVertexCount() const { return (unsigned int)vertices.size() ; }
	unsigned int getIndexCount() const { return (unsigned int)indices.size() * 3; }
	unsigned int getVerticesSize() const { return (unsigned int)vertices.size() * sizeof(vec3); }
	unsigned int getIndiciesSize() const { return (unsigned int)indices.size() * sizeof(unsigned int) * 3; }

	const vector<vec3> getVertices() const { return vertices; }
	const vector<unsigned int > getIndices() const { return indices; }
	void addVertex(vec3 vertex) { vertices.push_back(vertex); };
	void addVertices(vec3 v1, vec3 v2, vec3 v3) { 
		addVertex(v1);
		addVertex(v2);
		addVertex(v3);
	}

	void addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
	{
		indices.push_back(i1);
		indices.push_back(i2);
		indices.push_back(i3);
	}

protected:
	vector<vec3> vertices;
	vector<unsigned int> indices;

};

