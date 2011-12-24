#include "Occluder.h"

GLuint occluderBufferVBOIndex;

//GLEE_ARB_occlusion_query
COccluder::COccluder(GLfloat min[3], GLfloat max[3])
{
	GLushort _indicies[] = {0, 1, 2, 3, 
													4, 5, 6, 7, 
													0, 1, 5, 4, 
													3, 2, 6, 7, 
													1, 5, 6, 2, 
													0, 4, 7, 3};
	GLfloat _coords[8][3] = {
		{ min[0], min[1], min[2] },
		{ min[0], min[1], max[2] },
		{ min[0], max[1], max[2] },
		{ min[0], max[1], min[2] },
		{ max[0], min[1], min[2] },
		{ max[0], min[1], max[2] },
		{ max[0], max[1], max[2] },
		{ max[0], max[1], min[2] },
	};

	GLfloat _data[24][3];
	for (int i = 0; i < 24; ++i)
	{
		_data[i][0] = _coords[_indicies[i]][0];
		_data[i][1] = _coords[_indicies[i]][1];
		_data[i][2] = _coords[_indicies[i]][2];
	}
	glGenBuffersARB(1, &bufferVBO);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, bufferVBO);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB,sizeof(GLfloat)*24*3,_data,GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	center = vec3(max[0]-min[0], max[1]-min[1], max[2]-min[2]);
}

COccluder::~COccluder(void)
{	
	if (bufferVBO!=0)
		glDeleteBuffersARB(1, &bufferVBO);
}

void COccluder::Render()
{	
	// Для OC
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);

	// Выбираем буферы VBO как текущие
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, bufferVBO);

	// указываем данные для массивов
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,0);
	
	// выводим occluder
	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);

	// Устанавливаем текущие буферы VBO = 0
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Разрешение записи в буферы цвета и глубины
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);

	if (!CullFaceFlag)
		glEnable(GL_CULL_FACE);
}
