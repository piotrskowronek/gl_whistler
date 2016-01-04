#pragma once
#include "stdafx.h"
#include <vector>
#include <memory>

class TimerHandler;
class SceneObject;
class Item;

class Scene {
protected:
	vector<Item*> items;
	vector<SceneObject*> objects;
	GLuint texId;

	vector< shared_ptr< TimerHandler > > handlers;
public:
	void onInit();
	void onRender();
	void onTimer();

	void registerUpdateHandler(shared_ptr<TimerHandler>);
};