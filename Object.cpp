#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

bool Object::loadOBJ(string path)
{
	//vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	//vector< vec3 > temp_vertices;
	//vector< vec2 > temp_uvs;
	//vector< vec3 > temp_normals;

	//FILE * file = fopen(path.c_str(), "r");
	//if (file == NULL) {
	//	printf("Impossible to open the file !\n");
	//	return false;
	//}
	//while (1) {

	//	char lineHeader[128];
	//	// read the first word of the line
	//	int res = fscanf(file, "%s", lineHeader);
	//	if (res == EOF)
	//		break; // EOF = End Of File. Quit the loop.
	//	// else : parse lineHeader
	return false;

}


vec3 Object::computeFaceNormal( vec3 v1, vec3 v2, vec3 v3)
{
	const float EPSILON = 0.000001f;
	vec3 n = (0.f, 0.f, 0.f);
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

