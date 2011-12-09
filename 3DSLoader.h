#pragma once
#include "main.h"
#include "C3DSObject.h"
#include "Camera.h"
#include "Light.h"
#include <fstream>

using namespace glm;

char objectName[256];
bool meshFirst;
vec3 color;
ivec3 colorByte;
bool isColor24Bit;
bool isSpotLight;
bool isLightEnabled;