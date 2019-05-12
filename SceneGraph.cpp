#include "SceneGraph.h"

vector<Object*> allNodes = vector<Object*>();

ScoreBox userScore = ScoreBox(- 0.9f, 0.9f);
ScoreBox comScore  = ScoreBox(0.9f, 0.9f);
void addGameScore(bool addUserScore);
Sphere ball(0.2f, 2, addGameScore);

void addGameScore(bool addUserScore) {
    if (addUserScore) {
        userScore.addScore();
    } else {
        comScore.addScore();
    }
    ball.resetPosition();
}


Background background(WIDTH, DEPTH, HEIGHT);
Character player = Character(glm::vec3(0.f, -DEPTH * 0.35f, 0.f), false);
Character com = Character(glm::vec3(0.f, DEPTH * 0.35f, 0.f), true);
DirectionalLight dLight = DirectionalLight(glm::vec3(0.f, DEPTH * 0.5f, HEIGHT),
        glm::vec3(0.f, -DEPTH * 0.35f, HEIGHT),
        1.5f);
PointLight pLight = PointLight(glm::vec3(2 * ball.getRadius(), 2 * ball.getRadius(), 2 * ball.getRadius()),
                               1.5f);

void SceneGraph::init() {
	player.loadOBJ("resource/pikachu/pikachu.obj");
	com.loadOBJ("resource/pikachu/pikachu.obj");

	player.loadTextureImage("resource/pikachu/pikachu_texture/Final_Pokemon_Diffuse.png");
	com.loadTextureImage("resource/pikachu/pikachu_texture/Final_Pokemon_Diffuse.png");

	ball.loadTextureImage("resource/ball/ball.bmp");

	background.leftPlane.loadTextureImage("resource/wall/diffuse.DDS");
	background.rightPlane.loadTextureImage("resource/wall/diffuse.DDS");
	background.downPlane.loadTextureImage("resource/wall/diffuse.DDS");
	background.frontPlane.loadTextureImage("resource/wall/diffuse.DDS");
	background.backPlane.loadTextureImage("resource/wall/diffuse.DDS");


	vertexLocation = glGetAttribLocation(myProgramObj, "vPosition");
	projectionMatrixLocation = glGetUniformLocation(myProgramObj, "Projection");
	viewMatrixLocation = glGetUniformLocation(myProgramObj, "View");
	modelMatrixLocation = glGetUniformLocation(myProgramObj, "Model");
	isGouraudShadingLocation = glGetUniformLocation(myProgramObj, "IsGouraudShading");
	isNoLightLocation = glGetUniformLocation(myProgramObj, "IsNoLight");
	ostringstream oss;
	for (int i = 0; i < DIRECTIONAL_LIGHTS; i++) {
		oss.clear();
		oss << "AmbientProduct[" << i << "]";
		ambientProductLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
		oss.clear();
		oss << "DiffuseProduct[" << i << "]"; 
		diffuseProductLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
		oss.clear();
		oss << "SpecularProduct[" << i << "]";
		specularProductLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
		oss.clear();
		oss << "LightPosition[" << i << "]";
		lightPositionLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
		oss.clear();
		oss << "Shininess[" << i << "]";
		shininessLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
	}
    for (int i = 0; i < POINT_LIGHTS; i++) {
		oss.clear();
		oss << "pAmbientProduct[" << i << "]";
        pAmbientProductLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
		oss.clear();
		oss << "pDiffuseProduct[" << i << "]";
		pDiffuseProductLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
		oss.clear();
		oss << "pSpecularProduct[" << i << "]";
		pSpecularProductLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
		oss.clear();
		oss << "pLightPosition[" << i << "]";
		pLightPositionLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
		oss.clear();
		oss << "pShininess[" << i << "]";
		pShininessLocation[i] = glGetUniformLocation(myProgramObj, oss.str().c_str());
    }

	colorLocation = glGetUniformLocation(myProgramObj, "vColor");
	textureLocation = glGetAttribLocation(myProgramObj, "vTexture");
	normalLocation = glGetAttribLocation(myProgramObj, "vNormal");

    // add 순서 중요 collision check 순서에 영향 - 순서는 reverse 순이다.

	//순서를 바꾸면 이상해짐
	root->addChild(&background);
	root->addChild(&com);
	root->addChild(&player);
	root->addChild(&ball);
    ball.addChild(&pLight);
	//Init Buffer
	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, this->getRoot()->totalVerticesSize(), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glGenBuffers(1, &indiciesVBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->getRoot()->totalIndicesSize(), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &texturesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texturesVBO);
	glBufferData(GL_ARRAY_BUFFER, this->getRoot()->totalTexturesSize(), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &normalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glBufferData(GL_ARRAY_BUFFER, this->getRoot()->totalNormalsSize(), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	unsigned vertexOffset = 0;
	unsigned indexOffset = 0;
	unsigned textureOffset = 0;
	unsigned normalOffset = 0;
	root->init(&vertexOffset, &indexOffset, &textureOffset, &normalOffset);
	pLight.init();
	dLight.init();
}

void SceneGraph::KeyboardFunc(unsigned char key, int x, int y)
{
	player.pressed(key);
	//ball.pressed(key);
}

void SceneGraph::DisplayFunc()
{
    pLight.draw();
	root->draw(projectionMatrix, modelViewMatrix);
    userScore.draw();
    comScore.draw();
}

void SceneGraph::IdleFunc()
{
    if (userScore.getScore() == endScore || comScore.getScore() == endScore) {
        root->reset();
        userScore.reset();
        comScore.reset();
    }
    else {
        root->move();
        dLight.move();
    }
}

void SceneGraph::reset()
{
    root->reset();
}
