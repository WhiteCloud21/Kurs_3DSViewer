#include "main.h"

bool CullFaceFlag=false;
bool UseDestructors=true;

string ProgPath;
string LogFile;
bool isFullLog = false;

int windowWidth, windowHeight;
bool UseOcclusionCulling;
unsigned int occludedCount;
int frameSkipQuery;