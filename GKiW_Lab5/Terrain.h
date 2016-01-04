#pragma once
#include "Item.h"

class CTexture;

class Terrain : public Item
{
protected:
	GLuint m_displayListId;
	CTexture* m_grassTexture;
public:
	Terrain();
	void onTimer();
	void onRender();
};

