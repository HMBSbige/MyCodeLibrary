#pragma once
#include <string>

class Punycode
{
public:
	static const int TMIN = 1;
	static const int TMAX = 26;
	static const int BASE = 36;
	static const int INITIAL_N = 128;
	static const int INITIAL_BIAS = 72;
	static const int DAMP = 700;
	static const int SKEW = 38;
	static const char DELIMITER = '-';
	static std::wstring encode(std::wstring input);
	static std::wstring decode(std::wstring input);
private:
	static int adapt(int delta, const int& numpoints, const bool& first);
	static bool is_basic(const wchar_t& c);
	static int Digit2codepoint(const int& d);
	static int Codepoint2digit(const int& c);
};