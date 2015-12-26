#pragma once
#include "stdafx.h"

class State;

class Item
{
protected:
	GLuint m_modelListId;
	vec3 m_pos;
	State* m_state;
public:
	vec3 m_pos_offset;

	Item(GLuint modelListId, vec3 pos);
	void onRender();
	void changeState(State* state);
};
