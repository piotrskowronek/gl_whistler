#include "stdafx.h"
#include "MoveYModifier.h"
#include "SceneObject.h"


MoveYModifier::MoveYModifier(float duration, float from, float to, SceneObject* object, M_CALLBACK, void* context)
	: Modifier(duration, object, p, context) 
	, m_from(from)
	, m_to(to) {
}

void MoveYModifier::onUpdate(){
	clock_t end = clock();
	double elapsed_secs = double(end - m_birth) / CLOCKS_PER_SEC;

	m_object->m_pos_offset.y = m_from + (m_to - m_from) * elapsed_secs / m_duration;
	Modifier::onUpdate();
}