#include "Object.h"



void Object::init(unsigned *vertexOffset, unsigned *indexOffset) {

	if (vertices.size() != 0) {
		initObject(vertexOffset, indexOffset);
		*vertexOffset += getVerticesSize();
		*indexOffset += getIndiciesSize();
		cout << "Init " << *vertexOffset << " " << *indexOffset << endl;
	}
	if (children.size() != 0) {
		for (vector<Object *>::iterator it = children.begin(); it != children.end(); ++it) {
			(*it)->init(vertexOffset, indexOffset);
		}
	}
}

void Object::initObject(unsigned* vertexOffset, unsigned* indexOffset)
{
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

bool Object::loadOBJ(string filename)
{
	FILE * file;
	errno_t err= fopen_s(&file, filename.c_str(), "r");

	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	vector<glm::vec3> temp_vertices;
	vector<glm::vec2> temp_textures;
	vector<glm::vec3> temp_normals;

	vector<unsigned int> temp_indices;
	vector<unsigned int> temp_texture_indices;
	vector<unsigned int> temp_normal_indices;

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
			temp_vertices.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 texture;
			fscanf_s(file, "%f %f\n", &texture.x, &texture.y);
			temp_textures.push_back(glm::vec2(texture.x, texture.y));
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
		}
		else if (strcmp(lineHeader, "f") == 0) {

			unsigned int vertexIndex[4], textureIndex[4], normalIndex[4];
			char line[256];
			fgets(line, 256, file);

			//string line_s(line);

			size_t fpos = 0;
			const char* fdelimiter = " ";
			char * fcontext = NULL;
			char * ftoken = strtok_s(line, fdelimiter, &fcontext);
			unsigned int fi = 0;

			size_t vpos = 0;
			const char* vdelimiter = "/";
			char * vcontext = NULL;
			unsigned int vi = 0;
			int numF = 0;

			while (ftoken != NULL) {
				int numV = 0;
				char * vtoken = strtok_s(ftoken, vdelimiter, &vcontext);
				while (vtoken != NULL) {
					switch(numV) {
					case 0:
						vertexIndex[numF] = atoi(vtoken);
						break;
					case 1:
						textureIndex[numF] = atoi(vtoken);
						break;
					case 2:
						normalIndex[numF] = atoi(vtoken);
						break;
					}
					numV++;
					vtoken = strtok_s(NULL, vdelimiter, &vcontext);
				}
				numF++;
				ftoken = strtok_s(NULL, fdelimiter, &fcontext);
			}

			//while ((fpos = line_s.find(fdelimiter)) != string::npos) {
			//	ftoken = line_s.substr(0, fpos);
			//	cout << ftoken;
			//	vi = 0;
			//	while ((vpos = ftoken.find(vdelimiter)) != string::npos) {
			//		vtoken = ftoken.substr(0, vpos);
			//		switch (vi) {
			//		case 0:
			//			vertexIndex[fi] = atoi(vtoken.c_str());
			//			break;
			//		case 1:
			//			textureIndex[fi] = atoi(vtoken.c_str());
			//			break;
			//		case 2:
			//			normalIndex[fi] = atoi(vtoken.c_str());
			//			break;
			//		}
			//		ftoken.erase(0, vpos + vdelimiter.length());
			//		vi++;
			//	}

			//	line_s.erase(0, fpos + fdelimiter.length());
			//	fi++;
			//}


			//cout << endl;

			//int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &textureIndex[0], &normalIndex[0], &vertexIndex[1], &textureIndex[1], &normalIndex[1], &vertexIndex[2], &textureIndex[2], &normalIndex[2], &vertexIndex[3], &textureIndex[3], &normalIndex[3]);
			//if (!(matches == 12 || matches == 9)) {
			//	printf("File can't be read by our simple parser : ( Try exporting with other options\n");
			//	return false;
			//}

			temp_indices.push_back(vertexIndex[0] - 1);
			temp_indices.push_back(vertexIndex[1] - 1);
			temp_indices.push_back(vertexIndex[2] - 1);

			//temp_indices.push_back(vertexIndex[2] - 1);
			//temp_indices.push_back(vertexIndex[3] - 1);
			//temp_indices.push_back(vertexIndex[0] - 1);

			temp_texture_indices.push_back(textureIndex[0] - 1);
			temp_texture_indices.push_back(textureIndex[1] - 1);
			temp_texture_indices.push_back(textureIndex[2] - 1);
		
			//temp_texture_indices.push_back(textureIndex[2] - 1);
			//temp_texture_indices.push_back(textureIndex[3] - 1);
			//temp_texture_indices.push_back(textureIndex[0] - 1);

			temp_normal_indices.push_back(normalIndex[0] - 1);
			temp_normal_indices.push_back(normalIndex[1] - 1);
			temp_normal_indices.push_back(normalIndex[2] - 1);

			//temp_normal_indices.push_back(textureIndex[2] - 1);
			//temp_normal_indices.push_back(textureIndex[3] - 1);
			//temp_normal_indices.push_back(textureIndex[0] - 1);

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

	for (int i = 0; i < temp_indices.size(); i += 3)
	{
		GLushort ia = temp_indices[i];
		GLushort ib = temp_indices[i + 1];
		GLushort ic = temp_indices[i + 2];
		addVertices(temp_vertices[ia], temp_vertices[ib], temp_vertices[ic]);
		addIndices(ia, ib, ic);
	}

	cout << "Load Done !" << endl;

	return true;

}

glm::vec3 Object::computeFaceNormal( glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	const float EPSILON = 0.000001f;
	glm::vec3 n = glm::vec3(0.f, 0.f, 0.f);

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
	windowMatrix = modelViewMatrix * originMatrix * coordinateMatrix;
	if (w > 0.f && h > 0.f && isnan(w) == 0 && isnan(h) == 0) {
		for (int i = 0; i < 5; i++) {
			finalPositions[i] = originMatrix * originPositions[i];
			windowPositions[i] = windowMatrix * originPositions[i];
		}
	}

	if (disableDraw) {
		return;
	}

	if (vertices.size() != 0) {
		drawShader(projectionMatrix, windowMatrix);
	}

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
		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(colorLocation, modelColor[0], modelColor[1], modelColor[2], modelColor[3]);
		glDrawArrays(GL_TRIANGLES, 0, getVertexCount());

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0f, 1.0f);
		glUniform4f(colorLocation, backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
		glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
		glDisable(GL_POLYGON_OFFSET_FILL);
		glDisable(GL_DEPTH_TEST);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(colorLocation, modelColor[0], modelColor[1], modelColor[2], modelColor[3]);
		glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
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
	while (doCollision()) {}
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

void Object::updateCurrentTransformationMatrix() {
    for (int i = 0; i < 5; i++) {
        finalPositions[i] = originMatrix * originPositions[i];
        windowPositions[i] = windowMatrix * originPositions[i];
    }
    for (vector<Object *>::iterator it = children.begin(); it != children.end(); ++it) {
        (*it)->updateCurrentTransformationMatrix();
    }
	updatedCurrentTransformationMatrix();
}

bool CheckCollisionBool(Object *one, Object *two)
{
    // Collision x-axis?
    bool collisionX = one->finalLeft() <= two->finalRight()
                      && one->finalRight() >= two->finalLeft();;
    // Collision y-axis?
    bool collisionY = one->finalBottom() <= two->finalTop()
                      && one->finalTop() >= two->finalBottom();
    // Collision only if on both axes
    return collisionX && collisionY;
}

bool Object::doCollision() {
    bool isOccur = checkCollision();
    if (isOccur) return true;
    for (vector<Object *>::iterator it = children.begin(); it != children.end(); ++it) {
        if ((*it)->doCollision()) {
            return true;
        }
    }
    return false;
}

GLfloat MAGIC_OVERLAP = 0.00001f;

Collision* CheckCollisionInfo(Object *one, Object *two)
{
    Collision* collision = new Collision();
    if (CheckCollisionBool(one, two)) {
        if (two->criticalCollisionAction(one)) {
            return collision;
        }
        collision->occur = true;
        GLfloat rl = two->finalRight() - one->finalLeft();
        GLfloat lr = two->finalLeft() - one->finalRight();
        GLfloat absRL = fabs(rl);
        GLfloat absLR = fabs(lr);
        GLfloat minXAbs = fmin(absRL, absLR);
        GLfloat maxXAbs = fmax(absRL, absLR);
        if (minXAbs < MAGIC_OVERLAP) {
            if (maxXAbs == absLR) {
                collision->overlapX = MAGIC_OVERLAP;
            }
            else {
                collision->overlapX = -MAGIC_OVERLAP;
            }
        }
        else if (minXAbs == absRL) {
            collision->overlapX = rl;
        }
        else {
            collision->overlapX = lr;
        }

        GLfloat tb = two->finalTop() - one->finalBottom();
        GLfloat bt = two->finalBottom() - one->finalTop();
        GLfloat absTB = fabs(tb);
        GLfloat absBT = fabs(bt);
        GLfloat minYAbs = fmin(absTB, absBT);
        GLfloat maxYAbs = fmax(absTB, absBT);
        if (minYAbs < MAGIC_OVERLAP) {
            if (maxYAbs == absBT) {
                collision->overlapY = MAGIC_OVERLAP;
            }
            else {
                collision->overlapY = -MAGIC_OVERLAP;
            }
        }
        else if (minYAbs == absTB) {
            collision->overlapY = tb;
        }
        else {
            collision->overlapY = bt;
        }
    }
    return collision;
}

bool Object::skipCollision(Object* node) {
	return node == this
		   || isSolid
           || !collisionCheck
           || !node->collisionCheck;
}

bool Object::checkCollision() {
    bool result = false;
    for (vector<Object *>::iterator it = allNodes.begin(); it != allNodes.end(); ++it) {
        if (skipCollision(*it)) {
            continue;
        }
        Collision* collision = CheckCollisionInfo(this, *it);
        if (collision->occur) {
            actionCollision(collision)->updateCurrentTransformationMatrix();
            return true;
        }
    }
    return result;
}

void Object::reset()
{
	resetPosition();
	for (vector<Object *>::iterator it = children.begin(); it != children.end(); ++it) {
		(*it)->reset();
	}
}

