#include "Object.h"



void Object::init(unsigned *vertexOffset, unsigned *indexOffset) {
	//loadOBJ(objPath);
	cout << "Init " << *vertexOffset << *indexOffset << endl;
	initObject( vertexOffset,  indexOffset);
	*vertexOffset += getVerticesSize();
	*indexOffset += getIndiciesSize();
	if (children.size() != 0) {
		for (vector<Object *>::iterator it = children.begin(); it != children.end(); ++it) {
			(*it)->init(vertexOffset, indexOffset);
		}
	}
}

void Object::initObject(unsigned* vertexOffset, unsigned* indexOffset)
{
	if (vertices.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
		glBufferSubData(GL_ARRAY_BUFFER, *vertexOffset, getVerticesSize(), &getVertices()[0].x);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, *indexOffset, getIndiciesSize(), &getIndices()[0]);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
		glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(*vertexOffset));
		glEnableVertexAttribArray(vertexLocation);
		glBindVertexArray(0);
	}
}

bool Object::loadOBJ(string filename)
{
	FILE * file;
	errno_t err= fopen_s(&file, filename.c_str(), "r");

	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (true)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		if (res == EOF)
			break; 

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			addVertex(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {

		}
		else if (strcmp(lineHeader, "vn") == 0) {

		}
		else if (strcmp(lineHeader, "f") == 0) {

			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			addIndices(vertexIndex[0]-1, vertexIndex[1]-1, vertexIndex[2]-1);
		}
		else if (strcmp(lineHeader, "#") == 0)
		{
			/* ignoring this line */
		}
		else
		{
			/* ignoring this line */
		}
	}

	//for (int i = 0; i < getIndiciesSize(); i += 3)
	//{
	//	GLushort ia = indices[i];
	//	GLushort ib = indices[i + 1];
	//	GLushort ic = indices[i + 2];

	//	glm::vec3 n = computeFaceNormal(vertices[ia], vertices[ib], vertices[ic]);
	//	addNormals(n, n, n);
	//}

	cout << "Load Done !" << endl;

	return true;

}

glm::vec3 Object::computeFaceNormal( glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	const float EPSILON = 0.000001f;
	glm::vec3 n = glm::vec3(0.f, 0.f, 0.f);
	// default return value (0, 0, 0)

	// find 2 edge vectors: v1-v2, v1-v3
	GLfloat ex1 = v2.x - v1.x;
	GLfloat ey1 = v2.y - v1.y;
	GLfloat ez1 = v2.z - v1.z;
	GLfloat ex2 = v3.x - v1.x;
	GLfloat ey2 = v3.y - v1.y;
	GLfloat ez2 = v3.z - v1.z;

	// cross product: e1 x e2
	GLfloat nx, ny, nz;
	nx = ey1 * ez2 - ez1 * ey2;
	ny = ez1 * ex2 - ex1 * ez2;
	nz = ex1 * ey2 - ey1 * ex2;

	// normalize only if the length is > 0
	float length = sqrtf(nx * nx + ny * ny + nz * nz);
	if (length > EPSILON)
	{
		// normalize
		float lengthInv = 1.0f / length;
		n.x = nx * lengthInv;
		n.y = ny * lengthInv;
		n.z = nz * lengthInv;
	}

	return n;
}

void Object::draw(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix)
{
	windowMatrix = modelViewMatrix * originMatrix;
	for (int i = 0; i < 5; i++) {
		finalPositions[i] = originMatrix * originPositions[i];
		windowPositions[i] = windowMatrix * originPositions[i];
	}
	drawShader(projectionMatrix, windowMatrix);

	if (children.size() != 0) {
		for (vector<Object *>::iterator it = children.begin(); it != children.end(); ++it) {
			(*it)->draw(projectionMatrix, windowMatrix);
		}
	}
}

void Object::drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix) {
	ctm = projectionMatrix * modelViewMatrix ;
	glBindVertexArray(VAO);
	glUniformMatrix4fv(ctmLocation, 1, GL_FALSE, &ctm[0][0]);

	if (isLineRemoval) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glUniform4f(colorLocation, backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
		glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(colorLocation, modelColor[0], modelColor[1], modelColor[2], modelColor[3]);
		glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);

	}

	else {
		glUniform4f(colorLocation, modelColor[0], modelColor[1], modelColor[2], modelColor[3]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);





}

vector<glm::vec3> Object::getVertices() {
	return vertices;
}

vector<unsigned int >Object:: getIndices() {
	return indices;

}

void Object::move()
{
	moveObject();
	for (vector<Object *>::reverse_iterator it = children.rbegin(); it != children.rend(); ++it) {
		(*it)->move();
	}
	//while (doCollision()) {}
}

unsigned Object::totalVerticesSize()
{
	unsigned size = getVerticesSize();

	if (children.size() != 0) {
		for (vector<Object*>::iterator it = children.begin(); it != children.end(); ++it) {
			size += (*it)->totalVerticesSize();
		}
	}
	return size;

}

unsigned Object::totalIndicesSize()
{
	unsigned size = getIndiciesSize();

	if (children.size() != 0) {
		for (vector<Object*>::iterator it = children.begin(); it != children.end(); ++it) {
			size += (*it)->totalIndicesSize();
		}
	}
	return size;
}
