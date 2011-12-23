#include "Occluder.h"

GLuint occluderBufferVBOIndex;

//GLEE_ARB_occlusion_query
COccluder::COccluder(GLfloat min[3], GLfloat max[3])
{
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
	glGenBuffersARB(1, &bufferVBO);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, bufferVBO);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB,sizeof(GLfloat)*8*3,_coords,GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

COccluder::~COccluder(void)
{	
	if (bufferVBO!=0)
		glDeleteBuffersARB(1, &bufferVBO);
}

void COccluder::Render()
{	
	// Выбираем буферы VBO как текущие
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, bufferVBO);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, occluderBufferVBOIndex);

	// указываем данные для массивов
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,0);
	
	// выводим occluder
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT,0);

	glDisableClientState(GL_VERTEX_ARRAY);

	// Устанавливаем текущие буферы VBO = 0
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}
