#include "Shader.h"

// �������� ������� �� ����� � ����������
bool Shader::Load(unsigned int shader, string FileName)
{
	// ������ �����
	vector <char *> v;
	// ���� ����� �������� ������
	char *buf;
	// ������ ����� ��� ��������
	char **str;
	// ��� ������
	int error=0;
	// ���� �������
	ifstream ShaderF(FileName.c_str(), ios::in|ios::binary);
	WriteLogF("  Loading shader \"%s\"...", FileName.c_str());
	
	// ���� ����������
	if (ShaderF!=NULL)
	{
		v.clear();
		// �������� ����� �� �����
		WriteLogF("    Loading...");
		while(ShaderF.good())
		{
			buf = new char[1024];
			ShaderF.getline(buf, 1024);
			buf[strlen(buf)+1]='\0';
			buf[strlen(buf)]='\n';
			v.push_back(buf);
		}
		// �������� ������� �����
		str = new char*[v.size()];
		for (unsigned int i=0;i<v.size();i++)
			str[i]=v[i];
		// ���������� �������
		WriteLogF("    Compiling...");
		glShaderSource(shader, v.size(), (const char**)str, 0);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
		// ������� ������
		for (unsigned int i=0;i<v.size();i++)
			delete[] v[i];
		// �������� ������
		if (error==GL_FALSE)
		{
			GLsizei count;
			char errtext[1024];
			glGetShaderInfoLog(shader, 1024, &count, errtext);
			WriteLogF("    Compilation failed! Errors:\n%s", errtext);
		}
		else
		{
			WriteLogF("    Shader successfully loaded");
			ShaderF.close();
			return true;
		}
	}
	else
		WriteLogF("    Error: file not exists");
	ShaderF.close();
	return false;
}

// �������� �������
void Shader::LoadShader(string Name)
{
	// ��� ������
	int error=0;

	VShader=glCreateShader(GL_VERTEX_SHADER);
	FShader=glCreateShader(GL_FRAGMENT_SHADER);
	PShader=glCreateProgram();
	
	WriteLogF("Loading shader program \"%s\"...", Name.c_str());
	Loaded=false;
	// �������� �� � ��
	if (Load(VShader, ProgPath+"Shaders\\"+Name+".vsh") && Load(FShader,  ProgPath+"Shaders\\"+Name+".fsh"))
	{
		// ������������� ��������
		glAttachShader(PShader, VShader);
		glAttachShader(PShader, FShader);
		// ��������
		glLinkProgram(PShader);
		glGetProgramiv(PShader, GL_LINK_STATUS, &error);
		if (error==GL_FALSE)
		{
			GLsizei count;
			char errtext[1024];
			glGetProgramInfoLog(PShader, 1024, &count, errtext);
			WriteLogF("  Link failed! Errors:\n%s", errtext);
		}
		else
		{
			WriteLogF("  Shader program successfully loaded");
			Loaded=true;
		}
	}
}

// ��������� �������
void Shader::Activate()
{
	if (Loaded)
		glUseProgram(PShader);
	else
		glUseProgram(0);
}

// ����������� �������
void Shader::Deactivate()
{
		glUseProgram(0);
}


Shader::Shader(void)
{
	Loaded = false;
}

Shader::~Shader(void)
{
	// �������� ��������
	glDeleteProgram(PShader);
	glDeleteShader(VShader);
	glDeleteShader(FShader);
}
