#include "SceneGraph.h"


// TODO : fix object instance
Object ball;
Object sphere;
Object plane;

void SceneGraph::init() {
    root = new Object();
    // add 순서 중요 collision check 순서에 영향 - 순서는 reverse 순이다.
 /*   root->addChild(&leftWall);
    root->addChild(&rightWall);
    root->addChild(&topWall);
    root->addChild(&bottomLeftWall);
    root->addChild(&bottomRightWall);
    root->addChild(&background);
    root->addChild(&cloud1);
    root->addChild(&cloud2);
    root->addChild(&cloud3);
    root->addChild(&net);
    root->addChild(&user);
    root->addChild(&com);
    root->addChild(&sceneNodeBall);
    root->addChild(&user_score);
    root->addChild(&com_score);*/

	root->init();
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
