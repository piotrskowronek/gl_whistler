#pragma once
#include "stdafx.h"
#include "SceneObject.h"
#include <vector>


class Light : public SceneObject
{
public:
	Light(GLuint modelListId, vec3 pos);
	void onRender();
};
