#pragma once

// Tekstura.
class CTexture
{
public:
	bool IsLoaded;

	CTexture(char*, GLuint id);
	CTexture(char*);
	~CTexture(void);
	bool Load(void);
	GLuint GetId(void);

protected:
	int _magFilter;
	int _minFilter;
	char * _file;
	GLuint _id;
};

