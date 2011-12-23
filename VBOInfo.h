#pragma once
#include "main.h"
#include "Material.h"

class CVBOInfo
{
public:
	GLuint buffer;
	GLsizei bufSize;
	CMaterial* material;
	bool isTransparent;
	CVBOInfo(GLuint a_buffer, GLsizei a_size, CMaterial* a_mat);
	~CVBOInfo(void);
};
