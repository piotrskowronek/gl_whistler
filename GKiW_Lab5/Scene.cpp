#include "stdafx.h"
#include "Scene.h"
#include <tuple>
#include "Item.h"
#include "ObjLoader.h"
#include "Texture.h"
#include "Item.h"
#include "ClosedState.h"
#include "OpenedState.h"
#include "Terrain.h"
#include "TimerHandler.h"
#include "SceneObject.h"
#include "Pipe.h"
#include "MoveYModifier.h"

using namespace std;


void Scene::onInit(){
	GLuint tex = LoadObj("mario");
	GLuint tex2 = LoadObj("pipe");
	GLuint tex3 = LoadObj("floor");
	GLuint tex4 = LoadObj("arch");
	CTexture tx("Resources\\tex\\grass.bmp", texId);
	tx.Load();
	CTexture tx2("Resources\\tex\\checkboard.bmp", texId2);
	tx2.Load();

	Terrain* terr = new Terrain();
	//items.push_back(terr);

	vector< vec3 > its;
	its.push_back(vec3(3.0f, 0.0f, 0.0f));
	its.push_back(vec3(0.0f, 0.0f, 0.0f));
	its.push_back(vec3(-3.0f, 0.0f, 0.0f));
	its.push_back(vec3(1.5f, 0.0f, 2.0f));
	its.push_back(vec3(-1.5f, 0.0f, 2.0f));
	its.push_back(vec3(3.0f, 0.0f, 4.0f));
	its.push_back(vec3(0.0f, 0.0f, 4.0f));
	its.push_back(vec3(-3.0f, 0.0f, 4.0f));

	for (int i = 0; i < its.size(); i++)
	{
		Item* item = new Item(tex, its[i]);
		items.push_back(item);
		objects.push_back(item);
		SceneObject* item2 = new Pipe(tex2, its[i]);
		objects.push_back(item2);
	}

	SceneObject* item2 = new Pipe(tex3, vec3(0.0f, -0.2f, 3.0f));
	objects.push_back(item2);

	SceneObject* item4 = new Pipe(tex3, vec3(0.0f, -0.2f, -6.0f));
	objects.push_back(item4);

	SceneObject* item5 = new Pipe(tex3, vec3(0.0f, -0.2f, -12.0f));
	objects.push_back(item5);

	SceneObject* item3 = new Pipe(tex4, vec3(-5.5f, -0.2f, -3.0f));
	objects.push_back(item3);

	void* ctx = new tuple< vector<Item*>* >(&items);
	shared_ptr<Modifier> th(new MoveYModifier(0.3f, -1.3f, 0.0f, items[3], [](void* context)->void{
		tuple< vector<Item*>* >* tpl = reinterpret_cast< tuple< vector<Item*>* >* >(context);

		shared_ptr<State> p(new OpenedState);
		(*get<0>(*tpl))[3]->changeState(p);
	}, ctx));
	items[3]->registerModifier(th);

	void* ctx2 = new tuple< vector<Item*>* >(&items);
	shared_ptr<TimerHandler> th2(new TimerHandler(0.2f, false, [](void* context)->void{
		tuple< vector<Item*>* >* tpl = reinterpret_cast< tuple< vector<Item*>* >* >(context);

		shared_ptr<Modifier> the(new MoveYModifier(0.3f, -1.3f, 0.0f, (*get<0>(*tpl))[2], [](void* cont)->void{
			tuple< vector<Item*>* >* tpl = reinterpret_cast< tuple< vector<Item*>* >* >(cont);

			shared_ptr<State> p(new OpenedState);
			(*get<0>(*tpl))[2]->changeState(p);
		}, tpl));

		(*get<0>(*tpl))[2]->registerModifier(the);
	}, ctx2));
	registerUpdateHandler(th2);
}

void Scene::onTimer(){
	vector< shared_ptr< TimerHandler > >::iterator it;
	for (it = handlers.begin(); it != handlers.end(); it++)
		(*it)->onUpdate();

	it = handlers.begin();
	while (it != handlers.end()) {
		bool terminated = (*it)->isTerminated();
		if (terminated)
			it = handlers.erase(it);
		else
			it++;
	}

	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->onTimer();
	}
}

void Scene::registerUpdateHandler(shared_ptr<TimerHandler> th){
	handlers.push_back(th);
	th->windUpClock();
}

void Scene::onRender(){
	#pragma region Swiatlo
		float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_pos[] = { 1.0f, 6.0f, 5.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
	#pragma endregion
	/*
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(l0_pos[0], l0_pos[1], l0_pos[2]);
		glutSolidCube(1.0f);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidCube(1.0f);
		glEnable(GL_LIGHTING);
	glPopMatrix();*/

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->onRender();
	}

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.0f, 0.0f);
		glScalef(10.0, 5.0f, 10.0f);
		glTranslatef(0.0f, -0.55f, 0.0f);
		glutSolidCube(1.0f);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	/*glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_GEN_S);	
		glEnable(GL_TEXTURE_GEN_T);
		glBindTexture(GL_TEXTURE_2D, texId2);
		glScalef(10.0, 5.0f, 10.0f);
		glTranslatef(1.0f, -0.55f, 0.0f);
		glutSolidCube(1.0f);
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	glPopMatrix();*/
}