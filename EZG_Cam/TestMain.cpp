﻿
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
Shader* shadowShader;
Shader* depthShader;

// lighting
float lightSpeed = 0.5f;
glm::vec3 lightPos(0.0f, 5.0f, 0.0f);

//Normal bumpiness
float bumpiness = 1;

//------------------------ Anti aliasing ------------------------------------
int samplingRate = 2;
bool useAntiAliasing = false;
bool switchMode = false;
GLenum aAMode = GL_FASTEST;

bool glutAlive = true;

void display();
void clearMem();
void hideConsole();
void timer(int value);
void initGame();
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
void initWindow(int width, int height);
void glutRun(int argc, char** argv);
void exitGlut();

int main(int argc, char** argv)
{
	while (glutAlive) {
		glutRun(argc, argv);
	}

	return 0;
}

void glutRun(int argc, char** argv) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//hideConsole();

	initGame();

	glutInit(&argc, argv);
	initWindow(WIN_WIDTH, WIN_HEIGHT);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutTimerFunc(15, timer, 1);
	//glutFullScreen();
	glutMainLoop();
	clearMem();
	glPopAttrib();
}

void initWindow(int width, int height) {

	glutSetOption(GLUT_MULTISAMPLE, samplingRate);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, aAMode);

	glutInitWindowSize(width, height);
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

	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	resize(width, height);
	cout << "Start loading\n";

	//lodTest->m_pos.y = 4;

	camSpline->setLineWidth(5.0f);
	camSpline->setColor(1, 0, 0, 1);

	// build and compile our shader zprogram
	// ------------------------------------

	//lightingShader = new Shader("Shader/basic_lighting.vs", "Shader/basic_lighting.fs");
	//lampShader = new Shader("Shader/basic_lighting.vs", "Shader/lamp.fs");
	shadowShader = new Shader("Shader/point_shadows.vs", "Shader/point_shadows.fs");
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

	// shader configuration
	// --------------------
	shadowShader->use();
	shadowShader->setInt("diffuseTexture", 0);
	shadowShader->setInt("normalMap", 1);
	shadowShader->setInt("depthMap", 2);

	shadowShader->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));

	cout << "Finished loading\n";

	//TODO Test
	playerCam->Yaw = -90;
	playerCam->Pitch = 0;

	lastTime = glutGet(GLUT_ELAPSED_TIME);
}

