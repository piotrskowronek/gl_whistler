#include "stdafx.h"
#include <vector>

#pragma region Zmienne globalne

SCameraState player;

double T = 0.0;

int mouseX = 0;
int mouseY = 0;
GLuint boy;

bool captureMouse = true;
bool free3DMovement = false;

float mouseSensitivity = .15f;

// Zmienne przechowuj¹ce identyfikatory tekstur
GLuint texCheckboard_nearest;
GLuint texCheckboard_linear;
GLuint texCheckboard_linear_mm;
GLuint texCheckboard_linear_mm_linear;

#pragma endregion

struct SFace {
        int v[4];
        int n[4];
        int t[4];
};
 
GLuint LoadObj(char * file) {
 
        FILE * fp = fopen(file, "r");
 
        if (fp == NULL) {
                printf("ERROR: Cannot read model file \"%s\".\n", file);
                return -1;
        }
 
        std::vector<vec3> * v = new std::vector<vec3>();
        std::vector<vec3> * n = new std::vector<vec3>();
        std::vector<vec3> * t = new std::vector<vec3>();
        std::vector<SFace> * f = new std::vector<SFace>();
 
        char buf[128];
 
        while (fgets(buf, 128, fp) != NULL) {
                if (buf[0] == 'v' && buf[1] == ' ') {
                        vec3 * vertex = new vec3();
                        sscanf(buf, "v %f %f %f", &vertex->x, &vertex->y, &vertex->z);
                        v->push_back(*vertex);
                }
                if (buf[0] == 'v' && buf[1] == 't') {
                        vec3 * vertex = new vec3();
                        sscanf(buf, "vt %f %f", &vertex->x, &vertex->y);
                        t->push_back(*vertex);
                }
                if (buf[0] == 'v' && buf[1] == 'n') {
                        vec3 * vertex = new vec3();
                        sscanf(buf, "vn %f %f %f", &vertex->x, &vertex->y, &vertex->z);
                        n->push_back(*vertex);
                }
                if (buf[0] == 'f' && buf[1] == ' ') {
                        SFace * face = new SFace();
                        sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                                &face->v[0], &face->t[0], &face->n[0],
                                &face->v[1], &face->t[1], &face->n[1],
                                &face->v[2], &face->t[2], &face->n[2]
                        );
                        f->push_back(*face);
                }
        }
 
        fclose(fp);
 
        GLuint dlId;
        dlId = glGenLists(1);
        glNewList(dlId, GL_COMPILE);
				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glBindTexture(GL_TEXTURE_2D, texCheckboard_nearest);
                glBegin(GL_TRIANGLES);
                for (int i = 0; i < f->size(); ++i) {
                        for (int j = 0; j < 3; ++j) {
								try {
									vec3 * cv = &(*v).at(((*f)[i].v[j] - 1));
									vec3 * ct = &(*t).at(((*f)[i].t[j] - 1));
									vec3 * cn = &(*n).at(((*f)[i].n[j] - 1));

									glVertex3f(cv->x, cv->y, cv->z);
									glTexCoord2f(ct->x, ct->y);
									glNormal3f(cn->x, cn->y, cn->z);
								} catch (const std::out_of_range& oor){ 
									printf(".");
								}
                        }
                }
                glEnd();
				glDisable(GL_TEXTURE_2D);
        glEndList();
 
        delete v;
        delete n;
        delete t;
        delete f;
 
        return dlId;
 
}
 
// Wywo³anie tak utworzonej display listy w celu jej narysowania:
// glCallList(id_zwrocone_przez_LoadObj);

// Funkcja odczytuj¹ca bitmapê i tworz¹ca na jej podstawie teksturê z zadanym rodzajem filtracji
GLuint LoadTexture(char * file, int magFilter, int minFilter) {
	
	// Odczytanie bitmapy
	Bitmap *tex = new Bitmap();
	if (!tex->loadBMP(file)) {
		printf("ERROR: Cannot read texture file \"%s\".\n", file);
		return -1;
	}

	// Utworzenie nowego id wolnej tekstury
	GLuint texId;
	glGenTextures(1, &texId);

	// "Bindowanie" tekstury o nowoutworzonym id
	glBindTexture(GL_TEXTURE_2D, texId);

	// Okreœlenie parametrów filtracji dla tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // Filtracja, gdy tekstura jest powiêkszana
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // Filtracja, gdy tekstura jest pomniejszana

	// Wys³anie tekstury do pamiêci karty graficznej zale¿nie od tego, czy chcemy korzystaæ z mipmap czy nie
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST) {
		// Automatyczne zbudowanie mipmap i wys³anie tekstury do pamiêci karty graficznej
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex->width, tex->height, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}
	else {
		// Wys³anie tekstury do pamiêci karty graficznej 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}
	
	// Zwolnienie pamiêci, usuniêcie bitmapy z pamiêci - bitmapa jest ju¿ w pamiêci karty graficznej
	delete tex;
	
	// Zwrócenie id tekstury
	return texId;
}

// Funkcja, która odpowiada za za³adowanie tekstur
void LoadTextures() {
	texCheckboard_nearest = LoadTexture("Resources\\tex\\Mat_Color.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	texCheckboard_linear = LoadTexture("Resources\\checkboard.bmp", GL_LINEAR, GL_LINEAR);
	texCheckboard_linear_mm = LoadTexture("Resources\\checkboard.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	texCheckboard_linear_mm_linear = LoadTexture("Resources\\checkboard.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("GKiW: Lab 5");

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

	player.pos.x = 0.0f;
	player.pos.y = 1.0f;
	player.pos.z = 4.0f;

	player.dir.x = 0.0f;
	player.dir.y = 0.0f;
	player.dir.z = -1.0f;

	player.speed = .4f;

	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutSetCursor(GLUT_CURSOR_NONE);


	LoadTextures(); // Ka¿d¹ teksturê ³adujemy *raz* (nie w ka¿dej klatce!), np. przed wejœciem do pêtli g³ównej
	boy = LoadObj("Resources\\penguin_triangles.obj");

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
		float l0_pos[] = { 1.0f, 5.0f, 4.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

	#pragma endregion

	glBindTexture(GL_TEXTURE_2D, texCheckboard_nearest);
	glCallList(boy);

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
