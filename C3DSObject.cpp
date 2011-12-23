#include "C3DSObject.h"

// установка имени
void C3DSObject::SetName(char* name)
{
	this->name = string(name);
}

void C3DSObject::ClearTexture()
{
	texture.imageData=NULL;
}

// установка текстуры
void C3DSObject::SetTexture(string FileName)
{
	ClearTexture();
	WriteLogF("Loading texture \"%s\"...", FileName.c_str());
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1,(GLuint *)&texture.texID);
	glBindTexture(GL_TEXTURE_2D,texture.texID);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_GENERATE_MIPMAP,GL_TRUE);

	string FullFileNameStr =ProgPath+"Textures\\"+FileName; 
	char *FullFileName=const_cast<char*>(FullFileNameStr.c_str());

	if (LoadTGA(&texture,FullFileName))
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		glTexImage2D (GL_TEXTURE_2D,0,GL_RGB,texture.width,texture.height,
			0,texture.type,GL_UNSIGNED_BYTE,texture.imageData);
		WriteLogF("  Loading succesfull\n");
	}
	else
		texture.imageData = NULL;
}

// установка режима фильтрации
void C3DSObject::SetFilterMode(char mode)
{
	glBindTexture(GL_TEXTURE_2D,texture.texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
	switch (mode)
	{
		case TEXTURE_FILTER_NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case TEXTURE_FILTER_LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case TEXTURE_FILTER_MIPMAP_LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case TEXTURE_FILTER_ANISOTROPY:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
			break;
	}
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
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Устанавливаем текущие буферы VBO = 0
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

C3DSObject::C3DSObject()
{
	Buffer=0;
	texture.imageData = NULL;
	VertexList = NULL;
	IndexList = NULL;
	TexVertList = NULL;
	VertexCount = 0;
	IndexCount = 0;
	wasDrawn = true;
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
