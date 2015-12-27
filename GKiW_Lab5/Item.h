#pragma once
#include "stdafx.h"
#include <vector>

class State;
class Modifier;

class Item
{
protected:
	GLuint m_modelListId;
	vec3 m_pos;
	shared_ptr<State> m_state;
	vector< shared_ptr<Modifier> > modifiers;
public:
	vec3 m_pos_offset;

	Item(GLuint modelListId, vec3 pos);
	void onRender();
	void onTimer(int fps);
	void changeState(shared_ptr<State> state);
	void registerModifier(shared_ptr<Modifier> modifier);
};
