#pragma once
#include "stdafx.h"
#include <memory>
#include <time.h>
#define M_CALLBACK void (*p)(void*)

class SceneObject;

class Modifier {
protected:
	float m_duration;
	SceneObject* m_object;
	void* m_context;
	clock_t m_birth;
	M_CALLBACK;
public:
	Modifier(float duration, SceneObject* object, M_CALLBACK, void* context);
	~Modifier();
	void windUpClock();
	virtual void onUpdate();
	bool isTerminated();
private:
	bool isReadyToTick();
};