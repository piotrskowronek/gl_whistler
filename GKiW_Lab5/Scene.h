#pragma once
#include "stdafx.h"
#include <vector>
#include <memory>
#include <time.h>

class TimerHandler;
class SceneObject;
class Item;

class Scene {
protected:
	vector<SceneObject*> objects;
	GLuint texId, texId2;
	clock_t m_gameStartTime;

	vector< shared_ptr< TimerHandler > > handlers;
public:
	//outer
	vector<Item*> items;

	void onInit();
	void onRender();
	void onTimer();
	void onKeyDown(unsigned char key, int x, int y);

	void start();

	void registerUpdateHandler(shared_ptr<TimerHandler>);
	void unregisterUpdateHandler(shared_ptr<TimerHandler>);
};