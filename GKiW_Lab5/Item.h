#pragma once
#include "stdafx.h"

class Item
{
protected:
	GLuint m_modelListId;
	vec3 m_pos;
public:
	Item(GLuint modelListId, vec3 pos);
	void onRender();
};
