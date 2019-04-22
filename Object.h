#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include "GL/glew.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "GL/freeglut.h"
#include "GL/glut.h"


using namespace std;

extern GLuint myProgramObj;

extern GLint ctmLocation;

extern GLint vertexLocation;

extern GLuint verticesVBO;
extern GLuint indiciesVBO;

extern GLuint ballVAO;
extern GLuint backgroundVAO;


class Object
{
public:
	Object();
	Object(glm::vec3 position) : position(position)
	{

	}
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
	
	void init(unsigned vertexOffset, unsigned indexOffset);
	virtual void initObject(unsigned vertexOffset, unsigned indexOffset);
	void draw(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix);
	void move();
	void translateOrigin(GLfloat x, GLfloat y) {
		originMatrix = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0.f)) * originMatrix;
	}
	void rotateOrigin(GLfloat angle) {
		originMatrix = glm::rotate(glm::mat4(1.f), angle, glm::vec3(0.f, 0.f, 1.f)) * originMatrix;
	}

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
	glm::vec3 position;
    glm::mat4 originMatrix = glm::mat4(1.f);

	virtual void localInit() {}
	virtual void drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix) {}
	virtual void moveObject() {}
};

