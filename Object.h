#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

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

extern glm::vec4 modelColor;
extern glm::vec4 backgroundColor;

extern glm::mat4 ctm;
extern bool isLineRemoval;

extern GLint ctmLocation;

extern GLint vertexLocation;
extern GLint colorLocation;

extern GLuint verticesVBO;
extern GLuint indiciesVBO;

struct Collision {
    bool occur;
    GLfloat overlapX;
    GLfloat overlapY;
};
class Object;

extern vector<Object*> allNodes;

class Object
{
public:
	Object(
        glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
        string objPath = "",
        GLfloat w = 0.f, GLfloat h = 0.f,
        bool collisionCheck = false, bool isSolid = false
        )
	: w(w), h(h), objPath(objPath), position(position), collisionCheck(collisionCheck), isSolid(isSolid)
	{
		translateOrigin(position);
		GLfloat w_2 = w * 0.5f;
		GLfloat h_2 = h * 0.5f;
		originPositions[0] = glm::vec4(position, 1.f);
		originPositions[1] = glm::vec4(-w_2, -h_2, 0.f, 1.f);
		originPositions[2] = glm::vec4(+w_2, -h_2, 0.f, 1.f);
		originPositions[3] = glm::vec4(+w_2, +h_2, 0.f, 1.f);
		originPositions[4] = glm::vec4(-w_2, +h_2, 0.f, 1.f);
		for (int i = 0; i < 5; i++) {
			finalPositions[i] = originPositions[i];
			windowPositions[i] = originPositions[i];
		}
        allNodes.push_back(this);
    }
	~Object() {};
	GLuint VAO;

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

	void setParent(Object * parent) { this->parent = parent; }
	Object * getParent() { return this->parent; }

	void addChild(Object * child) {
	    this->children.push_back(child);
	    child->setParent(this);
	}
	vector <Object *> getChildren() { return this->children; }

	bool loadOBJ(string path);

	glm::vec3 computeFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
	
	void init(unsigned* vertexOffset, unsigned* indexOffset);
	void initObject(unsigned* vertexOffset, unsigned* indexOffset);
	void draw(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix);
	void move();
    virtual bool checkCollision();
    virtual void resetPosition() {};
	virtual void reset();
    virtual bool criticalCollisionAction(Object* from) { return false; }
    bool skipCollision(Object* node);
    void updateCurrentTransformationMatrix();
    virtual bool doCollision();
    virtual Object* actionCollision(Collision* collision) {
        if (parent)
            return parent->actionCollision(collision);
        else
            return this;
    }
    GLfloat windowLeft() { return windowPositions[0].x - w * .5f; }
    GLfloat windowBottom() { return windowPositions[0].y - h * .5f; }
    GLfloat windowRight() { return windowPositions[0].x + w * .5f; }
    GLfloat windowTop() { return windowPositions[0].y + h * .5f; }

	void translateOrigin(GLfloat x, GLfloat y) {
		translateOrigin(x, y, 0);
	}
	void translateOrigin(GLfloat x, GLfloat y, GLfloat z) {
		translateOrigin(glm::vec3(x, y, z));
	}
	void translateOrigin(glm::vec3 translate) {
		originMatrix = glm::translate(glm::mat4(1.f), translate) * originMatrix;
	}
	void rotateOrigin(GLfloat angle) {
		rotateOrigin(angle, glm::vec3(0.f, 0.f, 1.f));
	}
	void rotateOrigin(GLfloat angle, glm::vec3 pivot) {
		originMatrix = glm::rotate(glm::mat4(1.f), angle, pivot) * originMatrix;
	}

	void setOriginalMatrix(glm::mat4 matrix) { this->originMatrix = matrix; }
	glm::mat4 getOriginalMatrix() { return originMatrix; }

	unsigned totalVerticesSize();
	unsigned totalIndicesSize();

protected:

	vector<glm::vec3> vertices;
	vector<unsigned int> indices;
	vector< glm::vec2 > uvs;
	vector< glm::vec3 > normals;
    GLfloat w, h;
	Object * parent = NULL;
	vector<Object *> children;
	string objPath;
    bool collisionCheck;
    bool isSolid;
	glm::vec3 position;
	glm::mat4 windowMatrix = glm::mat4(1.f);
	glm::mat4 originMatrix = glm::mat4(1.f);
	glm::vec4 originPositions[5];
	glm::vec4 finalPositions[5];
	glm::vec4 windowPositions[5];

	virtual void drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix);
	virtual void moveObject() {}
};

