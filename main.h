#pragma once
#include <windows.h>
#include "glee.h"
#include "glm/glm.hpp"
#include "glut.h"
#include "texture.h" 

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "macro.h"

using namespace std;

// Данные
typedef vector<GLfloat> vect;

const char TEXTURE_FILTER_NEAREST = 0;
const char TEXTURE_FILTER_LINEAR = 1;
const char TEXTURE_FILTER_MIPMAP_LINEAR = 2;
const char TEXTURE_FILTER_ANISOTROPY = 3;

const int MAX_CONFIG_LINE_LENGTH=500;

extern bool UseDestructors;
extern bool UseOcclusionCulling;
extern bool CullFaceFlag;

extern string ProgPath;
extern string ConfigFile;
extern string LogFile;
extern string LogFile;

extern int windowWidth, windowHeight;

// Функции
extern void split(const string& str, const string& delim, vector<string>& parts);
extern string remove_spaces(const string& source);
extern string StrToLower(string s);
extern inline string StrReplace(string text, string s, string d);
extern bool FileExists (const char *fname);
extern string getNowToString();

extern void ChangeTextureFilter();
extern void LoadObjects(char* filename);
extern void RenderObjects();

extern bool LoadTGA(Texture * texture, char * filename);