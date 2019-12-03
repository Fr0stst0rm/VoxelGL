
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <chrono>

#include <GL/glew.h>

#include "Defines.h"
#include "Input.h"

#include "Player.h"

#include "Voxel.h"
#include "LoadedLevel.h"

#include "Level1.h"

#include "LodObject.h"
#include "Spline.h"

using namespace std;

// x --> left/right
// y --> up/down
// z --> forward/backward

int window;

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;

const unsigned int SHADOW_WIDTH = 1024;
const unsigned int SHADOW_HEIGHT = 1024;

float near_plane = 0.5f;
float far_plane = 1000.0f;

unsigned int depthMapFBO;
unsigned int depthCubemap;

bool shadows = true;

long lastTime;
float deltaTime;

float lastMouseX = WIN_WIDTH / 2.0f;
float lastMouseY = WIN_HEIGHT / 2.0f;

int xRotationOffset = -1;
int yRotationOffset = -1;
int zRotationOffset = -1;

shared_ptr<Player> playerCam;
glm::quat camera_quat;

float flyOnSplineTime = -1;
long startTime;
shared_ptr<Spline> camSpline;

//shared_ptr<LodObject> lodTest;

//shader
//Shader* lightingShader;
//Shader* lampShader;
Shader* pointShadow;
Shader* depthShader;

// lighting
float lightSpeed = 0; // .25f;
glm::vec3 lightPos(0.0f, 5.0f, 0.0f);

//Normal bumpiness
float bumpiness = 1;

