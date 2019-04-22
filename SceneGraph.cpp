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
	
	player.loadOBJ("resource/Chikorita_OBJ.obj");
	com.loadOBJ("resource/Chikorita_OBJ.obj");
	
	player.setOriginalMatrix( glm::translate(glm::mat4(1.f), glm::vec3(0.f, - 0.5f , 0.f))
		* glm::rotate((float) M_PI_2, glm::vec3(1.f, 0.f, 0.f)) 
		* glm::rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f)) 
		* player.getOriginalMatrix());


	com.setOriginalMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.5f, 0.f))
		* glm::rotate((float)M_PI_2, glm::vec3(1.f, 0.f, 0.f))
		* com.getOriginalMatrix());

	vertexLocation = glGetAttribLocation(myProgramObj, "vPosition");
	ctmLocation = glGetUniformLocation(myProgramObj, "ctm");

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

}

void SceneGraph::DisplayFunc()
{
    root->draw(projectionMatrix, modelViewMatrix);
}

void SceneGraph::IdleFunc()
{
	root->move();
}
