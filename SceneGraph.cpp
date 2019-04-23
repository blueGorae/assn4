#include "SceneGraph.h"

#define WIDTH 4.f
#define DEPTH 8.f
#define HEIGHT 4.f

Sphere ball(0.2f, 2);
Background background(WIDTH, DEPTH, HEIGHT);
Character player;
Character com;

void SceneGraph::init() {
    root = new Object();

	player = Character(glm::vec3(0.f, -0.5f, 0.f), false);
	com = Character(glm::vec3(0.f, 0.5f, 0.f), true);
	player.loadOBJ("resource/Chikorita_OBJ.obj");
	com.loadOBJ("resource/Chikorita_OBJ.obj");

	vertexLocation = glGetAttribLocation(myProgramObj, "vPosition");
	ctmLocation = glGetUniformLocation(myProgramObj, "ctm");
	colorLocation = glGetUniformLocation(myProgramObj, "vColor");
    // add 순서 중요 collision check 순서에 영향 - 순서는 reverse 순이다.
	root->addChild(&ball);
	root->addChild(&player);
	root->addChild(&com);
	root->addChild(&background);
	//Init Buffer
	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, this->getRoot()->totalVerticesSize(), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &indiciesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->getRoot()->totalIndicesSize(), NULL, GL_STATIC_DRAW);

	unsigned vertexOffset = 0;
	unsigned indexOffset = 0;
	root->init(&vertexOffset, &indexOffset);
}

void SceneGraph::KeyboardFunc(unsigned char key, int x, int y)
{
	player.pressed(key);

}

void SceneGraph::DisplayFunc()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glBindVertexArray(background.VAO);
	//glUniform4f(colorLocation, modelColor[0], modelColor[1], modelColor[2], modelColor[3]);
	//background.draw(projectionMatrix, modelViewMatrix);
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glBindVertexArray(ball.VAO);
	//glUniform4f(colorLocation, backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
	//ball.draw(projectionMatrix, modelViewMatrix);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glUniform4f(colorLocation, modelColor[0], modelColor[1], modelColor[2], modelColor[3]);
	//ball.draw(projectionMatrix, modelViewMatrix);
	//glBindVertexArray(0);
	

	root->draw(projectionMatrix, modelViewMatrix);

}

void SceneGraph::IdleFunc()
{
	root->move();
}
