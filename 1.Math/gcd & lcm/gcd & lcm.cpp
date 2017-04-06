typedef int64_t ll;
ll gcd(ll a, ll b)//辗转相除法 迭代
{
	if (a<0) return gcd(-a, b);
	if (b<0) return gcd(a, -b);
	if (a == 0) return b;
	while (b)
	{
		ll t = a%b;
		a = b;
		b = t;
	}
	return a;
}
ll gcd(const ll& a, const ll& b)//辗转相除法 递归
{
	if (a<0) return gcd(-a, b);
	if (b<0) return gcd(a, -b);
	return b == 0 ? a : gcd1(b, a%b);
}
//stein算法
ll gcdcore(ll a, ll b) {
	if (a == 0) return b;
	if (b == 0) return a;
	while ((a & 0x1) == 0) {
		a = a >> 1;
	}
	if (a<b) {
		b = (b - a) >> 1;
		return gcdcore(b, a);
	}
	else {
		a = (a - b) >> 1;
		return gcdcore(a, b);
	}
}
ll gcd(ll a, ll b) {
	if (!a && !b)
		return 0;
	if (a<0) return gcd(-a, b);
	if (b<0) return gcd(a, -b);
	ll c = 0;
	while (((a & 0x1) == 0) && ((b & 0x1) == 0)) {
		a = a >> 1;
		b = b >> 1;
		++c;
	}
	if ((a & 0x1) == 0) {
		a = a >> 1;
		return gcdcore(a, b) << c;
	}
	else {
		return gcdcore(b, a) << c;
	}
}
ll lcm(const ll& a, const ll& b)//最小公倍数
{
	return a / gcd(a, b) *b;
}