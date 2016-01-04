#include "stdafx.h"
#include "SceneObject.h"
#include "State.h"
#include "ClosedState.h"
#include "ObjLoader.h"


SceneObject::SceneObject(GLuint modelListId, vec3 pos)
	: m_modelListId(modelListId)
	, m_pos(pos)
	, m_pos_offset(vec3(0.0f, 0.0f, 0.0f)) {
}

void SceneObject::onRender(){
	glPushMatrix();
		glTranslatef(m_pos.x + m_pos_offset.x, m_pos.y + m_pos_offset.y, m_pos.z + m_pos_offset.z);
		glCallList(m_modelListId);
	glPopMatrix();
}

void SceneObject::onTimer(){
	vector< shared_ptr< Modifier > >::iterator it;
	for (it = modifiers.begin(); it != modifiers.end(); it++)
		(*it)->onUpdate();

	it = modifiers.begin();
	while (it != modifiers.end()) {
		bool terminated = (*it)->isTerminated();
		if (terminated)
			it = modifiers.erase(it);
		else
			it++;
	}
}

void SceneObject::registerModifier(shared_ptr<Modifier> modifier)
{
	modifiers.push_back(modifier);
	modifier->windUpClock();
}