void initGame()
{
	//Create game object here
	playerCam = make_shared<Player>();
	//lodTest = make_shared<LodObject>();
	camSpline = make_shared<Spline>();

	//Load Level
	LoadedLevel::loadLevel(Level1::map, Level1::width, Level1::height, Level1::depth);

	//Config spawn
	playerCam->setPos(glm::vec3(0.0f, findSpawnHeight(0.0f, 4.0f), 4.0f));

	playerCam->m_movementSpeed = 10.0f;
	playerCam->setRotationSpeed(0.5f);

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

	if (useAntiAliasing) {
		glEnable(GL_MULTISAMPLE);
	}
	else {
		glDisable(GL_MULTISAMPLE);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Move light
	lightPos = glm::vec3(5.0f * cos(lightSpeed * lastTime / 1000), 5.0f, 5.0f * sin(lightSpeed * lastTime / 1000));

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
	glPushMatrix();
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
	glPopMatrix();

	glPushMatrix();
	//render scene
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shadowShader->use();
	glm::mat4 projection = glm::perspective(glm::radians(playerCam->Zoom), (float)WIN_WIDTH / (float)WIN_HEIGHT, near_plane, far_plane);
	glm::mat4 view = playerCam->GetViewMatrix();
	shadowShader->setMat4("projection", projection);
	shadowShader->setMat4("view", view);
	// set lighting uniforms
	shadowShader->setVec3("lightPos", lightPos);
	shadowShader->setVec3("viewPos", playerCam->Position);
	shadowShader->setInt("shadows", shadows);
	shadowShader->setFloat("far_plane", far_plane);
	shadowShader->setFloat("bumpiness", bumpiness);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);

	renderScene(shadowShader);
	
	glPopMatrix();

	glPushMatrix();
	//Render light
	
	glTranslatef(lightPos.x, lightPos.y, lightPos.z);

	shadowShader->setInt("shadows", false);
	glm::mat4 m_model(1.0f);
	m_model = glm::translate(m_model, glm::vec3(lightPos.x, lightPos.y, lightPos.z));
	shadowShader->setMat4("model", m_model);

	//glColor3f(1, 0, 0);
	GLUquadric* quad;
	quad = gluNewQuadric();
	gluSphere(quad, 0.33, 10, 10);
	glPopMatrix();

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

void clearMem() {
	//Free memory
	//delete lightingShader;
	//delete lampShader;
	delete shadowShader;
	delete depthShader;
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
		exitGlut();
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
		cout << "Player moved: " << playerCam->getPos().x << " " << playerCam->getPos().y << " " << playerCam->getPos().z << "\n";
	}
	if (keyPressedFlags.s) {
		playerCam->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		cout << "Player moved: " << playerCam->getPos().x << " " << playerCam->getPos().y << " " << playerCam->getPos().z << "\n";
	}
	if (keyPressedFlags.a) {
		playerCam->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
		cout << "Player moved: " << playerCam->getPos().x << " " << playerCam->getPos().y << " " << playerCam->getPos().z << "\n";
	}
	if (keyPressedFlags.d) {
		playerCam->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
		cout << "Player moved: " << playerCam->getPos().x << " " << playerCam->getPos().y << " " << playerCam->getPos().z << "\n";
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
	if (keyPressedFlags.v && keyChangedFlags.v) {
		useAntiAliasing = !useAntiAliasing;
		cout << "Use anti aliasing: " << useAntiAliasing << "\n";
	}
	if (keyPressedFlags.b && keyChangedFlags.b) {
		samplingRate = samplingRate * 2;
		if (samplingRate > 16) {
			samplingRate = 16;
		}
		else {
			cout << "Sampling rate: " << samplingRate << "\n";
			glutLeaveMainLoop();
			//glutDestroyWindow(window);
			//initWindow(WIN_WIDTH, WIN_HEIGHT);
		}
	}
	if (keyPressedFlags.n && keyChangedFlags.n) {
		if (samplingRate > 2) {
			samplingRate = samplingRate / 2;
			cout << "Sampling rate: " << samplingRate << "\n";
			glutLeaveMainLoop();
			//glutDestroyWindow(window);
			//initWindow(WIN_WIDTH, WIN_HEIGHT);
		}
	}

	if (keyPressedFlags.m && keyChangedFlags.m) {
		switchMode = !switchMode;
		if (switchMode) {
			aAMode = GL_NICEST;
			cout << "Mode: Nicest\n";
			glutLeaveMainLoop();
			//glutDestroyWindow(window);
			//initWindow(WIN_WIDTH, WIN_HEIGHT);
		}
		else {
			aAMode = GL_FASTEST;
			cout << "Mode: Fastest\n";
			glutLeaveMainLoop();
			//glutDestroyWindow(window);
			//initWindow(WIN_WIDTH, WIN_HEIGHT);
		}
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

	//cout << "Player rot pitch: " << playerCam->Pitch << "\n";
	//cout << "Player rot yaw: " << playerCam->Yaw << "\n";

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

GLfloat sunLight[] = { 1,1,0 };
//draws and animates because it is called every frame
void renderScene(Shader* shader)
{
	int testmax = 100;
	glPushMatrix();

	Voxel* voxel = LoadedLevel::getVoxel(0, 0, 0);
	voxel->setShader(shader);
	voxel->draw(static_cast<float>(0) - LoadedLevel::m_centerOffsetX, 0, static_cast<float>(0) - LoadedLevel::m_centerOffsetZ);
		
	for (int i = 1; i < testmax; i++) {
		Voxel* voxel = LoadedLevel::getVoxel(0, 0, 0);
		voxel->setShader(shader);
		voxel->draw(static_cast<float>(i) - LoadedLevel::m_centerOffsetX, 0, static_cast<float>(0) - LoadedLevel::m_centerOffsetZ);
	}
	for (int i = 1; i < testmax; i++) {
		Voxel* voxel = LoadedLevel::getVoxel(0, 0, 0);
		voxel->setShader(shader);
		voxel->draw(static_cast<float>(-i) - LoadedLevel::m_centerOffsetX, 0, static_cast<float>(0) - LoadedLevel::m_centerOffsetZ);
	}

	for (int i = 1; i < testmax; i++) {
		Voxel* voxel = LoadedLevel::getVoxel(0, 0, 0);
		voxel->setShader(shader);
		voxel->draw(static_cast<float>(0) - LoadedLevel::m_centerOffsetX, i, static_cast<float>(0) - LoadedLevel::m_centerOffsetZ);
	}
	for (int i = 1; i < testmax; i++) {
		Voxel* voxel = LoadedLevel::getVoxel(0, 0, 0);
		voxel->setShader(shader);
		voxel->draw(static_cast<float>(0) - LoadedLevel::m_centerOffsetX, -i, static_cast<float>(0) - LoadedLevel::m_centerOffsetZ);
	}

	for (int i = 1; i < testmax; i++) {
		Voxel* voxel = LoadedLevel::getVoxel(0, 0, 0);
		voxel->setShader(shader);
		voxel->draw(static_cast<float>(0) - LoadedLevel::m_centerOffsetX, 0, static_cast<float>(i) - LoadedLevel::m_centerOffsetZ);
	}
	for (int i = 1; i < testmax; i++) {
		Voxel* voxel = LoadedLevel::getVoxel(0, 0, 0);
		voxel->setShader(shader);
		voxel->draw(static_cast<float>(0) - LoadedLevel::m_centerOffsetX, 0, static_cast<float>(-i) - LoadedLevel::m_centerOffsetZ);
	}

	glPopMatrix();
}

void renderScene2(Shader* shader) {
	
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
}

void exitGlut() {
	clearMem();
	glutAlive = false;
}