#pragma once
#include "main.h"
using namespace glm;

class COccluder
{
private:
	GLuint bufferVBO;
public:
	vec3 center;
	COccluder(GLfloat min[3], GLfloat max[3]);
	~COccluder(void);
	void Render();
};
