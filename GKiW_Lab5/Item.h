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
	Item(GLuint modelListId, vec3 pos);
	void changeState(shared_ptr<State> state);
};
