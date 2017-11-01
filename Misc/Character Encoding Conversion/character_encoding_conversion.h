#pragma once
#include <Windows.h>
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
	void Release();
private:
	std::wstring_convert<codecvt_utf8<wchar_t>, wchar_t> conver;
	char* m_char;
	wchar_t* m_wchar;
};