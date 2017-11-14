#pragma once
#include <codecvt>
using namespace std;
class CharacterEncodingConversion
{
public:
	CharacterEncodingConversion();
	virtual~ CharacterEncodingConversion();
	char* WcharToChar(const wchar_t* wp);
	static char* StringToChar(const string& s);
	char* WstringToChar(const wstring& ws);
	wchar_t* CharToWchar(const char* c);
	static wchar_t* WstringToWchar(const wstring& ws);
	wchar_t* StringToWchar(const string& s);
	wstring StringToWstring(const string& s);
	string WstringToString(const wstring& ws);
	string WstringToU8string(const wstring& ws);
	wstring U8stringToWstring(const string& u8s);
	wstring GBKstringToWstring(const string& GBK);
	string WstringToGBKstring(const wstring& ws);
	void Release();
private:
	const string GBK_LOCALE_NAME = ".936";//GBK在windows下的locale name
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> conver;
	wstring_convert<codecvt_byname<wchar_t, char, mbstate_t>> cv1;

	char* m_char;
	wchar_t* m_wchar;
};