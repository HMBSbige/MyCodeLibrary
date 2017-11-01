#include "Punycode.h"
#include <Windows.h>

std::wstring Punycode::encode(std::wstring input)
{
	int n = INITIAL_N;
	int delta = 0;
	int bias = INITIAL_BIAS;
	std::wstring output;
	// Copy all basic code points to the output
	int b = 0;
	for (int i = 0; i<input.length(); i++) {
		wchar_t c = input[i];
		if (is_basic(c)) {
			output.append(1,c);
			++b;
		}
	}
	// Append delimiter
	if (b > 0) {
		output.append(1,DELIMITER);
	}
	int h = b;
	while (h<input.length())
	{
		int m = INT_MAX;
		// Find the minimum code point >= n
		for(int c : input)
		{
			if (c >= n && c<m) {
				m = c;
			}
		}
		if (m - n >(INT_MAX - delta) / (h + 1)) {
			OutputDebugString(L"OVERFLOW\n");
			return L"";
		}
		delta = delta + (m - n) * (h + 1);
		n = m;
		for(int c : input)
		{
			if (c<n) {
				delta++;
				if (0 == delta) {
					OutputDebugString(L"OVERFLOW\n");
					return L"";
				}
			}
			if (c == n) {
				int q = delta;
				for (int k = BASE;; k += BASE) {
					int t;
					if (k <= bias) {
						t = TMIN;
					}
					else if (k >= bias + TMAX) {
						t = TMAX;
					}
					else {
						t = k - bias;
					}
					if (q<t) {
						break;
					}
					output.append(1,static_cast<wchar_t>(Digit2codepoint(t + (q - t) % (BASE - t))));
					q = (q - t) / (BASE - t);
				}
				output.append(1,static_cast<wchar_t>(Digit2codepoint(q)));
				bias = adapt(delta, h + 1, h == b);
				delta = 0;
				h++;
			}
		}
		delta++;
		n++;
	}
	return output;
}

std::wstring Punycode::decode(std::wstring input)
{
	int n = INITIAL_N;
	int i = 0;
	int bias = INITIAL_BIAS;
	std::wstring output;
	int d = input.find_last_of(DELIMITER);

	if (d > 0) {
		for (int j = 0; j<d; j++) {
			wchar_t c = input[j];
			if (!is_basic(c)) {
				OutputDebugString(L"BAD_INPUT\n");
				return L"";
			}
			output.append(1,c);
		}
		d++;
	}
	else {
		d = 0;
	}
	while (d<input.length()) {
		const int oldi = i;
		int w = 1;
		for (int k = BASE;; k += BASE) {
			if (d == input.length()) {
				OutputDebugString(L"BAD_INPUT\n");
				return L"";
			}
			int c = input[d++];
			const int digit = Codepoint2digit(c);
			if (digit >(INT_MAX - i) / w) {
				OutputDebugString(L"OVERFLOW\n");
				return L"";
			}
			i = i + digit* w;
			int t;
			if (k <= bias) {
				t = TMIN;
			}
			else if (k >= bias + TMAX) {
				t = TMAX;
			}
			else {
				t = k - bias;
			}
			if (digit<t) {
				break;
			}
			w = w* (BASE - t);
		}
		bias = adapt(i - oldi, output.length() + 1, oldi == 0);
		if (i / (output.length() + 1) > INT_MAX - n) {
			OutputDebugString(L"OVERFLOW\n");
			return L"";
		}
		n = n + i / (output.length()+ 1);
		i = i % (output.length() + 1);
		std::wstring temp;
		temp = static_cast<wchar_t>(n);
		output.insert(i, temp);
		i++;
	}
	return output;
}

int Punycode::adapt(int delta, const int& numpoints, const bool& first)
{
	if (first)
	{
		delta = delta / DAMP;
	}
	else
	{
		delta = delta / 2;
	}
	delta = delta + (delta / numpoints);
	int k = 0;
	while (delta > ((BASE - TMIN) * TMAX) / 2)
	{
		delta = delta / (BASE - TMIN);
		k = k + BASE;
	}
	return k + ((BASE - TMIN + 1) * delta) / (delta + SKEW);
}

bool Punycode::is_basic(const wchar_t& c)
{
	return c < 0x80;
}

int Punycode::Digit2codepoint(const int& d)
{
	if (d < 26) {
		// 0..25 : 'a'..'z'
		return d + 'a';
	}
	if (d < 36) {
		// 26..35 : '0'..'9';
		return d - 26 + '0';
	}
	OutputDebugString(L"BAD_INPUT\n");
	return -1;
}

int Punycode::Codepoint2digit(const int& c)
{
		if (c - '0' < 10) {
			// '0'..'9' : 26..35
			return c - '0' + 26;
		}
		if (c - 'a' < 26) {
			// 'a'..'z' : 0..25
			return c - 'a';
		}
		OutputDebugString(L"BAD_INPUT\n");
		return -1;
}