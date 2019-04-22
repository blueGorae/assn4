#include "SceneGraph.h"


// TODO : fix object instance


void SceneGraph::init() {
    root = new Object();

	vertexLocation = glGetAttribLocation(myProgramObj, "vPosition");
	ctmLocation = glGetUniformLocation(myProgramObj, "ctm");

    // add 순서 중요 collision check 순서에 영향 - 순서는 reverse 순이다.
	root->addChild(&ball);
	root->addChild(&background);

	//Init Buffer
	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, this->getRoot()->getVerticesSize(), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &indiciesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->getRoot()->getIndiciesSize(), NULL, GL_STATIC_DRAW);

	unsigned vertexOffset = 0;
	unsigned indexOffset = 0;
	root->init(vertexOffset, indexOffset);

	// Create the ballVAO for the program.
	glGenVertexArrays(1, &ballVAO);
	glBindVertexArray(ballVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vertexLocation);
	glBindVertexArray(0);

	// Create the floorVAO for the program.
	glGenVertexArrays(1, &backgroundVAO);
	glBindVertexArray(backgroundVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(ball.getVerticesSize()));
	glEnableVertexAttribArray(vertexLocation);
	glBindVertexArray(0);

	projectionMat = glm::mat4(1.f);
	modelViewMat = glm::mat4(1.f);
	ctm = projectionMat * modelViewMat;

	glUniformMatrix4fv(ctmLocation, 1, GL_TRUE, &ctm[0][0]);

}

void SceneGraph::KeyboardFunc(unsigned char key, int x, int y)
{

}

void SceneGraph::DisplayFunc()
{
    root->draw(projectionMatrix, modelViewMatrix);
}

void SceneGraph::IdleFunc()
{
	root->move();
}
