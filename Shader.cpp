#include "Shader.h"

// Загрузка шейдера из файла и компиляция
bool Shader::Load(unsigned int shader, string FileName)
{
	// Вектор строк
	vector <char *> v;
	// Сюда будут читаться строки
	char *buf;
	// Массив строк для передачи
	char **str;
	// Код ошибки
	int error=0;
	// Файл шейдера
	ifstream ShaderF(FileName.c_str(), ios::in|ios::binary);
	printf("  Loading shader \"%s\"...\n", FileName.c_str());
	
	// Файл существует
	if (ShaderF!=NULL)
	{
		v.clear();
		// Загрузка строк из файла
		printf("    Loading...\n");
		while(ShaderF.good())
		{
			buf = new char[1024];
			ShaderF.getline(buf, 1024);
			buf[strlen(buf)+1]='\0';
			buf[strlen(buf)]='\n';
			v.push_back(buf);
		}
		// Создание массива строк
		str = new char*[v.size()];
		for (unsigned int i=0;i<v.size();i++)
			str[i]=v[i];
		// Компиляция шейдера
		printf("    Compiling...\n");
		glShaderSource(shader, v.size(), (const char**)str, 0);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
		// Очистка памяти
		for (unsigned int i=0;i<v.size();i++)
			delete[] v[i];
		// Проверка ошибок
		if (error==GL_FALSE)
		{
			GLsizei count;
			char errtext[1024];
			glGetShaderInfoLog(shader, 1024, &count, errtext);
			printf("    Compilation failed! Errors:\n%s\n", errtext);
		}
		else
		{
			printf("    Shader successfully loaded\n");
			ShaderF.close();
			return true;
		}
	}
	else
		printf("    Error: file not exists\n");
	ShaderF.close();
	return false;
}

// Загрузка шейдера
void Shader::LoadShader(string Name)
{
	// Код ошибки
	int error=0;

	VShader=glCreateShader(GL_VERTEX_SHADER);
	FShader=glCreateShader(GL_FRAGMENT_SHADER);
	PShader=glCreateProgram();
	
	printf("\nLoading shader program \"%s\"...\n", Name.c_str());
	Loaded=false;
	// Загрузка ВШ и ФШ
	if (Load(VShader, ProgPath+"Shaders\\"+Name+".vsh") && Load(FShader,  ProgPath+"Shaders\\"+Name+".fsh"))
	{
		// Присоединение шейдеров
		glAttachShader(PShader, VShader);
		glAttachShader(PShader, FShader);
		// Линковка
		glLinkProgram(PShader);
		glGetProgramiv(PShader, GL_LINK_STATUS, &error);
		if (error==GL_FALSE)
		{
			GLsizei count;
			char errtext[1024];
			glGetProgramInfoLog(PShader, 1024, &count, errtext);
			printf("  Link failed! Errors:\n%s\n", errtext);
		}
		else
		{
			printf("  Shader program successfully loaded\n");
			Loaded=true;
		}
	}
}

// Активация шейдера
void Shader::Activate()
{
	if (Loaded)
		glUseProgram(PShader);
	else
		glUseProgram(0);
}

Shader::Shader(void)
{
	Loaded = false;
}

Shader::~Shader(void)
{
	// Удаление шейдеров
	glDeleteProgram(PShader);
	glDeleteShader(VShader);
	glDeleteShader(FShader);
}
