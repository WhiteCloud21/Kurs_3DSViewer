#include <fstream>
#include "C3DS.h"
#include "Shader.h"
	
C3DS scene;

extern void DrawFps();

char TextureFilter;

Shader ModelShader;

// Изменение режима фильтрации
void ChangeTextureFilter() 
{
	++TextureFilter;
	TextureFilter%=4;
	scene.SetFilterMode(TextureFilter);
}

// Загрузка объектов.
void LoadObjects(char* filename)
{
	string _fnf = ProgPath+"Models\\"+string(filename);
	if (!FileExists(_fnf.c_str()))
	{
		WriteLogF("Scene file does not exists, exiting...");
		exit(1);
	}
	TextureFilter = TEXTURE_FILTER_NEAREST;

	// Загрузка сцены
	scene.Load(_fnf.c_str(), &ModelShader);

	// Загрузка шейдеров
	ModelShader.LoadShader("Phong");
}

void RenderObjects()
{
	// Применение источника света
	CLight* _light = scene.GetCurrentLight();
	if (_light != NULL)
		_light->ApplyLight();

	// используем шейдер
	ModelShader.Activate();
	// Вывод объектов
	scene.Render();

	ModelShader.Deactivate();
	DrawFps();
}