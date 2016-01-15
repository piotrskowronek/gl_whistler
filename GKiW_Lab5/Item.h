#pragma once
#include "stdafx.h"
#include "SceneObject.h"
#include <vector>

class State;

class Item : public SceneObject
{
protected:
	shared_ptr<State> m_state;
public:
	unsigned char m_key;

	Item(GLuint modelListId, vec3 pos, unsigned char key);
	void changeState(shared_ptr<State> state);
	shared_ptr<State> getState();
	void onKeyDown(unsigned char key, int x, int y);
};
