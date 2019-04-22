#include "Sphere.h"



Sphere::Sphere(GLfloat radius, GLint subdivision, glm::vec3 position)
{
	this->radius = radius;
	this->subdivision = subdivision;
	this->posX = position.x;
	this->posY = position.y;
	this->posZ = position.z;

	buildVerticesFlat();

}


Sphere::~Sphere()
{
}

void Sphere::drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix)
{
	glm::mat4 ctm = projectionMatrix * modelViewMatrix * originMatrix;
	glBindVertexArray(ballVAO);
	glUniformMatrix4fv(ctmLocation, 1, GL_TRUE, &ctm[0][0]);
	glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
}

vector<glm::vec3> Sphere::computeIcosahedronVertices()
{
	const GLfloat H_ANGLE = M_PI / 180 * 72;    // 72 degree = 360 / 5
	const GLfloat V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree

	vector<glm::vec3> vertices(12);    // 12 vertices
	int i1, i2;                             // indices
	GLfloat z, xy;                            // coords
	GLfloat hAngle1 = -M_PI / 2 - H_ANGLE / 2;  // start from -126 deg at 2nd row
	GLfloat hAngle2 = -M_PI / 2;                // start from -90 deg at 3rd row

	// the first top vertex (0, 0, r)
	vertices[0] = glm::vec3(0.f, 0.f, this->radius);

	// 10 vertices at 2nd and 3rd rows
	for (int i = 1; i <= 5; ++i)
	{
		i1 = i;         // for 2nd row
		i2 = (i + 5);   // for 3rd row

		z = radius * sinf(V_ANGLE);              // elevaton
		xy = radius * cosf(V_ANGLE);

		vertices[i1] = glm::vec3(xy * cosf(hAngle1), xy * sinf(hAngle1), z);
		vertices[i2] = glm::vec3(xy * cosf(hAngle2), xy * sinf(hAngle2), -z);

		// next horizontal angles
		hAngle1 += H_ANGLE;
		hAngle2 += H_ANGLE;
	}

	// the last bottom vertex (0, 0, -r)
	vertices[11] = glm::vec3(0.f, 0.f, -radius);

	return vector<glm::vec3>(vertices);
}

void Sphere::buildVerticesFlat() {

	// compute 12 vertices of icosahedron
	vector<glm::vec3> tmpVertices = computeIcosahedronVertices(); 

	// clear memory of prev arrays
	vector<glm::vec3>().swap(vertices);
	vector<unsigned int>().swap(indices);

	glm::vec3 v0, v1, v2, v3, v4, v11;          // vertex positions
	unsigned int index = 0;

	// compute and add 20 tiangles of icosahedron first
	v0 = tmpVertices[0];       // 1st vertex
	v11 = tmpVertices[11]; // 12th vertex

	for (int i = 1; i <= 5; ++i)
	{
		// 4 vertices in the 2nd row
		v1 = tmpVertices[i];
		if (i < 5)
			v2 = tmpVertices[i + 1];
		else
			v2 = tmpVertices[1];

		v3 = tmpVertices[i + 5];
		if ((i + 5) < 10)
			v4 = tmpVertices[i + 6];
		else
			v4 = tmpVertices[6];

		glm::vec3 n;

		// add a triangle in 1st row
		addVertices(v0, v1, v2);
		n = computeFaceNormal(v0, v1, v2);
		addNormals(n, n, n);
		addIndices(index, index + 1, index + 2 );

		// add 2 triangles in 2nd row
		addVertices(v1, v3, v2);
		n = computeFaceNormal(v1, v3, v2);
		addNormals(n, n, n);
		addIndices(index + 3, index + 4, index + 5);

		addVertices(v2, v3, v4);
		n = computeFaceNormal(v2, v3, v4);
		addNormals(n, n, n);
		addIndices(index + 6, index + 7, index + 8);

		// add a triangle in 3rd row
		addVertices(v3, v11, v4);
		n = computeFaceNormal(v3, v11, v4);
		addNormals(n, n, n);
		addIndices(index + 9, index + 10, index + 11);

		// next index
		index += 12;
	}

	// subdivide icosahedron
	subdivideVerticesFlat();

	// generate interleaved vertex array as well
	//buildInterleavedVertices();
}

void Sphere::subdivideVerticesFlat(){
	vector<glm::vec3> tmpVertices;
	vector<unsigned int> tmpIndices;

	int indexCount;

	glm::vec3 v1, v2, v3;          // ptr to original vertices of a triangle
	glm::vec3 newV1, newV2, newV3; // new vertex positions

	unsigned int index = 0;             // new index value
	int i, j;

	// iteration
	for (i = 1; i <= subdivision; ++i)
	{
		// copy prev arrays
		tmpVertices = vertices;
		tmpIndices = indices;

		// clear prev arrays
		vertices.clear();
		indices.clear();

		index = 0;
		indexCount = (int)tmpIndices.size();

		for (j = 0; j < indexCount; j += 3)
		{
			// get 3 vertice and texcoords of a triangle
			v1 = tmpVertices[tmpIndices[j]];
			v2 = tmpVertices[tmpIndices[j + 1]];
			v3 = tmpVertices[tmpIndices[j + 2]];

			// get 3 new vertices by spliting half on each edge
			newV1 = computeHalfVertex(v1, v2, radius);
			newV2 = computeHalfVertex(v2, v3, radius);
			newV3 = computeHalfVertex(v1, v3, radius);

			glm::vec3 n;
			// add 4 new triangles
			addVertices(v1, newV1, newV3);
			n = computeFaceNormal(v1, newV1, newV3);
			addNormals(n, n, n);
			addIndices(index, index + 1, index + 2);

			addVertices(newV1, v2, newV2);
			n = computeFaceNormal(newV1, v2, newV2);
			addNormals(n, n, n);
			addIndices(index + 3, index + 4, index + 5);

			addVertices(newV1, newV2, newV3);
			n = computeFaceNormal(newV1, newV2, newV3);
			addNormals(n, n, n);
			addIndices(index + 6, index + 7, index + 8);

			addVertices(newV3, newV2, v3);
			n = computeFaceNormal(newV3, newV2, v3);
			addNormals(n, n, n);
			addIndices(index + 9, index + 10, index + 11);

			// next index
			index += 12;
		}
	}
}

glm::vec3 Sphere::computeHalfVertex( glm::vec3 v1, glm::vec3 v2, float length)
{
	glm::vec3 newV;
	newV.x = v1[0] + v2[0];
	newV.y = v1[1] + v2[1];
	newV.z = v1[2] + v2[2];
	float scale = computeScaleForLength(newV, length);
	newV.x *= scale;
	newV.y *= scale;
	newV.z *= scale;

	return newV;
}

float Sphere::computeScaleForLength(glm::vec3 v, float length)
{
	// and normalize the vector then re-scale to new radius
	return length / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
