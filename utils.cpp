#include "main.h"
#include <cctype>
#include <functional>
#include <fstream>
#include <iostream>
#include <io.h>

void split(const string& str, const string& delim, vector<string>& parts) {
  size_t start, end = 0;
  while (end < str.size()) {
    start = end;
    while (start < str.size() && (delim.find(str[start]) != string::npos)) {
      start++;  // skip initial whitespace
    }
    end = start;
    while (end < str.size() && (delim.find(str[end]) == string::npos)) {
      end++; // skip to end of word
    }
    if (end-start != 0) {  // just ignore zero-length strings.
      parts.push_back(string(str, start, end-start));
    }
  }
}

string remove_spaces(const string& source)
{
    string s = source;
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    return (s);
}

string StrToLower(string s)
{
	transform(s.begin(), s.end(), s.begin(),std::ptr_fun(tolower));
	return s;
}

inline string StrReplace(string text, string s, string d)
{
	for(unsigned index=0; index=text.find(s, index), index!=string::npos;)
	{
		text.replace(index, s.length(), d);
		index+=d.length();
	}
	return text;
}

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

void WriteLog(char *text)
{
	string _outText(text);
	_outText = getNowTimeStamp() + _outText + "\n";
	cout << _outText;
	try
	{
		ofstream _logFile(LogFile.c_str(), ios::app);
		_logFile << _outText;
		_logFile.close();
	}
	catch (exception)
	{
		cout << "Ошибка записи в лог-файл";
	}
}

bool FileExists (const char *fname)
{
	return _access(fname,0) != -1;
}