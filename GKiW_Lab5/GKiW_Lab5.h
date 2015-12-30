#pragma once

#define PI 3.14159265

// Deklaracje funkcji u¿ywanych jako obs³uga zdarzeñ GLUT-a.
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnMouseMove(int, int);
void OnTimer(int);

struct vec3 {
	float x, y, z;

	vec3(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3(){
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}
};

struct SCameraState {
	vec3 pos;
	vec3 dir;
	float speed;
	float velRX, velRY, velM, velS;
};
