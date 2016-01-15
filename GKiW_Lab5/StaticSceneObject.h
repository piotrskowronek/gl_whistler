#pragma once
#include "stdafx.h"
#include "SceneObject.h"
#include <vector>


class StaticSceneObject : public SceneObject
{
public:
	StaticSceneObject(GLuint modelListId, vec3 pos);
};
