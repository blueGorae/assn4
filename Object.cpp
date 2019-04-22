#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
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
			vec3 v; s >> v.x; s >> v.y; s >> v.z;
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

		vec3 n = computeFaceNormal(vertices[ia], vertices[ib], vertices[ic]);
		addNormals(n, n, n);
	}

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

void Object::draw() {

}
