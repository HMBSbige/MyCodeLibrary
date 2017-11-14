#include "character_encoding_conversion.h"

CharacterEncodingConversion::CharacterEncodingConversion()
:cv1(new codecvt_byname<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME))
,m_char(nullptr), m_wchar(nullptr)
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
string CharacterEncodingConversion::WstringToU8string(const wstring& ws)
{
	/*Release();
	auto iTextLen = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, nullptr, 0, nullptr, nullptr);
	m_char = new char[iTextLen + 1];
	WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, m_char, iTextLen, nullptr, nullptr);
	m_char[iTextLen] = '\0';
	string strText = m_char;
	return strText;*/
	return conver.to_bytes(ws);
}
wstring CharacterEncodingConversion::U8stringToWstring(const string& u8s)
{
	/*Release();
	auto unicodeLen = MultiByteToWideChar(CP_UTF8,0, u8s.c_str(),-1,nullptr,0);
	m_wchar = new wchar_t[unicodeLen + 1];
	MultiByteToWideChar(CP_UTF8,0, u8s.c_str(),-1,static_cast<LPWSTR>(m_wchar),unicodeLen);
	m_wchar[unicodeLen] = '\0';
	wstring rt = m_wchar;
	return rt;*/
	return conver.from_bytes(u8s);
}

wstring CharacterEncodingConversion::GBKstringToWstring(const string& GBK)
{
	return cv1.from_bytes(GBK);
}

string CharacterEncodingConversion::WstringToGBKstring(const wstring& ws)
{
	return cv1.to_bytes(ws);
}