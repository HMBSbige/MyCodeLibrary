#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class BigNumber {
	const static int ten[4];
	const static size_t maxl;//4*(maxl-1)
	static bool smaller(const BigNumber &a, const BigNumber &b, size_t delta);
	static void Minus(BigNumber &a, const BigNumber &b, size_t delta);
	vector<size_t> d;
public:
	explicit BigNumber(string s);
	BigNumber();
	template<class T> void InitbyInt(T x);
	BigNumber(size_t x);
	string toString();
	BigNumber big_pow(size_t n)const;
	BigNumber BigNumber::sqrt()const;
	BigNumber BigNumber::sqrt3()const;
	friend BigNumber operator +(const BigNumber &a, const BigNumber &b);
	friend BigNumber operator -(const BigNumber &a, const BigNumber &b);
	friend BigNumber operator *(const BigNumber &a, const BigNumber &b);
	friend BigNumber operator *(const BigNumber &a, const size_t &k);
	friend BigNumber operator /(const BigNumber &a, const BigNumber &b);
	friend BigNumber operator %(const BigNumber &a, const BigNumber &b);
	friend bool operator < (const BigNumber &a, const BigNumber &b);
	friend bool operator > (const BigNumber &a, const BigNumber &b);
	friend bool operator == (const BigNumber &a, const BigNumber &b);
	friend bool operator != (const BigNumber &a, const BigNumber &b);
	friend bool operator <= (const BigNumber &a, const BigNumber &b);
	friend bool operator >= (const BigNumber &a, const BigNumber &b);
	friend istream& operator>>(istream& is, BigNumber& n);
	friend ostream& operator<<(ostream& os, BigNumber& n);
	friend ostream& operator<<(ostream& os, BigNumber&& n);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
const int BigNumber::ten[4] = { 1,10,100,1000 };
const size_t BigNumber::maxl = 1000;
BigNumber::BigNumber(string s) :d(maxl) {
	auto len = s.size();//2^64-1
	vector<size_t>(maxl, 0).swap(d);
	d[0] = (len - 1) / 4 + 1;
	for (size_t i = 0; i <= len - 1; ++i)//(len-1-i)
	{
		auto j = i / 4 + 1;
		auto k = i % 4;
		d[j] += ten[k] * (s[len - 1 - i] - '0');
	}
	while (d[0]>1 && d[d[0]] == 0)
		--d[0];
}
BigNumber::BigNumber() :d(maxl) {
	*this = BigNumber(string("0"));
}
template<class T> 
void BigNumber::InitbyInt(T x) {
	for (size_t i = 0; i<maxl; ++i)
		d[i] = 0;
	if (!x)
		d[0] = 1;
	while (x)
	{
		d[++d[0]] = x % 10000;
		x /= 10000;
	}
}
BigNumber::BigNumber(size_t x) :d(maxl) { InitbyInt<size_t>(x); }
string BigNumber::toString()
{
	string s("");
	int i;
	for (i = 3; i >= 1; --i)
		if (d[d[0]] >= ten[i])
			break;
	auto temp = d[d[0]];
	for (auto j = i; j >= 0; --j)
	{
		s += static_cast<char>(temp / ten[j] + '0');
		temp %= ten[j];
	}
	if (d[0]>1)
	{
		for (auto k = d[0] - 1; k>1; --k)
		{
			temp = d[k];
			for (auto j = 3; j >= 0; --j)
			{
				s += static_cast<char>(temp / ten[j] + '0');
				temp %= ten[j];
			}
		}
		temp = d[1];
		for (auto j = 3; j >= 0; --j)
		{
			s += static_cast<char>(temp / ten[j] + '0');
			temp %= ten[j];
		}
	}
	return s;
}
bool BigNumber::smaller(const BigNumber &a, const BigNumber &b, size_t delta)
{
	if (a.d[0] + delta != b.d[0])
		return a.d[0] + delta<b.d[0];
	for (auto i = a.d[0]; i>1; --i)
		if (a.d[i] != b.d[i + delta])
			return a.d[i]<b.d[i + delta];
	if (a.d[1] != b.d[1 + delta])
		return a.d[1]<b.d[1 + delta];
	return true;
}
void BigNumber::Minus(BigNumber &a, const BigNumber &b, size_t delta)
{
	size_t x = 0;
	for (size_t i = 1; i <= a.d[0] - delta; ++i)
	{
		x += 10000 + a.d[i + delta] - b.d[i];
		a.d[i + delta] = x % 10000;
		x = x / 10000 - 1;
	}
	while ((a.d[0]>1) && (a.d[a.d[0]] == 0))
		--a.d[0];
}
BigNumber operator +(const BigNumber &a, const BigNumber &b) {
	BigNumber c;
	c.d[0] = max(a.d[0], b.d[0]);
	size_t x = 0;
	for (size_t i = 1; i <= c.d[0]; ++i) {
		x += a.d[i] + b.d[i];
		c.d[i] = x % 10000;
		x /= 10000;
	}
	while (x) {
		c.d[++c.d[0]] = x % 10000;
		x /= 10000;
	}
	return c;
}

