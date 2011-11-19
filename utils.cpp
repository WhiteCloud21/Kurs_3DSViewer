#include "main.h"
#include <cctype>
#include <functional>
#include <fstream>

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