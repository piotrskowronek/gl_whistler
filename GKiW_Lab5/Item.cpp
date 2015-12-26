#include "stdafx.h"
#include "Item.h"
#include "State.h"
#include "ClosedState.h"


Item::Item(GLuint modelListId, vec3 pos)
	: m_state(new ClosedState)
	, m_modelListId(modelListId)
	, m_pos(pos)
	, m_pos_offset()
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

void Item::changeState(State* state)
{
	m_state = state;
	m_state->initialize(this);
	m_state->onInit();
}