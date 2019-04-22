#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

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
	ifstream in(filename, ios::in);
	if (!in)
	{
		cout << "Cannot open " << filename << endl;
	}

	string line;
	while (getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			istringstream s(line.substr(2));
			glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
			addVertex(v);
		}
		else if (line.substr(0, 2) == "vt") {

		}
		
		else if (line.substr(0, 2) == "f ")
		{
			istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a; s >> b; s >> c;
			a--; b--; c--;
			addIndices(a, b, c);
		}
		else if (line[0] == '#')
		{
			/* ignoring this line */
		}
		else
		{
			/* ignoring this line */
		}
	}

	for (int i = 0; i < getIndiciesSize(); i += 3)
	{
		GLushort ia = indices[i];
		GLushort ib = indices[i + 1];
		GLushort ic = indices[i + 2];

		glm::vec3 n = computeFaceNormal(vertices[ia], vertices[ib], vertices[ic]);
		addNormals(n, n, n);
	}

	return false;

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
    drawShader(projectionMatrix, modelViewMatrix);

    glm::mat4 childModelViewMatrix = modelViewMatrix * originMatrix;
	if (children.size() != 0) {
		for (vector<Object *>::iterator it = children.begin(); it != children.end(); ++it) {
			(*it)->draw(projectionMatrix, childModelViewMatrix);
		}
	}
}

void Object::drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix) {
	ctm = projectionMatrix * modelViewMatrix * originMatrix;
	glBindVertexArray(VAO);
	glUniformMatrix4fv(ctmLocation, 1, GL_TRUE, &ctm[0][0]);
	glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
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
