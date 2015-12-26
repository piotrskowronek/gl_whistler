#include "stdafx.h"
#include "Item.h"


Item::Item(GLuint modelListId, vec3 pos)
	: m_modelListId(modelListId)
	, m_pos(pos)
{
}

void Item::onRender(){
	glPushMatrix();
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		glCallList(m_modelListId);
	glPopMatrix();
}