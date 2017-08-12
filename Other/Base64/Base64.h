#pragma once
#ifndef ___BASE64_H___
#define ___BASE64_H___

#include <string>

using namespace std;
/*
 * 1.不能正确加密非ASCII码字符
 * 2.解密出的是u8string，可以转化成wstring在控制台输出或直接输出文件
 */
class Base64
{
public:
	Base64();
	~Base64();
	string static Encode(string strIn);
	string static Decode(const string& strIn);
};

#endif // ___BASE64_H___