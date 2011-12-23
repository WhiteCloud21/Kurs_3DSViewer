#include "3DSLoader.h"

// получение ID чанка
unsigned short GetChunkId(ifstream &ModelF)
{
	unsigned short chunk_id;
	int gp = ModelF.tellg();
	ModelF.read((char *)&chunk_id,sizeof(chunk_id));
	ModelF.seekg(gp, ios::beg);
	return chunk_id;
}

// чтение чанка
void ReadChunk(ifstream &ModelF, C3DS* scene)
{
	GLfloat _tempFloat;
	GLubyte _tempByte;
	GLint _tempInt;
	GLuint _tempUint;
	GLushort _tempShort, _tempShort2;
	GLfloat _posX, _posY, _posZ, _tX, _tY, _tZ;

	C3DSObject* currentObject = NULL;
	if (scene->objects.size() > 0)
		currentObject = scene->objects.back();

	// Идентификатор, определяет тип блока (2 байта)
	unsigned short chunk_id;
	unsigned short temp_chunk_id;

	// Длина блока в байтах (4 байта)
	unsigned int chunk_len;

	int gp;
	char _tempChar;
	char * _name = NULL;
	int _len;
	bool _flag;
	// Читаем заголовок чанка
	ModelF.read((char *)&chunk_id,sizeof(chunk_id));
	ModelF.read((char *)&chunk_len,sizeof(chunk_len));
	WriteLogF("  Chunk ID = 0x%hX Length = %u",chunk_id,chunk_len);
	switch (chunk_id)
	{
	// Чанки, которые НЕ пропускаем
	case 0x0010: //RGB_COLOR
		// Загрузка цвета
		ModelF.read((char *)&_tempFloat, sizeof(GLfloat));
		color.r = _tempFloat;
		ModelF.read((char *)&_tempFloat, sizeof(GLfloat));
		color.g = _tempFloat;
		ModelF.read((char *)&_tempFloat, sizeof(GLfloat));
		color.b = _tempFloat;
		WriteLogF("   Loaded color: (%f; %f; %f)", color.r, color.g, color.b);
		break;
	case 0x0011: //RGB_COLOR_24BIT
		// Загрузка цвета
		ModelF.read((char *)&_tempByte, sizeof(GLubyte));
		color.r = _tempByte / 255.0;
		ModelF.read((char *)&_tempByte, sizeof(GLubyte));
		color.g = _tempByte / 255.0;
		ModelF.read((char *)&_tempByte, sizeof(GLubyte));
		color.b = _tempByte / 255.0;
		WriteLogF("   Loaded color: (%f; %f; %f)", color.r, color.g, color.b);
		break;
	case 0x0030: //PERCENT_INT
		// Загрузка процента
		ModelF.read((char *)&_tempShort, sizeof(GLshort));
		percent = _tempShort;
		WriteLogF("   Loaded percent: (%f)", percent);
		break;
	case 0x4D4D: //MAIN3DS
	case 0x3D3D: //EDIT3DS
		break;
	case 0xAFFF: //EDIT_MATERIAL
		// Загрузка параметров материала
		scene->materials.push_back(new CMaterial());
		WriteLogF(" Loading material...");
		temp_chunk_id = GetChunkId(ModelF);
		while (temp_chunk_id >= 0xA000 && temp_chunk_id < 0xAFFF)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		break;
	case 0xA000: //MATERIAL_NAME
		gp = ModelF.tellg();
		// Читаем имя
		_len = 0;
		do
		{
			ModelF.read((char *)&_tempChar, 1);
			_len++;
		} while (_tempChar != '\0');
		ModelF.seekg(gp, ios::beg);
		delete[] objectName;
		objectName = new char[_len];
		ModelF.read(objectName, _len);
		scene->materials.back()->SetName(objectName);
		WriteLogF("    Material name = \"%s\"", objectName);
		break;
	case 0xA010: //MATERIAL_AMBIENT_COLOR
		temp_chunk_id = GetChunkId(ModelF);
		color = vec3(1.0f, 1.0f, 1.0f);
		while (temp_chunk_id == 0x0010 || temp_chunk_id == 0x0011)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		scene->materials.back()->SetAmbient(color);
		break;
	case 0xA020: //MATERIAL_DIFFUSE_COLOR
		temp_chunk_id = GetChunkId(ModelF);
		color = vec3(1.0f, 1.0f, 1.0f);
		while (temp_chunk_id == 0x0010 || temp_chunk_id == 0x0011)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		scene->materials.back()->SetDiffuse(color);
		break;
	case 0xA030: //MATERIAL_SPECULAR_COLOR
		temp_chunk_id = GetChunkId(ModelF);
		color = vec3(1.0f, 1.0f, 1.0f);
		while (temp_chunk_id == 0x0010 || temp_chunk_id == 0x0011)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		scene->materials.back()->SetSpecular(color);
		break;
	case 0xA040: //MATERIAL_SHININESS
		temp_chunk_id = GetChunkId(ModelF);
		percent = 32.0;
		while (temp_chunk_id == 0x0030 || temp_chunk_id == 0x0031)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		scene->materials.back()->SetShininess(percent);
		break;
	case 0xA041: //MATERIAL_SHININESSSTRENGTH
		temp_chunk_id = GetChunkId(ModelF);
		percent = 32.0;
		while (temp_chunk_id == 0x0030 || temp_chunk_id == 0x0031)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		scene->materials.back()->SetShininessStrength(percent);
		break;
	case 0xA050: //MATERIAL_TRANSPARENSY
		temp_chunk_id = GetChunkId(ModelF);
		percent = 100.0;
		while (temp_chunk_id == 0x0030 || temp_chunk_id == 0x0031)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		scene->materials.back()->SetTransparency(percent);
		break;
	case 0xA052: //MATERIAL_TRANSPARENSY_FALLOFF
		temp_chunk_id = GetChunkId(ModelF);
		percent = 100.0;
		while (temp_chunk_id == 0x0030 || temp_chunk_id == 0x0031)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		//materials.back()->SetTransparency(percent);
		break;
	case 0xA084: //MATERIAL_SELFILLUM
		temp_chunk_id = GetChunkId(ModelF);
		percent = 0.0;
		while (temp_chunk_id == 0x0030 || temp_chunk_id == 0x0031)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		scene->materials.back()->SetSelfIllum(percent);
		break;
	case 0xA200: //MATERIAL_TEXTURE1_MAP
		temp_chunk_id = GetChunkId(ModelF);
		currentMap = &(scene->materials.back()->texture1);
		while (temp_chunk_id == 0x0030 || temp_chunk_id == 0xA300 || temp_chunk_id == 0xA351 || temp_chunk_id == 0xA353)
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		break;
	case 0xA300: //MATERIAL_MAP_FILENAME
			gp = ModelF.tellg();
		// Читаем имя
		_len = 0;
		do
		{
			ModelF.read((char *)&_tempChar, 1);
			_len++;
		} while (_tempChar != '\0');
		ModelF.seekg(gp, ios::beg);
		_name = new char[_len];
		ModelF.read(_name, _len);
		currentMap->SetFileName(string(_name));
		delete[] _name;
		break;
	case 0x4000: //EDIT_OBJECT
		meshFirst = false;
		gp = ModelF.tellg();
		// Читаем имя объекта
		_len = 0;
		do
		{
			ModelF.read((char *)&_tempChar, 1);
			_len++;
		} while (_tempChar != '\0');
		ModelF.seekg(gp, ios::beg);
		delete[] objectName;
		objectName = new char[_len];
		ModelF.read(objectName, _len);
		WriteLogF("    Object name = \"%s\"", objectName);
		break;
	case 0x4100: //OBJ_TRIMESH
		meshFirst=!meshFirst;
		if (!meshFirst)
		{
			// Пропускаем чанк, ошибка формата файла
			ModelF.ignore(chunk_len-6);
			WriteLogF("   IGNORING, not first OBJ_TRIMESH");
		}
		else
		{
			// Начинается загрузка нового объекта
			currentObject = new C3DSObject();
			currentObject->SetName(objectName);
			//delete[] objectName;
			scene->objects.push_back(currentObject);
		}
		break;
	case 0x4110: //POINT_ARRAY
		// Читаем массив вершин
		ModelF.read((char *)&(currentObject->VertexCount),sizeof(unsigned short));
		currentObject->VertexList = new GLfloat[currentObject->VertexCount*3];
		//ModelF.read((char *)currentObject->VertexList,currentObject->VertexCount*sizeof(GLfloat)*3);
		for (int i=0;i<currentObject->VertexCount;++i)
		{
			ModelF.read((char *)&(currentObject->VertexList[3*i]),sizeof(GLfloat));
			ModelF.read((char *)&(currentObject->VertexList[3*i+2]),sizeof(GLfloat));
			ModelF.read((char *)&(currentObject->VertexList[3*i+1]),sizeof(GLfloat));
			currentObject->VertexList[3*i+2] = -currentObject->VertexList[3*i+2];
		}
		WriteLogF(" VertexCount = %hu",currentObject->VertexCount);
		break;
	case 0x4120: //FACE_ARRAY
		// Читаем массив индексов
		ModelF.read((char *)&(_tempShort),sizeof(unsigned short));
		currentObject->IndexCount = _tempShort;
		currentObject->IndexList = new unsigned short[currentObject->IndexCount*3];
		for (unsigned int i=0;i<currentObject->IndexCount;++i)
		{
			ModelF.read((char *)&(currentObject->IndexList[3*i]),sizeof(unsigned short));
			ModelF.read((char *)&(currentObject->IndexList[3*i+1]),sizeof(unsigned short));
			ModelF.read((char *)&(currentObject->IndexList[3*i+2]),sizeof(unsigned short));
			// Пропускаем ненужный параметр
			ModelF.ignore(sizeof(unsigned short));
		}
		currentObject->IndexCount*=3;
		WriteLogF(" IndexCount = %hu",currentObject->IndexCount);
		break;
	case 0x4130: //FACE_MATERIALS_ARRAY
		gp = ModelF.tellg();
		// Читаем имя
		_len = 0;
		do
		{
			ModelF.read((char *)&_tempChar, 1);
			_len++;
		} while (_tempChar != '\0');
		ModelF.seekg(gp, ios::beg);
		_name = new char[_len];
		ModelF.read(_name, _len);
		ModelF.read((char *)&(_tempShort),sizeof(GLushort));
		WriteLogF("   Material '%s' Count = %hu", _name, _tempShort);
		if (_tempShort > 0)
		{
			for (vector<CMaterial*>::iterator _it = scene->materials.begin(); _it != scene->materials.end(); _it++)
			{
				if (strcmp((*_it)->GetName(), _name) == 0)
				{
					GLuint* _shArr = new GLuint[3 * _tempShort];
					for (int i = 0; i <_tempShort; i++)
					{
						ModelF.read((char *)&(_tempShort2),sizeof(GLushort));
						_shArr[3*i] = 3*_tempShort2;
						_shArr[3*i+1] = 3*_tempShort2+1;
						_shArr[3*i+2] = 3*_tempShort2+2;
					}
					glGenBuffersARB(1, &_tempUint);
					glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _tempUint);
					glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(GLuint)*3*_tempShort, _shArr, GL_STATIC_DRAW_ARB);
					glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
					currentObject->IndexVBO.push_back(CVBOInfo(_tempUint, 3*_tempShort, *_it));
					if ((*_it)->IsTransparent())
						currentObject->isTransparent = true;
					WriteLogF("      Created buffer %u", _tempUint);
					delete[] _shArr;
					break;
				}
			}
			delete[] _name;
		}
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
	case 0x4600: //OBJ_LIGHT
		// Загрузка источника света
		ModelF.read((char *)&_posX, sizeof(GLfloat));
		ModelF.read((char *)&_posZ, sizeof(GLfloat));
		ModelF.read((char *)&_posY, sizeof(GLfloat));
		scene->lights.push_back(new CLight(isLightEnabled, vec3(_posX, _posY, -_posZ)));
		WriteLogF(" Loaded light: (%f; %f; %f)", _posX, _posY, -_posZ);
		temp_chunk_id = GetChunkId(ModelF);
		color = vec3(1.0f, 1.0f, 1.0f);
		while (temp_chunk_id == 0x0010 || temp_chunk_id == 0x0011 || (temp_chunk_id >= 0x4600 && temp_chunk_id < 0x4700))
		{
			ReadChunk(ModelF, scene);
			temp_chunk_id = GetChunkId(ModelF);
		}
		scene->lights.back()->SetColor(color);
		break;
	case 0x4610: //LIGHT_SPOTLIGHT
		// Загрузка направленного источника света
		ModelF.read((char *)&_posX, sizeof(GLfloat));
		ModelF.read((char *)&_posZ, sizeof(GLfloat));
		ModelF.read((char *)&_posY, sizeof(GLfloat));
		ModelF.ignore(sizeof(GLfloat)*2);
		scene->lights.back()->SetTarget(vec3(_posX, _posY, -_posZ));
		WriteLogF("   Spotlight target: (%f; %f; %f)", _posX, _posY, -_posZ);
		break;
	case 0x4620: //LIGHT_ENABLED
		ModelF.read((char *)&isLightEnabled, sizeof(GLboolean));
		break;
	case 0x4700: //OBJ_CAMERA
		// Загрузка новой камеры
		// Читаем параметры камеры
		ModelF.read((char *)&_posX, sizeof(GLfloat));
		ModelF.read((char *)&_posZ, sizeof(GLfloat));
		ModelF.read((char *)&_posY, sizeof(GLfloat));
		ModelF.read((char *)&_tX,	 sizeof(GLfloat));
		ModelF.read((char *)&_tZ,	 sizeof(GLfloat));
		ModelF.read((char *)&_tY,	 sizeof(GLfloat));
		ModelF.ignore(sizeof(GLfloat)*2);
		// Создание камеры
		scene->cameras.push_back(new CCamera(_posX, _posY, -_posZ, _tX, _tY, -_tZ));
		// пропуск остатков
		//ModelF.ignore(chunk_len - 6 - 32);
		WriteLogF(" Loaded camera: (%f; %f; %f) -> (%f; %f; %f)", _posX, _posY, -_posZ, _tX, _tY, -_tZ);
		break;
	default:
		// Пропускаем чанк
		ModelF.ignore(chunk_len-6);
		WriteLogF("   IGNORING");
		break;
	}
}

// загрузка файла 3ds
bool Load3DSFile(const char *FileName, C3DS* scene)
{
	// Файл модели
	ifstream ModelF(FileName, ios::in|ios::binary);

		// Файл существует
	if (ModelF!=NULL)
	{
		ModelF.seekg(0);
		while(ModelF.good())
		{
			ReadChunk(ModelF, scene);
		}
		ModelF.close();
		return true;
	}
	return false;
}
