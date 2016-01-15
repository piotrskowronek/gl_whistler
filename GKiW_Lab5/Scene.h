#pragma once
#include "stdafx.h"
#include <vector>
#include <memory>

class TimerHandler;
class SceneObject;
class Item;

class Scene {
protected:
	vector<SceneObject*> objects;
	GLuint texId, texId2;

	vector< shared_ptr< TimerHandler > > handlers;
public:
	//outer
	vector<Item*> items;

	void onInit();
	void onRender();
	void onTimer();

	void start();

	void registerUpdateHandler(shared_ptr<TimerHandler>);
};