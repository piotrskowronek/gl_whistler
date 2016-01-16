#include "stdafx.h"
#include "Light.h"
#include "State.h"
#include "ClosedState.h"
#include "ObjLoader.h"


Light::Light(GLuint modelListId, vec3 pos)
	: SceneObject(modelListId, pos) {
}

void Light::onRender(){
	float l0_amb[] = { 0.2f * m_light_multipler.x, 0.2f * m_light_multipler.y, 0.2f * m_light_multipler.z, 1.0f };
	float l0_dif[] = { 1.0f * m_light_multipler.x, 1.0f * m_light_multipler.y, 1.0f * m_light_multipler.z, 1.0f };
	float l0_spe[] = { 1.0f * m_light_multipler.x, 1.0f * m_light_multipler.y, 1.0f * m_light_multipler.z, 1.0f };
	float l0_pos[] = { 1.0f * m_light_multipler.x, 6.0f * m_light_multipler.y, 5.0f * m_light_multipler.z, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
}