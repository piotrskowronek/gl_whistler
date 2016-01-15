#include "stdafx.h"
#include "Item.h"
#include "State.h"
#include "ClosedState.h"
#include "ObjLoader.h"


Item::Item(GLuint modelListId, vec3 pos)
	: SceneObject(modelListId, pos)
	, m_state(shared_ptr<State>(new ClosedState())) {
	m_state->initialize(this);
	m_state->onInit();
}

void Item::changeState(shared_ptr<State> state)
{
	m_state = state;
	m_state->initialize(this);
	m_state->onInit();
}

shared_ptr<State> Item::getState(){
	return m_state;
}