#pragma once
#include "stdafx.h"
#include "Modifier.h"

class SceneObject;

class MoveYModifier : public Modifier
{
private:
	float m_from;
	float m_to;
public:
	MoveYModifier(float duration, float from, float to, SceneObject* object, M_CALLBACK, void* context);
	void onUpdate();
};