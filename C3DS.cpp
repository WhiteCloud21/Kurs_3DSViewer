#include "C3DS.h"

// загрузка файла 3ds
extern bool Load3DSFile(const char *FileName, vector<C3DSObject*> &objects, vector<CCamera*> &cameras, vector<CLight*> &lights, vector<CMaterial*> &materials);

// установка режима фильтрации
void C3DS::SetFilterMode(char mode)
{
	for (uint i = 0; i < objects.size(); i++)
		objects[i]->SetFilterMode(mode);
}

// Получение текущей камеры
CCamera* C3DS::GetCurrentCamera()
{
	return cameras[cameraIndex];
}

// Получение следующей камеры
CCamera* C3DS::GetNextCamera()
{
	return cameras[(++cameraIndex)%cameras.size()];
}

// Получение текущего источника света
CLight* C3DS::GetCurrentLight()
{
	if (lightIndex >= 0)
		return lights[lightIndex];
	else
		return NULL;
}

// Получение следующего источника света
CLight* C3DS::GetNextLight()
{
	if (lightIndex >= 0)
		return lights[(++lightIndex)%lights.size()];
	else
		return NULL;
}

// загрузка файла 3ds
bool C3DS::Load(const char *FileName, Shader* shader)
{
	bool _retBool = false;
	UseDestructors=false;
	cameraIndex = 0;
	lightIndex = -1;

	WriteLogF("Loading scene \"%s\"...", FileName);

	// Файл существует
	if (Load3DSFile(FileName, objects, cameras, lights, materials)!=NULL)
	{
		if (cameras.size() == 0)
		{
			cameras.push_back(new CCamera());
			WriteLogF("Cameras not found. Created default camera.");
		}

		if (lights.size() > 0)
			lightIndex = 0;

		if (objects.size() > 0 && objects.back()->VertexCount == 0)
			objects.pop_back();

		for (uint _objNum = 0; _objNum < objects.size(); _objNum++)
		{
			C3DSObject * currentObject = objects[_objNum];
			// Преобразования систем координат
			//for(int i=0;i<currentObject->VertexCount;++i)
			//{
			//		//Надо сначала сдвинуть его назад, то есть на вектор
			//		//-offset (НЕ на offset),
			//		// x
			//		currentObject->VertexList[3*i]-=currentObject->LocalMatrix[9];
			//		// y
			//		currentObject->VertexList[3*i+1]-=currentObject->LocalMatrix[11];
			//		// z
			//		currentObject->VertexList[3*i+2]-=currentObject->LocalMatrix[10];
			//		//а потом применить матрицу поворота rotmatr
			//		//Матрица записана построчно
			//		//В ней y и z тоже везде обменены местами!
			//		GLfloat x=-currentObject->VertexList[3*i];
			//		GLfloat y=-currentObject->VertexList[3*i+1];
			//		GLfloat z=-currentObject->VertexList[3*i+2];
			//		currentObject->VertexList[3*i]=currentObject->LocalMatrix[0]*x+currentObject->LocalMatrix[2]*z+currentObject->LocalMatrix[1]*y;
			//		currentObject->VertexList[3*i+2]=currentObject->LocalMatrix[3]*x+currentObject->LocalMatrix[5]*z+currentObject->LocalMatrix[4]*y;
			//		currentObject->VertexList[3*i+1]=currentObject->LocalMatrix[6]*x+currentObject->LocalMatrix[8]*z+currentObject->LocalMatrix[7]*y;
			//}

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
		UseDestructors=true;
		_retBool = true;
	}
	else
	{
		WriteLogF("  Error: File not found.\n");
		_retBool = false;
	}
	return _retBool;
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
	for (uint i = 0; i < cameras.size(); i++)
		delete cameras[i];
	for (uint i = 0; i < lights.size(); i++)
		delete lights[i];
	for (uint i = 0; i < materials.size(); i++)
		delete materials[i];

	objects.clear();
	cameras.clear();
	lights.clear();
	materials.clear();
}
