#include "C3DSObject.h"

// установка имени
void C3DSObject::SetName(char* name)
{
	this->name = string(name);
}

// вывод на экран
void C3DSObject::Render(void)
{	
	// Выбираем буферы VBO как текущие
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, Buffer);

	// выводим модель
	// включаем массивы
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	// указываем данные для массивов
	glVertexPointer(3,GL_FLOAT,0,0);
	glNormalPointer(GL_FLOAT,0,reinterpret_cast<void *>(IndexCount*3*sizeof(*VertexList)));
	
	// Применение материалов
	for (vector<CVBOInfo>::iterator _it=IndexVBO.begin() ; _it != IndexVBO.end(); _it++ )
	{
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _it->buffer);
		_it->material->Apply(reinterpret_cast<void *>(IndexCount*3*2*sizeof(*VertexList)));
		glDrawElements(GL_TRIANGLES,_it->bufSize,GL_UNSIGNED_INT,0);
	}
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glClientActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTexture(GL_TEXTURE1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Устанавливаем текущие буферы VBO = 0
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

C3DSObject::C3DSObject()
{
	Buffer=0;
	VertexList = NULL;
	IndexList = NULL;
	TexVertList = NULL;
	VertexCount = 0;
	IndexCount = 0;
	wasDrawn = true;
	isTransparent = false;
}

C3DSObject::~C3DSObject(void)
{
	// Освобождение буферов VBO
	if (Buffer!=0 && UseDestructors)
	{
		glDeleteBuffersARB(1, &Buffer);

		for (vector<CVBOInfo>::iterator _it=IndexVBO.begin() ; _it != IndexVBO.end(); _it++ )
			glDeleteBuffersARB(1, &(_it->buffer));
		delete[] IndexList;
		delete[] VertexList;
		delete[] TexVertList;
		delete occluder;
	}
}