#include "stdafx.h"
#include "Item.h"
#include "State.h"
#include "OpenedState.h"


Item::Item(GLuint modelListId, vec3 pos)
	: m_state(shared_ptr<State>(new OpenedState))
	, m_modelListId(modelListId)
	, m_pos(pos)
	, m_pos_offset(vec3(0.0f, 0.0f, 0.0f))
{
	m_state->initialize(this);
	m_state->onInit();
}

void Item::onRender(){
	glPushMatrix();
		glTranslatef(m_pos.x + m_pos_offset.x, m_pos.y + m_pos_offset.y, m_pos.z + m_pos_offset.z);
		glCallList(m_modelListId);
	glPopMatrix();
}

void Item::onTimer(int fps){
	for (int i = 0; i < modifiers.size(); i++)
	{
		//modifiers[i].perform
	}
}

void Item::changeState(shared_ptr<State> state)
{
	m_state = state;
	m_state->initialize(this);
	m_state->onInit();
}

void Item::registerModifier(shared_ptr<Modifier> modifier)
{
	modifiers.push_back(modifier);
}