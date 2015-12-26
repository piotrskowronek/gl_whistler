#include "stdafx.h"
#include <vector>
#include "ObjLoader.h"
#include "Texture.h"
#include "Item.h"

#pragma region Zmienne globalne

SCameraState player;

double T = 0.0;

int mouseX = 0;
int mouseY = 0;


bool captureMouse = true;
bool free3DMovement = true;

float mouseSensitivity = .15f;

vector<Item*> items;
GLuint texId;

#pragma endregion

void LoadTextures() {
	CTexture tex("Resources\\tex\\Mat_Color.bmp");
	texId = tex.Load();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("glWhistler");

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
	
	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	player.pos.x = 0.081256f;
	player.pos.y = 3.542898f;
	player.pos.z = 8.002872f;

	player.dir.x = -0.011955f;
	player.dir.y = -0.464438f;
	player.dir.z = -0.885525f;

	player.speed = .4f;

	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutSetCursor(GLUT_CURSOR_NONE);


	LoadTextures();
	GLuint tex = LoadObj("Resources\\penguin_triangles.obj", texId);

	vec3 pos = {2.0f, 0.0f, 0.0f};
	Item* item = new Item(tex, pos);
	items.push_back(item);

	vec3 pos2 = {0.0f, 0.0f, 0.0f};
	Item* item2 = new Item(tex, pos2);
	items.push_back(item2);

	vec3 pos3 = {-2.0f, 0.0f, 0.0f};
	Item* item3 = new Item(tex, pos3);
	items.push_back(item3);

	vec3 pos4 = {1.0f, 0.0f, 2.0f};
	Item* item4 = new Item(tex, pos4);
	items.push_back(item4);

	vec3 pos5 = {-1.0f, 0.0f, 2.0f};
	Item* item5 = new Item(tex, pos5);
	items.push_back(item5);

	vec3 pos6 = {2.0f, 0.0f, 4.0f};
	Item* item6 = new Item(tex, pos6);
	items.push_back(item6);

	vec3 pos7 = {0.0f, 0.0f, 4.0f};
	Item* item7 = new Item(tex, pos7);
	items.push_back(item7);

	vec3 pos8 = {-2.0f, 0.0f, 4.0f};
	Item* item8 = new Item(tex, pos8);
	items.push_back(item8);

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

	glutTimerFunc(17, OnTimer, 0);

	#pragma region Ruch kamery

	if (captureMouse) {
		player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
		player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}

	if (keystate['w']) {
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
	}

	float T = acos(player.dir.y);
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
	player.velS /= 1.2;

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

	#pragma region Swiatlo
		float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_pos[] = { 1.0f, 5.0f, 6.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
	#pragma endregion

	for (size_t i = 0; i < items.size(); i++)
	{
		items[i]->onRender();
	}

	glDisable(GL_LIGHT0);
	glPushMatrix();
		glScalef(10.0, 0.3f, 10.0f);
		glTranslatef(0.0f, 1.3f, 0.0f);
		glutSolidCube(1.0f);
	glPopMatrix();
	glEnable(GL_LIGHT0);

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
