#include "main.h"
#include <cctype>
#include <functional>
#include <fstream>
#include <iostream>
#include <io.h>

string wordToStrWithZeros(WORD value, unsigned short digitCount)
{
	char _buf[8];
	sprintf_s(_buf, "%hu", value);
	string _retStr(_buf);
	for(int i = 1; i < digitCount; i++)
	{
		value /= 10;
		if (value == 0)
			_retStr = "0" + _retStr;
	}
	return _retStr;
}

inline string twoDigitWordToStr(WORD value)
{
	return wordToStrWithZeros(value, 2);
}

string getNowTimeStamp()
{
  SYSTEMTIME _time;
  GetLocalTime( &_time ); 

  string _retStr("");
	_retStr = "[" + twoDigitWordToStr(_time.wHour)+ ":" + twoDigitWordToStr(_time.wMinute) + ":" 
		+ twoDigitWordToStr(_time.wSecond) + "] ";

  return _retStr;
     
}

string getNowToString()
{
  SYSTEMTIME _time;
  GetLocalTime( &_time ); 

  string _retStr("");
  _retStr += wordToStrWithZeros(_time.wYear, 4);
  _retStr += "_";
  _retStr += twoDigitWordToStr(_time.wMonth);
  _retStr += "_";
  _retStr += twoDigitWordToStr(_time.wDay);
  _retStr += "_";
  _retStr += twoDigitWordToStr(_time.wHour);
  _retStr += "_";
  _retStr += twoDigitWordToStr(_time.wMinute);
  _retStr += "_";
  _retStr += twoDigitWordToStr(_time.wSecond);

  return _retStr;
}
bool FileExists (const char *fname)
{
	return _access(fname,0) != -1;
}