#include <conio.h>
#include <stdio.h>
#include "main.h"
#include "C3DS.h"
#include "Camera.h"
#include "Shader.h"
#include "vkscancodes.h"

extern C3DS scene;
CCamera* camera;

inline string GetPathFromFilename( const string& filename )
{
	return filename.substr( 0, filename.rfind("\\")+1 );
}


void ToggleCullFace()
{
	if (CullFaceFlag)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);
	CullFaceFlag = !CullFaceFlag;
}


// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display (void)
{
	// очищаем буфер цвета и буфер глубины
	glClearColor(0.3,0.3,0.3,1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// режим вывода полигонов (выводим в виде линии)
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	// устанавливаем камеру
	camera->ApplyCamera();

	// отрисовка объектов
	RenderObjects();

	// смена переднего и заднего буферов
	glutSwapBuffers();
}

// функция, вызываемая при изменении размеров окна
void Reshape (int w,int h)
{
	windowWidth = w;
	windowHeight = h;
	// установить новую область просмотра, равную всей области окна
	glViewport(0,0,(GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (camera != NULL)
	{
		vec3 _camPos = camera->GetPos();
		gluPerspective(25.0,((float)w)/h,1.0,sqrt(_camPos.x * _camPos.x + _camPos.y * _camPos.y + _camPos.z * _camPos.z)*15);
	}
	else
		gluPerspective(25.0,((float)w)/h,1.0,1000.0);

	// принудительно перерисовать окно
	glutPostRedisplay();
}

// функция вызывается по таймеру
void Simulation(void)
{
	// принудительно перерисовать окно
	glutPostRedisplay();
}

void KeyPressed(unsigned char c, int, int)
{
	// получение клавиатурной раскладки основного потока программы
	HKL _keyboardLayout = GetKeyboardLayout(0);
	// получение виртуального кода нажатой клавиши
	int _key = VkKeyScanExA(c,_keyboardLayout);

	switch (c)
	{
		case '+':
			camera->Forward();
			break;
		case '-':
			camera->Back();
			break;
	}

	switch (_key)
	{
		case VK_ADD:
			camera->Forward();
			break;
		case VK_SUBTRACT:
			camera->Back();
			break;
		case VK_W:
			camera->Up();
			break;
		case VK_S:
			camera->Down();
			break;
		case VK_A:
			camera->Left();
			break;
		case VK_D:
			camera->Right();
			break;
		case VK_R:
			camera->Reset();
			break;	
		case VK_TAB:
			camera = scene.GetNextCamera();
			break;	
		case VK_L:
			ToggleCullFace();
			break;	
		case VK_O:
			UseOcclusionCulling = !UseOcclusionCulling && GLEE_ARB_occlusion_query;
			WriteLogF("Occlusion culling: %s", UseOcclusionCulling?"Enabled":"Disabled");
			break;
		case VK_T:
			ChangeTextureFilter();
			break;
	}
}

void main(int argc,char **argv)
{
	setlocale(LC_CTYPE, "RUS");

	ProgPath = GetPathFromFilename(argv[0]);
	LogFile = ProgPath + "Logs\\" + getNowToString() + ".log";
	if (!FileExists((ProgPath + "Logs").c_str()))
	{
		CreateDirectory((ProgPath + "Logs").c_str(), NULL);
	}

	// инициализация библиотеки GLUT
	glutInit(&argc,argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// создание окна:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200,200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(600,600);
	// 3. создаем окно
	glutCreateWindow("Курсовая работа");
	// 4. устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// 5. устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// 6. устанавливаем функцию, которая будет вызываться при нажатии клавиши
	glutKeyboardFunc(KeyPressed);
	// 7. устанавливаем функцию которая вызывается всякий раз, когда процессор простаивает
	glutIdleFunc(Simulation);

	// вывод строк описывающих OpenGL
	// вывод производителя
	WriteLogF("Vendor: %s", glGetString(GL_VENDOR));
	WriteLogF("Render: %s", glGetString(GL_RENDER));
	WriteLogF("Version: %s", glGetString(GL_VERSION));
	// вывод версии шейдерного языка
	WriteLogF("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	// вывод всех доступных расширений
	char *_ext=(char*)glGetString(GL_EXTENSIONS);
	char *_extForPrint = new char[strlen(_ext) * 2];
	int i = 0, j = 0;
	do 
	{
		if (_ext[i] ==' ')
		{
			_extForPrint[j] = '\n';
			j++;
			_extForPrint[j] = '\t';
		}
		else
			_extForPrint[j] = _ext[i];
		j++;
	} while (_ext[i++] != NULL);

	WriteLogF("%s\n\t%s", "Supported extensions:", _extForPrint);
	delete[] _extForPrint;

	// проверка потдержки VBO
	if (GLEE_ARB_vertex_buffer_object)
	{
		WriteLogF("supporting VBO ......OK");
	}
	else
	{
		WriteLogF("supporting VBO ......fail");
		printf("Press any key...");
		_getch();
		exit(1);
	}

	// Проверка поддержки шейдеров
	if (GLEE_ARB_shader_objects && GLEE_ARB_fragment_shader && GLEE_ARB_vertex_shader)
	{
		WriteLogF("supporting shaders ......OK");
		if (GLEE_ARB_occlusion_query)
		{
			WriteLogF("supporting occlusion query ......OK");
		}
		else
			WriteLogF("supporting occlusion query ......fail");
	}
	else
	{
		WriteLogF("supporting shaders ......fail");
		printf("Press any key...");
		_getch();
		exit(1);
	}

	// загрузка объектов
	if (argc>1)
		LoadObjects(argv[1]);
	else
		LoadObjects("scene.3ds");

	printf("\n");
	camera = scene.GetCurrentCamera();
	UseOcclusionCulling = GLEE_ARB_occlusion_query;
	
	// основной цикл обработки сообщений ОС
	glutMainLoop();
	return;
}