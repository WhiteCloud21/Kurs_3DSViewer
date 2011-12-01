#include "C3DS.h"

// установка режима фильтрации
void C3DS::SetFilterMode(char mode)
{
	for (uint i = 0; i < objects.size(); i++)
		objects[i]->SetFilterMode(mode);
}

// загрузка файла 3ds
bool C3DS::Load(const char *FileName, Shader* shader)
{
	C3DSObject * currentObject = NULL;
	UseDestructors=false;

	bool MeshFirst=false;

	WriteLogF("Loading scene \"%s\"...", FileName);
	
	// Файл модели
	ifstream ModelF(FileName, ios::in|ios::binary);

	// Файл существует
	if (ModelF!=NULL)
	{
		ModelF.seekg(0);

		// Идентификатор, определяет тип блока (2 байта)
		unsigned short chunk_id;

		// Длина блока в байтах (4 байта)
		unsigned int chunk_len;

		unsigned short *TempPtr;

		while(ModelF.good())
		{
			int gp;
			// Читаем заголовок чанка
			ModelF.read((char *)&chunk_id,2);
			ModelF.read((char *)&chunk_len,4);
			WriteLogF("  Chunk ID = 0x%hX Length = %u",chunk_id,chunk_len);
			switch (chunk_id)
			{
			// Чанки, которые НЕ пропускаем
			case 0x4D4D: //MAIN3DS
			case 0x3D3D: //EDIT3DS
				break;
			case 0x4100: //OBJ_TRIMESH
				MeshFirst=!MeshFirst;
				if (!MeshFirst)
				{
					// ВРЕМЕННО Пропускаем чанк
					ModelF.ignore(chunk_len-6);
					WriteLogF("   IGNORING, not first OBJ_TRIMESH");
				}
				break;
			case 0x4000: //EDIT_OBJECT
				MeshFirst = false;
				currentObject = new C3DSObject();
				objects.push_back(currentObject);
				gp = ModelF.tellg();
				// Читаем имя объекта
				ModelF.read(currentObject->name, 255);
				// Если прочитали лишнего, возвращаемся
				ModelF.seekg(gp+strlen(currentObject->name)+1, ios::beg);
				break;
			case 0x4110: //POINT_ARRAY
				// Читаем массив вершин
				ModelF.read((char *)&(currentObject->VertexCount),2);
				currentObject->VertexList = new GLfloat[currentObject->VertexCount*6];
				ModelF.read((char *)currentObject->VertexList,currentObject->VertexCount*sizeof(GLfloat)*3);
				// Добавляем в массив цвет!
				for (int i=currentObject->VertexCount; i< currentObject->VertexCount*2; ++i)
				{
					currentObject->VertexList[3*i]=currentObject->color.r;
					currentObject->VertexList[3*i+1]=currentObject->color.g;
					currentObject->VertexList[3*i+2]=currentObject->color.b;
				}
				WriteLogF(" VertexCount = %hu",currentObject->VertexCount);
				break;
			case 0x4120: //FACE_ARRAY
				// Читаем массив индексов
				ModelF.read((char *)&(currentObject->IndexCount),2);
				currentObject->IndexList = new unsigned short[currentObject->IndexCount*3];
				TempPtr=currentObject->IndexList;
				for (int i=0;i<currentObject->IndexCount;++i)
				{
					ModelF.read((char *)TempPtr,sizeof(unsigned short)*3);
					TempPtr+=3;
					// Пропускаем ненужный параметр
					ModelF.ignore(sizeof(unsigned short));
				}
				currentObject->IndexCount*=3;
				WriteLogF(" IndexCount = %hu",currentObject->IndexCount);
				break;
			case 0x4140: //TEX_VERTS
				// Читаем массив текст. координат
				ModelF.read((char *)&(currentObject->TexVertCount),2);
				currentObject->TexVertList = new GLfloat[currentObject->TexVertCount*2];
				ModelF.read((char *)currentObject->TexVertList,currentObject->TexVertCount*sizeof(GLfloat)*2);
				WriteLogF(" TextureVertexCount = %hu",currentObject->TexVertCount);
				break;
			case 0x4160: //MESH_MATRIX
				// Считывание матрицы
				ModelF.read((char *)currentObject->LocalMatrix,sizeof(currentObject->LocalMatrix));
				break;
			default:
				// Пропускаем чанк
				ModelF.ignore(chunk_len-6);
				WriteLogF("   IGNORING");
				break;
			}
		}

		if (objects.size() > 0 && objects.back()->VertexCount == 0)
			objects.pop_back();

		for (uint _objNum = 0; _objNum < objects.size(); _objNum++)
		{
			currentObject = objects[_objNum];
			// Преобразования систем координат
			for(int i=0;i<currentObject->VertexCount;++i)//y и z поменяны местами
					{
							//Надо сначала сдвинуть его назад, то есть на вектор
							//-offset (НЕ на offset),
							// x
							currentObject->VertexList[3*i]-=currentObject->LocalMatrix[9];
							// z
							currentObject->VertexList[3*i+1]-=currentObject->LocalMatrix[10];
							// y
							currentObject->VertexList[3*i+2]-=currentObject->LocalMatrix[11];
							//а потом применить матрицу поворота rotmatr
							//Матрица записана построчно
							//В ней y и z тоже везде обменены местами!
							GLfloat x0=-currentObject->VertexList[3*i];
							GLfloat x1=-currentObject->VertexList[3*i+1];
							GLfloat x2=-currentObject->VertexList[3*i+2];
							currentObject->VertexList[3*i]=currentObject->LocalMatrix[0]*x0+currentObject->LocalMatrix[2]*x1+currentObject->LocalMatrix[1]*x2;
							currentObject->VertexList[3*i+2]=currentObject->LocalMatrix[3]*x0+currentObject->LocalMatrix[5]*x1+currentObject->LocalMatrix[4]*x2;
							currentObject->VertexList[3*i+1]=currentObject->LocalMatrix[6]*x0+currentObject->LocalMatrix[8]*x1+currentObject->LocalMatrix[7]*x2;
					}

			// дублирование вершин
			GLfloat *VertexListCopy=new GLfloat[currentObject->IndexCount*4*2];//+нормали+текстурные координаты
			for(int i=0;i<currentObject->IndexCount;++i)
			{
				for(int k=0;k<3;++k)	
					VertexListCopy[3*i+k]=currentObject->VertexList[3*currentObject->IndexList[i]+k];
				for(int k=0;k<2;++k)	
					// добавление текстурных координат
					VertexListCopy[currentObject->IndexCount*3*2+2*i+k]=currentObject->TexVertList[2*currentObject->IndexList[i]+k];
			}

			// Вычисление нормалей
			for(int i=0;i<currentObject->IndexCount/3;++i)
			{
				//A2A1
				vec3 a1=vec3(VertexListCopy[3*(3*i+2)]-VertexListCopy[3*(3*i+1)], VertexListCopy[3*(3*i+2)+1]-VertexListCopy[3*(3*i+1)+1], VertexListCopy[3*(3*i+2)+2]-VertexListCopy[3*(3*i+1)+2]);
				//A0A1
				vec3 a2=vec3(VertexListCopy[3*3*i]-VertexListCopy[3*(3*i+1)], VertexListCopy[3*3*i+1]-VertexListCopy[3*(3*i+1)+1], VertexListCopy[3*3*i+2]-VertexListCopy[3*(3*i+1)+2]);
				vec3 normal=normalize(-cross(a1, a2));
				//устанавливаем нормаль для каждой из 3 вершин
				for(int j=0;j<3;++j)
					for(int k=0;k<3;++k)
						VertexListCopy[currentObject->IndexCount*3+i*9+j*3+k]=normal[k];
			}
			// VBO
			// Получаем свободный идентификатор
			glGenBuffersARB(1, &currentObject->Buffer);

			// Выбираем буферы как текущие
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, currentObject->Buffer);
			//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Buffers[1]);

			// Заполнение буферов VBO
			glBufferDataARB(GL_ARRAY_BUFFER_ARB,sizeof(GLfloat)*6*currentObject->IndexCount+sizeof(GLfloat)*2*currentObject->IndexCount,VertexListCopy,GL_STATIC_DRAW_ARB);
			//glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,sizeof(unsigned short)*IndexCount,IndexList,GL_STATIC_DRAW_ARB);

			// Устанавливаем текущие буферы VBO = 0
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

			//printf("  Loading successful. Using buffers %u and %u\n", Buffers[0], Buffers[1]);
			WriteLogF("  Loading successful. Using buffer %u\n", currentObject->Buffer);
			delete[] VertexListCopy;
			currentObject->shader=shader;
		}
		return true;
	}
	else
	{
		WriteLogF("  Error: File not found.\n");
		return false;
	}
	
	UseDestructors=true;
}

// вывод на экран
void C3DS::Render(void)
{
	for (uint i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

C3DS::C3DS()
{

}

C3DS::~C3DS(void)
{
	for (uint i = 0; i < objects.size(); i++)
		delete objects[i];
	objects.clear();
}