void display();
void exitMain();
void hideConsole();
void timer(int value);
void init(int width, int height);
void resize(int width, int height);
void checkInput();
void specialKeyPressed(int key, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void specialKeyUp(int key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouseMoved(int x, int y);
void mouseDragged(int x, int y);
void mouseClicked(int button, int state, int x, int y);
float findSpawnHeight(float x, float z);
void renderScene(Shader* shader);

int main(int argc, char** argv)
{
	//hideConsole();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("VoxelTest");

	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);

	glutKeyboardFunc(&keyPressed);
	glutKeyboardUpFunc(&keyUp);
	glutSpecialFunc(&specialKeyPressed);
	glutSpecialUpFunc(&specialKeyUp);
	glutMouseFunc(&mouseClicked);

	glutMotionFunc(&mouseDragged);
	glutPassiveMotionFunc(&mouseMoved);

	init(WIN_WIDTH, WIN_HEIGHT);
	glutTimerFunc(15, timer, 1);
	//glutFullScreen();

	glutMainLoop();
	exitMain();
	return 0;
}

void init(int width, int height)
{
	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	resize(width, height);

	cout << "Start loading\n";

	//Create game object here
	playerCam = make_shared<Player>();

	//lodTest = make_shared<LodObject>();
	//lodTest->m_pos.y = 4;

	camSpline = make_shared<Spline>();
	camSpline->setLineWidth(5.0f);
	camSpline->setColor(1, 0, 0, 1);

	//Load Level

	LoadedLevel::loadLevel(Level1::map, Level1::width, Level1::height, Level1::depth);

	//Config spawn
	playerCam->setPos(glm::vec3(0.0f, findSpawnHeight(0.0f, 4.0f), 4.0f));

	playerCam->m_movementSpeed = 10.0f;
	playerCam->setRotationSpeed(0.5f);

	// build and compile our shader zprogram
	// ------------------------------------

	//lightingShader = new Shader("Shader/basic_lighting.vs", "Shader/basic_lighting.fs");
	//lampShader = new Shader("Shader/basic_lighting.vs", "Shader/lamp.fs");
	pointShadow = new Shader("Shader/point_shadows.vs", "Shader/point_shadows.fs");
	depthShader = new Shader("Shader/point_shadows_depth.vs", "Shader/point_shadows_depth.fs", "Shader/point_shadows_depth.gs");

	//depth map FBO
	glGenFramebuffers(1, &depthMapFBO);
	// create depth cubemap texture
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	for (int i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/*
	Voxel* voxel;
	for (uint32_t z = 0; z < LoadedLevel::m_depth; z++) {
		for (uint32_t y = 0; y < LoadedLevel::m_height; y++) {
			for (uint32_t x = 0; x < LoadedLevel::m_width; x++) {
				voxel = LoadedLevel::getVoxel(x, y, z);

				if (voxel->isTransparent()) {

				}
				else if (voxel->isShining()) {
					voxel->setShader(lampShader);
					lightingShader->use();
					lightingShader->setVec3("lightColor", VoxelTypes::getColor(voxel->m_type).red, VoxelTypes::getColor(voxel->m_type).green, VoxelTypes::getColor(voxel->m_type).blue);
					lightingShader->setVec3("lightPos", glm::vec3(static_cast<float>(x) - LoadedLevel::m_centerOffsetX, y, static_cast<float>(z) - LoadedLevel::m_centerOffsetZ));
				}
				else {
					voxel->setShader(lightingShader);
				}
			}
		}
	}
	*/

	// shader configuration
	// --------------------
	pointShadow->use();
	pointShadow->setInt("diffuseTexture", 0);
	pointShadow->setInt("normalMap", 1);
	pointShadow->setInt("depthMap", 2);

	pointShadow->setVec3("lightColor", glm::vec3(0.5f,0.5f,0.5f));

	cout << "Finished loading\n";
	lastTime = glutGet(GLUT_ELAPSED_TIME);
}

void display()
{
	//Get delta time
	deltaTime = float(glutGet(GLUT_ELAPSED_TIME) - lastTime) / 1000.0f;
	lastTime = glutGet(GLUT_ELAPSED_TIME); // Milli sec

	// Input
	updateInput();
	checkInput();

	// Graphics
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Move light
	//lightPos = glm::vec3(5.0f * cos(lightSpeed * lastTime/1000), 5.0f, 5.0f * sin(lightSpeed * lastTime/1000));

	// create depth cubemap transformation matrices
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	// render depth cubemap
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	depthShader->use();
	for (int i = 0; i < 6; ++i) {
		depthShader->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
	}
	depthShader->setFloat("far_plane", far_plane);
	depthShader->setVec3("lightPos", lightPos);
	renderScene(depthShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//render scene
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pointShadow->use();
	glm::mat4 projection = glm::perspective(glm::radians(playerCam->Zoom), (float)WIN_WIDTH / (float)WIN_HEIGHT, near_plane, far_plane);
	glm::mat4 view = playerCam->GetViewMatrix();
	pointShadow->setMat4("projection", projection);
	pointShadow->setMat4("view", view);
	// set lighting uniforms
	pointShadow->setVec3("lightPos", lightPos);
	pointShadow->setVec3("viewPos", playerCam->Position);
	pointShadow->setInt("shadows", shadows);
	pointShadow->setFloat("far_plane", far_plane);
	pointShadow->setFloat("bumpiness", bumpiness);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);

	renderScene(pointShadow);

	//Render light
	pointShadow->setInt("shadows", false);
	glm::mat4 m_model(1.0f);
	m_model = glm::translate(m_model, glm::vec3(lightPos.x, lightPos.y, lightPos.z));
	pointShadow->setMat4("model", m_model);

	//glColor3f(1, 0, 0);
	GLUquadric* quad;
	quad = gluNewQuadric();
	gluSphere(quad, 0.33, 10, 10);

	glutSwapBuffers();
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 1);
}

void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void exitMain() {
	//Free memory
	//delete lightingShader;
	//delete lampShader;
	delete pointShadow;
	delete depthShader;

	exit(0);
}


void resize(int width, int height)
{
	// prevent division by zero
	if (height == 0) { height = 1; }

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
}

void checkInput() {

	if (keyPressedFlags.esc) {
		exitMain();
	}
	if (keyPressedFlags.up && keyChangedFlags.up) {
		playerCam->m_movementSpeed += 0.5f;
		if (playerCam->m_movementSpeed > 10) {
			playerCam->m_movementSpeed = 0;
		}
		cout << "Speed: " << playerCam->m_movementSpeed << "\n";

	}
	if (keyPressedFlags.down && keyChangedFlags.down) {
		playerCam->m_movementSpeed -= 0.5f;

		if (playerCam->m_movementSpeed < 1) {
			playerCam->m_movementSpeed = 0;
		}
		cout << "Speed: " << playerCam->m_movementSpeed << "\n";
	}
	if (keyPressedFlags.left) {
		bumpiness -= deltaTime;
		if (bumpiness < 0) bumpiness = 0;
		//cout << "Bumpiness: " << bumpiness << "\n";
	}
	if (keyPressedFlags.right) {
		bumpiness += deltaTime;
		if (bumpiness > 1) bumpiness = 1;
		//cout << "Bumpiness: " << bumpiness << "\n";
	}
	if (keyPressedFlags.e) {
		lightPos.z += 0.5 * deltaTime;
	}
	if (keyPressedFlags.w) {
		playerCam->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
		//playerCam->m_pos.z -= playerCam->getLookingDir().z * playerCam->m_walkingSpeed * deltaTime;
		//playerCam->m_pos.x += playerCam->getLookingDir().x * playerCam->m_walkingSpeed * deltaTime;
	}
	if (keyPressedFlags.s) {
		playerCam->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		//playerCam->m_pos.z += playerCam->getLookingDir().z * playerCam->m_walkingSpeed * deltaTime;
		//playerCam->m_pos.x -= playerCam->getLookingDir().x * playerCam->m_walkingSpeed * deltaTime;
	}
	if (keyPressedFlags.a) {
		playerCam->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
		//playerCam->m_pos.z -= playerCam->getLookingDir().x * playerCam->m_walkingSpeed * deltaTime;
		//playerCam->m_pos.x -= playerCam->getLookingDir().z * playerCam->m_walkingSpeed * deltaTime;
	}
	if (keyPressedFlags.d) {
		playerCam->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
		//playerCam->m_pos.z += playerCam->getLookingDir().x * playerCam->m_walkingSpeed * deltaTime;
		//playerCam->m_pos.x += playerCam->getLookingDir().z * playerCam->m_walkingSpeed * deltaTime;
	}
	/*if (keyPressedFlags.q) {
		playerCam->setPos(glm::vec3(playerCam->getPos().x, playerCam->getPos().y - playerCam->m_movementSpeed * deltaTime, playerCam->getPos().z));
		//playerCam->m_pos.y -= playerCam->m_movementSpeed * deltaTime;
	}
	if (keyPressedFlags.e) {
		playerCam->setPos(glm::vec3(playerCam->getPos().x, playerCam->getPos().y + playerCam->m_movementSpeed * deltaTime, playerCam->getPos().z));
		//playerCam->m_pos.y += playerCam->m_movementSpeed * deltaTime;
	}*/
	if (keyPressedFlags.c && keyChangedFlags.c) {
		camSpline->clearPoints();
	}
	if (keyPressedFlags.space && keyChangedFlags.space) {
		camSpline->addPoint({ playerCam->getPos().x, playerCam->getPos().y, playerCam->getPos().z }, playerCam->m_quatRot);
	}
	if (keyPressedFlags.t && keyChangedFlags.t) {
		camSpline->toggleSplineRender();
	}
	if (keyPressedFlags.f && keyChangedFlags.f) {
		flyOnSplineTime = 0;
		cout << "Line length: " << camSpline->getLineLength() << "m\n";
		cout << "Starting spline now\n";
		startTime = glutGet(GLUT_ELAPSED_TIME);
	}

}

void mouseClicked(int button, int state, int x, int y)
{
	cout << "Click: " << button << " " << state << " " << x << " " << y << "\n";
}

void mouseDragged(int x, int y)
{
	mouseMoved(x, y);
	cout << "Drag x: " << x << " y: " << y << "\n";
}

void mouseMoved(int x, int y)
{
	if (yRotationOffset == -1) {
		yRotationOffset = x;
	}


	if (xRotationOffset == -1) {
		xRotationOffset = y;
		lastMouseX = x;
	}
	if (zRotationOffset == -1) {
		zRotationOffset = y;
		lastMouseY = y;
	}

	float xoffset = x - lastMouseX;
	float yoffset = lastMouseY - y; // reversed since y-coordinates go from bottom to top

	lastMouseX = x;
	lastMouseY = y;

	playerCam->ProcessMouseMovement(xoffset, yoffset);

	/*

	//Rotation um y achse mit mouse x value

	float xDeg = static_cast<int>(static_cast<float>(y - xRotationOffset) * playerCam->m_rotationSpeed) % 360;
	float yDeg = static_cast<int>(static_cast<float>(x - yRotationOffset) * playerCam->m_rotationSpeed) % 360;

	glm::quat mouseRot(glm::vec3(glm::radians(xDeg), glm::radians(yDeg), glm::radians(0.0f)));

	playerCam->m_quatRot = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	playerCam->m_quatRot *= glm::quat({ 0.0f, glm::radians(yDeg), 0.0f });
	playerCam->m_quatRot = glm::quat({ glm::radians(xDeg), 0.0f, 0.0f }) * playerCam->m_quatRot;

	//cout << "CamRot Y: " << glm::degrees(glm::eulerAngles(playerCam->m_keyRot).y) << "\n";
	*/
}


float findSpawnHeight(float x, float z) {
	float y = 0;
	for (y = (LoadedLevel::m_height - 1); y >= 0; y--) {
		if (LoadedLevel::getVoxelCentered(x, y, z)->m_type != VoxelType::AIR) {
			break;
		}
	}

	cout << "Player start Y pos: " << (y + 1) << "\n";

	return y + 1;
}

void renderScene(Shader* shader) {
	//LOD Test
	//float distance = (lodTest->m_pos - player->m_pos).length();
	//cout << "LodDistance: " << distance << "\n";
	//lodTest->draw(distance);

	//Draw Spline

	/*
	if (flyOnSplineTime >= 0) {

		playerCam->m_quatRot = camSpline->getCameraRotationAtTime(flyOnSplineTime * playerCam->m_movementSpeed);

		flyOnSplineTime += deltaTime;

		if (int(flyOnSplineTime * playerCam->m_movementSpeed) >= camSpline->getPointCount()) {
			flyOnSplineTime = -1;
			cout << "Spline finished: " << (float(glutGet(GLUT_ELAPSED_TIME) - startTime) / 1000.0f) << "s\n";
		}

	}
	*/

	//camSpline->drawSpline();


	//Draw level

	Voxel* voxel;
	std::vector<SortingHelper> trasparentSortingVector;

	//Draw opaque objects here
	//Draw farest z layer first
	glm::vec3 drawPos;
	for (uint32_t z = 0; z < LoadedLevel::m_depth; z++) {
		for (uint32_t y = 0; y < LoadedLevel::m_height; y++) {
			for (uint32_t x = 0; x < LoadedLevel::m_width; x++) {
				voxel = LoadedLevel::getVoxel(x, y, z);

				//cout << "X " << x << " Y " << y << " Z " << z << " -> Index: " << XYZ_TO_ARRAY_INDEX(x, y, z, LoadedLevel::m_width, LoadedLevel::m_depth) << " = " << LoadedLevel::m_map[XYZ_TO_ARRAY_INDEX(x, y, z, LoadedLevel::m_width, LoadedLevel::m_depth)] << "\n";
				//cout << "Size of voxel: " << sizeof(voxel) << "\n";

				if (!voxel->isTransparent()) {
					voxel->setShader(shader);
					voxel->draw(static_cast<float>(x) - LoadedLevel::m_centerOffsetX, y, static_cast<float>(z) - LoadedLevel::m_centerOffsetZ);
				}
				else if (voxel->m_type != VoxelType::AIR)
				{
					float order = (Vector3f(x, y, z) - Vector3f(playerCam->getPos().x + LoadedLevel::m_centerOffsetX, playerCam->getPos().y, playerCam->getPos().z + LoadedLevel::m_centerOffsetZ)).length();
					//insert at right pos
					int i = 0;
					for (; i < trasparentSortingVector.size(); i++) {
						if (order < trasparentSortingVector[i].sortingVal) {
							break;
						}
					}
					SortingHelper elem = { Vector3f(x,y,z), order };
					trasparentSortingVector.insert(trasparentSortingVector.begin() + i, elem);
				}
			}
		}
	}

	//cout << "Start transparent\n";

	/*
	//Draw transparent objects here
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Draw farest z layer first
	while (!trasparentSortingVector.empty())
	{
		voxel = LoadedLevel::getVoxel(trasparentSortingVector.back().position);
		voxel->setShader(lightingShader);
		voxel->drawTransparent(trasparentSortingVector.back().position.x - LoadedLevel::m_centerOffsetX, trasparentSortingVector.back().position.y, trasparentSortingVector.back().position.z - LoadedLevel::m_centerOffsetZ);

		trasparentSortingVector.pop_back();
	}


	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	*/
}
