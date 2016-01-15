#include "stdafx.h"
#include "StaticSceneObject.h"
#include "State.h"
#include "ClosedState.h"
#include "ObjLoader.h"


StaticSceneObject::StaticSceneObject(GLuint modelListId, vec3 pos)
	: SceneObject(modelListId, pos) {
}