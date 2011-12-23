#pragma once

#include "main.h"

class CTextureMap
{
	friend class CMaterial;
private:
	Texture texture;
	string filename;
	void clearTexture();
public:
	int sampler;
	GLushort options;
	void SetFileName(string);
	Texture* GetTexture();
	CTextureMap(void);
	~CTextureMap(void);
};
