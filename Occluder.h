#pragma once
#include "main.h"


class COccluder
{
private:
	GLuint bufferVBO;
public:
	COccluder(GLfloat min[3], GLfloat max[3]);
	~COccluder(void);
	void Render();
};
