#pragma once
#include <sstream>
#include <string>
using namespace std;

template<class T>
T StringToNum(const string& s)//字符串转数字
{
	T num;
	stringstream ss(s);
	ss >> num;
	return num;
}
template<class T> 
string ToString(const T& t)//数字转字符串
{
	ostringstream oss;
	oss << t;
	return oss.str();
}
template<class out_type, class in_value>
out_type convert(const in_value & t)//通用转换
{
	stringstream stream;
	stream << t;
	out_type result;
	stream >> result;
	return result;
}