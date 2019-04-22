#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include "glm/glm.hpp"
#include "GL/glut.h"


using namespace std;

class Object
{
public:
	Object();
	~Object();

	unsigned int getVertexCount()  { return (unsigned int)getVertices().size() ; }
	unsigned int getIndexCount()  { return (unsigned int)getIndices().size(); }
	unsigned int getVerticesSize()  { return (unsigned int)getVertices().size() * sizeof(GLfloat) * 3; }
	unsigned int getIndiciesSize()  { return (unsigned int)getIndices().size() * sizeof(unsigned int); }

	vector<glm::vec3> getVertices();
	vector<unsigned int > getIndices();
	void addVertex(glm::vec3 vertex) { vertices.push_back(vertex); };
	void addVertices(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
		addVertex(v1);
		addVertex(v2);
		addVertex(v3);
	}

	void addNormal(glm::vec3 n) { this->normals.push_back(n); }
	void addNormals(glm::vec3 n1, glm::vec3 n2, glm::vec3 n3) {
		addNormal(n1);
		addNormal(n2);
		addNormal(n3);
	}

	void addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
	{
		indices.push_back(i1);
		indices.push_back(i2);
		indices.push_back(i3);
	}

	glm::vec3 getPosition() { return glm::vec3(posX, posY, posZ); }

	void setParent(Object * parent) { this->parent = parent; }
	Object * getParent() { return this->parent; }

	void addChild(Object * child) { this->children.push_back(child); }
	vector <Object *> getChildren() { return this->children; }

	bool loadOBJ(string path);

	glm::vec3 computeFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
	
	void init();
	void draw(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix);

	void setOriginalMatrix(glm::mat4 matrix) { this->originMatrix = matrix; }
	glm::mat4 getOriginalMatrix() { return originMatrix; }

protected:
	vector<glm::vec3> vertices;
	vector<unsigned int> indices;
	vector< glm::vec2 > uvs;
	vector< glm::vec3 > normals;

	GLfloat posX = 0.f, posY = 0.f, posZ = 0.f;

	Object * parent = NULL;
	vector<Object *> children;
    glm::mat4 originMatrix = glm::mat4(1.f);

    virtual void drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix) {}
};

