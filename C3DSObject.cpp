#include "C3DSObject.h"

// установка позиции
void C3DSObject::SetPos(GLfloat x, GLfloat y, GLfloat z)
{
	position=vec3(x,y,z);
}

// установка цвета
void C3DSObject::SetColor(GLfloat r, GLfloat g, GLfloat b)
{
	color=vec3(r,g,b);
}

// установка масштаба
void C3DSObject::SetScale(GLfloat newscale)
{
	scale=newscale;
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

//// загрузка файла 3ds и запись в буферы VBO
//bool C3DSObject::Load(const char *FileName, Shader* shader)
//{
//	bool MeshFirst=false, Flag=true;
//
//	WriteLogF("Loading object \"%s\"...", FileName);
//	
//	// Файл модели
//	ifstream ModelF(FileName, ios::in|ios::binary);
//
//	// Файл существует
//	if (ModelF!=NULL)
//	{
//		ModelF.seekg(0);
//
//		// Идентификатор, определяет тип блока (2 байта)
//		unsigned short chunk_id;
//
//		// Длина блока в байтах (4 байта)
//		unsigned int chunk_len;
//
//		unsigned short *TempPtr;
//		float Local[12]={0.0f};
//
//		while(Flag && ModelF.good())
//		{
//			int gp;
//			// Читаем заголовок чанка
//			ModelF.read((char *)&chunk_id,2);
//			ModelF.read((char *)&chunk_len,4);
//			WriteLogF("  Chunk ID = 0x%hX Length = %u",chunk_id,chunk_len);
//			switch (chunk_id)
//			{
//			// Чанки, которые НЕ пропускаем
//			case 0x4D4D: //MAIN3DS
//			case 0x3D3D: //EDIT3DS
//				break;
//			case 0x4100: //OBJ_TRIMESH
//				Flag=(MeshFirst=!MeshFirst);
//				break;
//			case 0x4000: //EDIT_OBJECT
//				gp = ModelF.tellg();
//				// Читаем имя объекта
//				ModelF.read(name, 255);
//				// Если прочитали лишнего, возвращаемся
//				ModelF.seekg(gp+strlen(name)+1, ios::beg);
//				break;
//			case 0x4110: //POINT_ARRAY
//				// Читаем массив вершин
//				ModelF.read((char *)&VertexCount,2);
//				VertexList = new GLfloat[VertexCount*6];
//				ModelF.read((char *)VertexList,VertexCount*sizeof(GLfloat)*3);
//				// Добавляем в массив цвет!
//				for (int i=VertexCount; i< VertexCount*2; ++i)
//				{
//					VertexList[3*i]=color.r;
//					VertexList[3*i+1]=color.g;
//					VertexList[3*i+2]=color.b;
//				}
//				WriteLogF(" VertexCount = %hu",VertexCount);
//				break;
//			case 0x4120: //FACE_ARRAY
//				// Читаем массив индексов
//				ModelF.read((char *)&IndexCount,2);
//				IndexList = new unsigned short[IndexCount*3];
//				TempPtr=IndexList;
//				for (int i=0;i<IndexCount;++i)
//				{
//					ModelF.read((char *)TempPtr,sizeof(unsigned short)*3);
//					TempPtr+=3;
//					// Пропускаем ненужный параметр
//					ModelF.ignore(sizeof(unsigned short));
//				}
//				IndexCount*=3;
//				WriteLogF(" IndexCount = %hu",IndexCount);
//				break;
//			case 0x4140: //TEX_VERTS
//				// Читаем массив текст. координат
//				ModelF.read((char *)&TexVertCount,2);
//				TexVertList = new GLfloat[TexVertCount*2];
//				ModelF.read((char *)TexVertList,TexVertCount*sizeof(GLfloat)*2);
//				WriteLogF(" TextureVertexCount = %hu",TexVertCount);
//				break;
//			case 0x4160: //MESH_MATRIX
//				// Считывание матрицы
//				ModelF.read((char *)Local,sizeof(Local));
//				break;
//			default:
//				// Пропускаем чанк
//				ModelF.ignore(chunk_len-6);
//				WriteLogF("   IGNORING");
//				break;
//			}
//		}
//
//		// Преобразования систем координат
//		for(int i=0;i<VertexCount;++i)//y и z поменяны местами
//        {
//            //Надо сначала сдвинуть его назад, то есть на вектор
//            //-offset (НЕ на offset),
//			// x
//            VertexList[3*i]-=Local[9];
//			// z
//            VertexList[3*i+1]-=Local[10];
//			// y
//            VertexList[3*i+2]-=Local[11];
//            //а потом применить матрицу поворота rotmatr
//            //Матрица записана построчно
//            //В ней y и z тоже везде обменены местами!
//            float x0=VertexList[3*i];
//            float x1=VertexList[3*i+1];
//            float x2=VertexList[3*i+2];
//            VertexList[3*i]=x0*scale;
//            VertexList[3*i+1]=x2*scale;
//            VertexList[3*i+2]=x1*scale;
//        }
//
//		// дублирование вершин
//		GLfloat *VertexListCopy=new GLfloat[IndexCount*3*2+IndexCount*2];//+нормали+текстурные координаты
//		for(int i=0;i<IndexCount;++i)
//		{
//			for(int k=0;k<3;++k)	
//				VertexListCopy[3*i+k]=VertexList[3*IndexList[i]+k];
//			for(int k=0;k<2;++k)	
//				// добавление текстурных координат
//				VertexListCopy[IndexCount*3*2+2*i+k]=TexVertList[2*IndexList[i]+k];
//		}
//
//		// Вычисление нормалей
//		for(int i=0;i<IndexCount/3;++i)
//		{
//			//A2A1
//			vec3 a1=vec3(VertexListCopy[3*(3*i+2)]-VertexListCopy[3*(3*i+1)], VertexListCopy[3*(3*i+2)+1]-VertexListCopy[3*(3*i+1)+1], VertexListCopy[3*(3*i+2)+2]-VertexListCopy[3*(3*i+1)+2]);
//			//A0A1
//			vec3 a2=vec3(VertexListCopy[3*3*i]-VertexListCopy[3*(3*i+1)], VertexListCopy[3*3*i+1]-VertexListCopy[3*(3*i+1)+1], VertexListCopy[3*3*i+2]-VertexListCopy[3*(3*i+1)+2]);
//			vec3 normal=normalize(-cross(a1, a2));
//			//устанавливаем нормаль для каждой из 3 вершин
//			for(int j=0;j<3;++j)
//				for(int k=0;k<3;++k)
//					VertexListCopy[IndexCount*3+i*9+j*3+k]=normal[k];
//		}
//		// VBO
//		// Получаем свободный идентификатор
//		glGenBuffersARB(1, &Buffer);
//
//		// Выбираем буферы как текущие
//		glBindBufferARB(GL_ARRAY_BUFFER_ARB, Buffer);
//		//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Buffers[1]);
//
//		// Заполнение буферов VBO
//		glBufferDataARB(GL_ARRAY_BUFFER_ARB,sizeof(GLfloat)*6*IndexCount+sizeof(GLfloat)*2*IndexCount,VertexListCopy,GL_STATIC_DRAW_ARB);
//		//glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,sizeof(unsigned short)*IndexCount,IndexList,GL_STATIC_DRAW_ARB);
//
//		// Устанавливаем текущие буферы VBO = 0
//		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
//		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
//
//		//printf("  Loading successful. Using buffers %u and %u\n", Buffers[0], Buffers[1]);
//		WriteLogF("  Loading successful. Using buffer %u\n", Buffer);
//		delete[] VertexListCopy;
//		C3DSObject::shader=shader;
//		return true;
//	}
//	else
//	{
//		WriteLogF("  Error: File not found.\n");
//		return false;
//	}
//}

// вывод на экран
void C3DSObject::Render(void)
{
	GLfloat ModelMatrix[16]={
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	ModelMatrix[12]=position.x;
	ModelMatrix[13]=position.y;
	ModelMatrix[14]=position.z;
	
	// Выбираем буферы VBO как текущие
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, Buffer);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Buffers[1]);

	glPushMatrix();
	// умножаем матрицу камеры на матрицу трансформации объекта
	glMultMatrixf(ModelMatrix);
	// выводим модель
	// данные текстуры
	if (texture.imageData != NULL)
	{
		// Индекс семплера
		int sampler = glGetUniformLocation(shader->PShader, "MyTex");

		// Установка текущего ТБ
		glUniform1i(sampler,0);

		// Связывание ТБ с текустурой
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture.texID);

		// Включение массива текстурных координат
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		// Передача текстурных координат
		glTexCoordPointer(2,GL_FLOAT,0,
			reinterpret_cast<void *>(IndexCount*3*2*sizeof(*VertexList)));
	}
	// включаем массивы
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	// указываем данные для массивов
	glVertexPointer(3,GL_FLOAT,0,0);
	//glColorPointer(3,GL_FLOAT,0,reinterpret_cast<void *>(VertexCount*3*sizeof(*VertexList)));
	glNormalPointer(GL_FLOAT,0,reinterpret_cast<void *>(IndexCount*3*sizeof(*VertexList)));
	// вывод полигонов
	//glDrawElements(GL_TRIANGLES,IndexCount,GL_UNSIGNED_SHORT,0);
	glDrawArrays(GL_TRIANGLES,0,IndexCount);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	// востанавливаем матрицу камеры
	glPopMatrix();

	// Устанавливаем текущие буферы VBO = 0
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

}

C3DSObject::C3DSObject()
{
	scale=1;
	Buffer=0;
	color = vec3(0,0,1);
	texture.imageData = NULL;
	VertexList = NULL;
	IndexList = NULL;
	VertexCount = 0;
	IndexCount = 0;
}

C3DSObject::~C3DSObject(void)
{
	// Освобождение буферов VBO
	if (Buffer!=0 && UseDestructors)
	{
		glDeleteBuffersARB(1, &Buffer);
		delete[] IndexList;
		delete[] VertexList;
		delete[] TexVertList;
	}
}
