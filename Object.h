#pragma once
//#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL
#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

#define WIDTH 4.f
#define DEPTH 8.f
#define HEIGHT 4.f

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
#include "SOIL.h"


using namespace std;

extern glm::vec4 modelColor;
extern glm::vec4 backgroundColor;

extern bool isLineRemoval;

extern GLint projectionMatrixLocation;
extern GLint modelViewMatrixLocation;
extern GLint isGouraudShadingLocation;
extern GLint isNoLightLocation;
extern GLint ambientProductLocation;
extern GLint diffuseProductLocation;
extern GLint specularProductLocation;
extern GLint lightPositionLocation;
extern GLint shininessLocation;

extern GLint vertexLocation;
extern GLint colorLocation;
extern GLint textureLocation;
extern GLint normalLocation;

extern GLuint verticesVBO;
extern GLuint indiciesVBO;
extern GLuint texturesVBO;
extern GLuint normalsVBO;

extern GLuint myProgramObj;


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
		GLfloat baisW = 0.5f, GLfloat baisH = 0.5f,
        bool collisionCheck = false, bool isSolid = false,
		glm::vec3 diffuseStrength = glm::vec3(0.7f),
		glm::vec3 specularStrength = glm::vec3(0.3f),
        GLfloat shininess = 32
        )
	: w(w), h(h), baisW(baisW), baisH(baisH), objPath(objPath),
	position(position), collisionCheck(collisionCheck), isSolid(isSolid),
	specularStrength(specularStrength), shininess(shininess)
	{
		translateOrigin(position);
		GLfloat minW = -w * baisW;
		GLfloat maxW = w * (1.f-baisW);
		GLfloat minH = -h * baisH;
		GLfloat maxH = h * (1.f - baisH);
		originPositions[0] = glm::vec4(0.f, 0.f, 0.f, 1.f);
		originPositions[1] = glm::vec4(minW, minH, 0.f, 1.f);
		originPositions[2] = glm::vec4(maxW, minH, 0.f, 1.f);
		originPositions[3] = glm::vec4(maxW, maxH, 0.f, 1.f);
		originPositions[4] = glm::vec4(minW, maxH, 0.f, 1.f);
		for (int i = 0; i < 5; i++) {
			finalPositions[i] = originPositions[i];
			windowPositions[i] = originPositions[i];
		}
		if (w > 0.f && h > 0.f && isnan(w) == 0 && isnan(h) == 0) {
			allNodes.push_back(this);
		}
    }
	~Object() {};
	GLuint VAO;
	GLuint texture;
	unsigned int getVertexCount()  { return (unsigned int)getVertices().size() ; }
	unsigned int getIndexCount()  { return (unsigned int)getIndices().size(); }
	unsigned int getTextureCount() { return (unsigned int)getTextures().size(); }
	unsigned int getNormalCount() { return (unsigned int)getNormals().size(); }
	unsigned int getVerticesSize()  { return (unsigned int)getVertices().size() * sizeof(GLfloat) * 3; }
	unsigned int getIndiciesSize()  { return (unsigned int)getIndices().size() * sizeof(unsigned int); }
	unsigned int getTexturesSize() { return (unsigned int)getTextures().size() * sizeof(GLfloat) * 2; }
	unsigned int getNormalsSize() { return (unsigned int)getNormals().size() * sizeof(GLfloat) * 3; }
	vector<glm::vec3> getVertices();
	vector<unsigned int > getIndices();
	vector<glm::vec2> getTextures();
	vector<glm::vec3> getNormals();

	void addVertex(glm::vec3 vertex) { vertices.push_back(vertex); };
	void addVertices(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
		addVertex(v1);
		addVertex(v2);
		addVertex(v3);
	}

	void addTexture(glm::vec2 t) { this->textures.push_back(t); }
	void addTextures(glm::vec2 t1, glm::vec2 t2, glm::vec2 t3) {
		addTexture(t1);
		addTexture(t2);
		addTexture(t3);
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
	bool loadTextureImage(string texturePath);

	glm::vec3 computeFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
	
	void init(unsigned* vertexOffset, unsigned* indexOffset, unsigned* textureOffset, unsigned* normalOffset);
	void initObject(unsigned* vertexOffset, unsigned* indexOffset, unsigned* textureOffset, unsigned* normalOffset);
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
    GLfloat finalLeft() { return glm::min(finalPositions[1].x, finalPositions[3].x); }
    GLfloat finalBottom() { return glm::min(finalPositions[2].y, finalPositions[4].y); }
    GLfloat finalRight() { return glm::max(finalPositions[1].x, finalPositions[3].x); }
    GLfloat finalTop() { return glm::max(finalPositions[2].y, finalPositions[4].y); }

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

	void setCoordinateMatrix(glm::mat4 matrix) { this->coordinateMatrix = matrix; }

	unsigned totalVerticesSize();
	unsigned totalIndicesSize();
	unsigned totalTexturesSize();
	unsigned totalNormalsSize();

protected:

	vector<glm::vec3> vertices;
	vector<unsigned int> indices;
	vector< glm::vec2 > textures;
	vector< glm::vec3 > normals;
    GLfloat w, h, baisW, baisH;
    glm::vec3 diffuseStrength;
    glm::vec3 specularStrength;
    GLfloat shininess;
	Object * parent = NULL;
	vector<Object *> children;
	string objPath;
	string texturePath;
    bool collisionCheck;
    bool isSolid;
	bool disableDraw = false;
	glm::vec3 position;
	glm::mat4 coordinateMatrix = glm::mat4(1.f);
	glm::mat4 windowMatrix = glm::mat4(1.f);
	glm::mat4 originMatrix = glm::mat4(1.f);
	glm::vec4 originPositions[5];
	glm::vec4 finalPositions[5];
	glm::vec4 windowPositions[5];

	virtual void drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix);
	virtual void moveObject() {}
	virtual void updatedCurrentTransformationMatrix() {}

};

