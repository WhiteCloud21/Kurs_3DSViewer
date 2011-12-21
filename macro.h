#pragma once
#include <string>
extern std::string LogFile;
extern std::string getNowTimeStamp();

// Макросы
//#define WriteLogF(format, ...) { char  _buf[20000]/* = new char[strlen(format)]*/; sprintf_s (_buf, format, __VA_ARGS__); WriteLog(_buf);/* delete[] _buf;*/ }
#define WriteLogF(format, ...) { FILE * _f; std::string _msg = getNowTimeStamp() + format + "\n"; errno_t _error = fopen_s(&_f, LogFile.c_str(), "a+"); \
	printf(_msg.c_str(), __VA_ARGS__); \
	if (_error == 0) { \
		fprintf(_f, _msg.c_str(), __VA_ARGS__); fclose(_f); \
	} }