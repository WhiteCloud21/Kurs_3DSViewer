#include "VBOInfo.h"

CVBOInfo::CVBOInfo(GLuint a_buffer, GLsizei a_bufSize, CMaterial* a_mat)
{
	buffer = a_buffer;
	bufSize = a_bufSize;
	material = a_mat;
}

CVBOInfo::~CVBOInfo(void)
{
}
