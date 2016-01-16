#include "stdafx.h"
#include "LightModifier.h"
#include "SceneObject.h"


LightModifier::LightModifier(float duration, float from, float to, SceneObject* object, M_CALLBACK, void* context)
	: Modifier(duration, object, p, context) 
	, m_from(from)
	, m_to(to) {
}

void LightModifier::onUpdate(){
	clock_t end = clock();
	double elapsed_secs = double(end - m_birth) / CLOCKS_PER_SEC;

	m_object->m_light_multipler.x = m_from + (m_to - m_from) * elapsed_secs / m_duration;
	m_object->m_light_multipler.y = m_from + (m_to - m_from) * elapsed_secs / m_duration;
	m_object->m_light_multipler.z = m_from + (m_to - m_from) * elapsed_secs / m_duration;
	Modifier::onUpdate();
}