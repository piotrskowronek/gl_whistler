#pragma once
#include "stdafx.h"
#include <vector>
#include "Modifier.h"


class SceneObject
{
protected:
	GLuint m_modelListId;
	vec3 m_pos;
	vector< shared_ptr<Modifier> > modifiers;
public:
	vec3 m_pos_offset;

	SceneObject(GLuint modelListId, vec3 pos);
	void onTimer();
	void onRender();

	void registerModifier(shared_ptr<Modifier> modifier);
};
