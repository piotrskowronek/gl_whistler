#include "stdafx.h"
#include <vector>
#include <memory>
#include <time.h>
#include "Scene.h"
#include "Light.h"

using namespace std;

#pragma region Zmienne globalne

SCameraState player;

double T = 0.0;

int mouseX = 0;
int mouseY = 0;

int fps = 1000;
clock_t begin = clock();

bool captureMouse = true;
bool free3DMovement = true;

Scene* scene = new Scene;
Light* light;
bool isEnd = false;

int lives = 20;
int points = 0;

float mouseSensitivity = .15f;

#pragma endregion

int main(int argc, char* argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 600);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("glWhackTheMario");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutTimerFunc(17, OnTimer, 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_FOG);
	float gl_fogcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, gl_fogcolor);
	glFogf(GL_FOG_START, 5.0f);
	glFogf(GL_FOG_END, 30.0f);
	
	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	/*player.pos.x = 0.081256f;
	player.pos.y = 3.542898f;
	player.pos.z = 8.002872f;

	player.dir.x = -0.011955f;
	player.dir.y = -0.464438f;
	player.dir.z = -0.885525f;*/
	     
	player.pos.x = -0.014905f;
	player.pos.y = 2.358988f;
	player.pos.z = 8.660418f;

	player.dir.x = 0.000000f;
	player.dir.y = -0.100331f;
	player.dir.z = -0.994954f; 

	player.speed = .4f;

	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutSetCursor(GLUT_CURSOR_NONE);

	scene->onInit();

	glutMainLoop();
	return 0;
}

#pragma region Obsluga wejscia

bool keystate[255];

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		keystate[key] = true;
		OnKeyDown(key, x, y);
	}
}

void OnKeyDown(unsigned char key, int x, int y) {
	scene->onKeyDown(key, x, y);

	if (key == 27) {
		glutLeaveMainLoop();
	}
	if (key == 'm' || key == 'M') {
		if (captureMouse) {
			captureMouse = false;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		else {
			captureMouse = true;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
	}
	if (key == 'l' || key == 'L') {
		free3DMovement = !free3DMovement;
	}
}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void OnMouseMove(int x, int y) {
	mouseX = x;
	mouseY = y;
}

#pragma endregion

void OnTimer(int id) {
	glutTimerFunc((int)(1000 / fps), OnTimer, 0);

	string title = "glWhackTheMario (Lives left: " + to_string(lives) + ", Points: " + to_string(points) + ")";
	glutSetWindowTitle(title.c_str());

	#pragma region Ruch kamery

	if (captureMouse) {
		player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
		player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}

	/*if (keystate['w']) {
		player.velM = player.speed;
	}
	if (keystate['s']) {
		player.velM = -player.speed;
	}
	if (keystate['a']) {
		player.velS = -player.speed;
	}
	if (keystate['d']) {
		player.velS = player.speed;
	}
	if (keystate['q']) {
		player.velRY = -player.speed;
	}
	if (keystate['e']) {
		player.velRY = player.speed;
	}
	if (keystate['f']) {
		player.velRX = -player.speed;
	}
	if (keystate['c']) {
		player.velRX = player.speed;
	}*/

	/*float T = acos(player.dir.y);
	float G = atan2(player.dir.z, player.dir.x);
	T -= player.velRX * .03f;
	G += player.velRY * .03f;
	player.dir.x = sin(T) * cos(G);
	player.dir.y = cos(T);
	player.dir.z = sin(T) * sin(G);

	vec3 per;
	per.x = -player.dir.z;
	per.y = 0;
	per.z = player.dir.x;

	player.pos.x += player.dir.x * player.velM * .1f;
	if (free3DMovement) {
		player.pos.y += player.dir.y * player.velM * .1f;
	}
	else {
		player.pos.y = 1.0f;
	}
	player.pos.z += player.dir.z * player.velM * .1f;

	player.pos.x += per.x * player.velS * .1f;
	if (free3DMovement) {
		player.pos.y += player.dir.y * player.velM * .1f;
	}
	else {
		player.pos.y = 1.0f;
	}
	player.pos.z += per.z * player.velS * .1f;

	player.velRX /= 1.2;
	player.velRY /= 1.2;
	player.velM /= 1.2;
	player.velS /= 1.2;*/

	scene->onTimer();

	//printf("%f %f %f %f %f %f\n", player.pos.x, player.pos.y, player.pos.z, player.dir.x, player.dir.y, player.dir.z);
	#pragma endregion
}

void OnRender() {

	T = glutGet(GLUT_ELAPSED_TIME);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z,
		player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z,
		0.0f, 1.0f, 0.0f
	);

	scene->onRender();

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float) width / height, .01f, 100.0f);
}
