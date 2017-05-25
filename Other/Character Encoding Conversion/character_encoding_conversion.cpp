#include "character_encoding_conversion.h"
CharacterEncodingConversion::CharacterEncodingConversion()
:m_char(nullptr)
,m_wchar(nullptr)
{}
CharacterEncodingConversion::~CharacterEncodingConversion(){Release();}
char* CharacterEncodingConversion::WcharToChar(const wchar_t* wp)
{
	Release();
	auto len= WideCharToMultiByte(CP_ACP,0,wp,int(wcslen(wp)),nullptr,0,nullptr,nullptr);
	m_char=new char[len+1];
	WideCharToMultiByte(CP_ACP,0,wp,int(wcslen(wp)),m_char,len,nullptr,nullptr);
	m_char[len]='\0';
	return m_char;
}
wchar_t* CharacterEncodingConversion::CharToWchar(const char* c)
{
	Release();
	auto len = MultiByteToWideChar(CP_ACP,0,c,int(strlen(c)),nullptr,0);
	m_wchar=new wchar_t[len+1];
	MultiByteToWideChar(CP_ACP,0,c,int(strlen(c)),m_wchar,len);
	m_wchar[len]='\0';
	return m_wchar;
}
void CharacterEncodingConversion::Release()
{
	if(m_char)
	{
		delete m_char;
		m_char= nullptr;
	}
	if(m_wchar)
	{
		delete m_wchar;
		m_wchar= nullptr;
	}
}
char* CharacterEncodingConversion::StringToChar(const string& s)
{
	return const_cast<char*>(s.c_str());
}
char* CharacterEncodingConversion::WstringToChar(const std::wstring &ws)
{
	const wchar_t* wp=ws.c_str();
	return WcharToChar(wp);
}
wchar_t* CharacterEncodingConversion::WstringToWchar(const std::wstring &ws)
{
	return const_cast<wchar_t*>(ws.c_str());
}
wchar_t* CharacterEncodingConversion::StringToWchar(const string& s)
{
	const char* p=s.c_str();
	return CharToWchar(p);
}
string CharacterEncodingConversion::WstringToString(const std::wstring &ws)
{
	string s;
	char* p=WstringToChar(ws);
	s.append(p);
	return s;
}
wstring CharacterEncodingConversion::StringToWstring(const std::string &s)
{
	wstring ws;
	wchar_t* wp=StringToWchar(s);
	ws.append(wp);
	return ws;
}