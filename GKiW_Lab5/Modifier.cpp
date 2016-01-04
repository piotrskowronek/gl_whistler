#include "stdafx.h"
#include "Modifier.h"
#include "SceneObject.h"
#include <time.h>


Modifier::Modifier(float duration, SceneObject* object, M_CALLBACK, void* context)
	: m_duration(duration)
	, m_object(object)
	, m_context(context)
	, m_birth(clock())
{
	this->p = p;
}

Modifier::~Modifier(){
	delete m_context;
}

void Modifier::windUpClock(){
	m_birth = clock();
}

void Modifier::onUpdate(){
	if ( isReadyToTick() )
		p(m_context);
}

bool Modifier::isTerminated(){
	bool ready = isReadyToTick();
	if ( ready )
		m_birth = clock();

	return ready;
}

bool Modifier::isReadyToTick(){
	clock_t end = clock();
	double elapsed_secs = double(end - m_birth) / CLOCKS_PER_SEC;
	
	if ( elapsed_secs >= m_duration )
		return true;
	return false;
}