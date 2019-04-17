#include "Sphere.h"



Sphere::Sphere(GLfloat radius, GLint subdivision)
{
	this->radius = radius;
	this->subdivision = subdivision;
	buildVerticesFlat();

}


Sphere::~Sphere()
{
}

vector<vec3> Sphere::computeIcosahedronVertices()
{
	const GLfloat H_ANGLE = M_PI / 180 * 72;    // 72 degree = 360 / 5
	const GLfloat V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree

	vector<vec3> vertices(12);    // 12 vertices
	int i1, i2;                             // indices
	GLfloat z, xy;                            // coords
	GLfloat hAngle1 = -M_PI / 2 - H_ANGLE / 2;  // start from -126 deg at 2nd row
	GLfloat hAngle2 = -M_PI / 2;                // start from -90 deg at 3rd row

	// the first top vertex (0, 0, r)
	vertices[0] = vec3(0.f, 0.f, this->radius);

	// 10 vertices at 2nd and 3rd rows
	for (int i = 1; i <= 5; ++i)
	{
		i1 = i;         // for 2nd row
		i2 = (i + 5);   // for 3rd row

		z = radius * sinf(V_ANGLE);              // elevaton
		xy = radius * cosf(V_ANGLE);

		vertices[i1] = vec3(xy * cosf(hAngle1), xy * sinf(hAngle1), z);
		vertices[i2] = vec3(xy * cosf(hAngle2), xy * sinf(hAngle2), -z);

		// next horizontal angles
		hAngle1 += H_ANGLE;
		hAngle2 += H_ANGLE;
	}

	// the last bottom vertex (0, 0, -r)
	vertices[11] = vec3(0.f, 0.f, -radius);

	return vector<vec3>(vertices);
}

void Sphere::buildVerticesFlat() {
	//const float S_STEP = 1 / 11.0f;         // horizontal texture step
	//const float T_STEP = 1 / 3.0f;          // vertical texture step
	const float S_STEP = 186 / 2048.0f;     // horizontal texture step
	const float T_STEP = 322 / 1024.0f;     // vertical texture step

	// compute 12 vertices of icosahedron
	vector<vec3> tmpVertices = computeIcosahedronVertices(); 

	// clear memory of prev arrays
	vector<vec3>().swap(vertices);
	vector<unsigned int>().swap(indices);

	vec3 v0, v1, v2, v3, v4, v11;          // vertex positions
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


		// add a triangle in 1st row
		addVertices(v0, v1, v2);
		addIndices(index, index + 1, index + 2 );

		// add 2 triangles in 2nd row
		addVertices(v1, v3, v2);
		addIndices(index + 3, index + 4, index + 5);

		addVertices(v2, v3, v4);
		addIndices(index + 6, index + 7, index + 8);

		// add a triangle in 3rd row
		addVertices(v3, v11, v4);
		addIndices(index + 9, index + 10, index + 11);

		// next index
		index += 12;
	}

	// subdivide icosahedron
	//subdivideVerticesFlat();

	// generate interleaved vertex array as well
	//buildInterleavedVertices();
}
