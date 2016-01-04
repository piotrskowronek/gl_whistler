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
	for (int i = 0; i < modifiers.size(); i++)
	{
		//modifiers[i].perform
	}
}

void SceneObject::registerModifier(shared_ptr<Modifier> modifier)
{
	modifiers.push_back(modifier);
}