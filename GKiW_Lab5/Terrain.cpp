#include "stdafx.h"
#include "Terrain.h"
#include "Texture.h"


Terrain::Terrain()
	: Item(0, vec3())
{
	m_grassTexture = new CTexture("Resources\\tex\\metal.bmp");
	m_grassTexture->Load();

	GLuint texture = glGenLists(1);

	float size = 50.0f;
	int N = 10;
	
	glNewList(m_displayListId, GL_COMPILE);
		glBegin(GL_QUADS);
		for (int x = 0; x < N; ++x) {
			for (int y = 0; y < N; ++y) {
				glTexCoord2f(size * (x + 1) / N, size * y / N);
				glVertex3f(size * (x + 1 - N/2) / N, 0.0f, size * (y - N/2) / N);
			
				glTexCoord2f(size * x / N, size * y / N);
				glVertex3f(size * (x - N/2) / N, 0.0f, size * (y - N/2) / N);
			
				glTexCoord2f(size * x / N, size * (y + 1) / N);
				glVertex3f(size * (x - N/2) / N, 0.0f, size * (y + 1 - N/2) / N);
			
				glTexCoord2f(size * (x + 1) / N, size * (y + 1) / N);
				glVertex3f(size * (x + 1 - N/2) / N, 0.0f, size * (y + 1 - N/2) / N);
			}
		}
		glEnd();
	glEndList();
}

void Terrain::onTimer()
{
}

void Terrain::onRender()
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_grassTexture->GetId());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glCallList(m_displayListId);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
