#pragma once
#include "stdafx.h"
#include "SceneObject.h"
#include <vector>


class Pipe : public SceneObject
{
public:
	Pipe(GLuint modelListId, vec3 pos);
};