BigNumber operator -(const BigNumber &a, const BigNumber &b) {
	BigNumber c;
	c.d[0] = a.d[0];
	size_t x = 0;
	for (size_t i = 1; i <= c.d[0]; ++i) {
		x += 10000 + a.d[i] - b.d[i];
		c.d[i] = x % 10000;
		x = x / 10000 - 1;
	}
	while (c.d[0]>1 && c.d[c.d[0]] == 0)
		--c.d[0];
	return c;
}

BigNumber operator *(const BigNumber &a, const BigNumber &b) {
	BigNumber c;
	c.d[0] = a.d[0] + b.d[0];
	for (size_t i = 1; i <= a.d[0]; ++i) {
		size_t x = 0;
		for (size_t j = 1; j <= b.d[0]; ++j) {
			x += a.d[i] * b.d[j] + c.d[i + j - 1];
			c.d[i + j - 1] = x % 10000;
			x /= 10000;
		}
		c.d[i + b.d[0]] = x;
	}
	while (c.d[0]>1 && c.d[c.d[0]] == 0)
		--c.d[0];
	return c;
}
BigNumber BigNumber::big_pow(size_t n)const
{
	if(n==0)
	return BigNumber(1);
	auto ans= big_pow(n/2);
	ans=ans*ans;
	if(n&1)
		ans=ans*(*this);
	return ans;
}
BigNumber operator *(const BigNumber &a, const size_t &k)
{
	BigNumber c;
	c.d[0] = a.d[0];
	size_t x = 0;
	for (size_t i = 1; i <= a.d[0]; ++i)
	{
		x = a.d[i] * k + x;
		c.d[i] = x % 10000;
		x /= 10000;
	}
	while (x>0)
	{
		c.d[++c.d[0]] = x % 10000;
		x /= 10000;
	}
	while ((c.d[0]>1) && (c.d[c.d[0]] == 0))
		--c.d[0];
	return c;
}
BigNumber operator /(const BigNumber &a, const BigNumber &b)
{
	BigNumber c;
	auto Remainder = a;//余数
	BigNumber mid1[15];
	mid1[0] = b;
	for (auto i = 1; i <= 13; ++i)
		mid1[i] = mid1[i - 1] * 2;
	if(a.d[0] >=b.d[0])
	{
		for (auto i = a.d[0] - b.d[0]; i > 0; --i)
		{
			auto temp = 8192;
			for (auto j = 13; j >= 0; --j)
			{
				if (a.smaller(mid1[j], Remainder, i))
				{
					a.Minus(Remainder, mid1[j], i);
					c.d[i + 1] += temp;
				}
				temp /= 2;
			}
		}
		//i=0
		auto temp = 8192;
		for (auto j = 13; j >= 0; --j)
		{
			if (a.smaller(mid1[j], Remainder, 0))
			{
				a.Minus(Remainder, mid1[j], 0);
				c.d[0 + 1] += temp;
			}
			temp /= 2;
		}
	}
	c.d[0] = max(static_cast<size_t>(1), a.d[0] - b.d[0] + 1);
	while ((c.d[0]>1) && (c.d[c.d[0]] == 0))
		c.d[0]--;
	return c;
}
BigNumber operator %(const BigNumber &a, const BigNumber &b)
{
	BigNumber c;
	auto Remainder = a;//余数
	BigNumber mid1[15];
	mid1[0] = b;
	for (auto i = 1; i <= 13; ++i)
		mid1[i] = mid1[i - 1] * 2;
	if (a.d[0] >= b.d[0])
	{
		for (auto i = a.d[0] - b.d[0]; i > 0; --i)
		{
			auto temp = 8192;
			for (auto j = 13; j >= 0; --j)
			{
				if (a.smaller(mid1[j], Remainder, i))
				{
					a.Minus(Remainder, mid1[j], i);
					c.d[i + 1] += temp;
				}
				temp /= 2;
			}
		}
		//i=0
		auto temp = 8192;
		for (auto j = 13; j >= 0; --j)
		{
			if (a.smaller(mid1[j], Remainder, 0))
			{
				a.Minus(Remainder, mid1[j], 0);
				c.d[0 + 1] += temp;
			}
			temp /= 2;
		}
	}
	return Remainder;
}
bool operator < (const BigNumber &a, const BigNumber &b)
{
	if (a.d[0] != b.d[0])
		return a.d[0]<b.d[0];
	for (auto i = a.d[0]; i>1; --i)
		if (a.d[i] != b.d[i])
			return a.d[i]<b.d[i];
	if (a.d[1] != b.d[1])
		return a.d[1]<b.d[1];
	return false;
}
bool operator > (const BigNumber &a, const BigNumber &b)
{
	if (b.d[0] != a.d[0])
		return b.d[0]<a.d[0];
	for (auto i = b.d[0]; i>1; --i)
		if (a.d[i] != b.d[i])
			return b.d[i]<a.d[i];
	if (a.d[1] != b.d[1])
		return b.d[1]<a.d[1];
	return false;
}
bool operator ==(const BigNumber &a, const BigNumber &b)
{
	if (a.d[0] != b.d[0])
		return false;
	for (size_t i = 1; i <= a.d[0]; ++i)
		if (a.d[i] != b.d[i])
			return false;
	return true;
}
bool operator != (const BigNumber &a, const BigNumber &b) { return !(a==b); }
bool operator <= (const BigNumber &a, const BigNumber &b) { return !(a>b); }
bool operator >= (const BigNumber &a, const BigNumber &b) { return !(a<b); }
istream& operator>>(istream& is, BigNumber& n) {
	string s;
	is >> s;
	n = BigNumber(s);
	return is;
}
ostream& operator<<(ostream& os, BigNumber& n) {
	os << n.toString();
	return os;
}
ostream& operator<<(ostream& os, BigNumber&& n) {
	os << n.toString();
	return os;
}
inline int64_t double2int64(double d)//d<1125899906842623
{
	d += 6755399441055744.0;// 1.5 * 2^52
	auto i = reinterpret_cast<int64_t&>(d);
	i <<= 13;
	i >>= 13;
	return i;
}
BigNumber BigNumber::sqrt()const {
	BigNumber l = 0, r = *this, _mid;
	BigNumber mid=0;
	while (l<r) {
		mid = _mid = (l + r) /2;
		mid = mid*mid;
		if (*this == mid)
			return _mid;
		if (*this<mid)
			r = _mid - 1; 
		else if (*this>mid)
			l = _mid + 1;
	}
	return l;
}
BigNumber BigNumber::sqrt3()const {
	BigNumber l = 0, r = *this, _mid;
	BigNumber mid = 0;
	while (l<r) {
		mid = _mid = (l + r) /2;
		mid = mid*mid*mid;
		if (*this == mid)
			return _mid;
		if (*this<mid)
			r = _mid - 1; 
		else if (*this>mid)
			l = _mid + 1;
	}
	return l;
}