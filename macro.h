// Макросы
#define WriteLogF(format, ...) { char  _buf[20000]/* = new char[strlen(format)]*/; sprintf_s (_buf, format, __VA_ARGS__); WriteLog(_buf);/* delete[] _buf;*/ }