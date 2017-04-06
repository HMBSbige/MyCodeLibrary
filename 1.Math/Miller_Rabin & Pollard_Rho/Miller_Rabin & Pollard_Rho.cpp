typedef int64_t ll;
typedef uint64_t ull;
class Miller_Rabin {
private:
	const int S;
	ll  pow_mod(ll   a, ll   n, ll   mod)
	{
		ll ret = 1;
		ll temp = a%mod;
		while (n)
		{
			if (n & 1)
				ret = mult_mod(ret, temp, mod);
			temp = mult_mod(temp, temp, mod);
			n >>= 1;
		}
		return ret;
	}
	bool check(ll a, ll n, ll x, ll t)
	{
		ll ret = pow_mod(a, x, n);
		ll last = ret;
		register ll i;
		for (i = 1; i <= t; ++i)
		{
			ret = mult_mod(ret, ret, n);
			if (ret == 1 && last != 1 && last != n - 1)
				return true;
			last = ret;
		}
		if (ret != 1)
			return true;
		return false;
	}
public:
	ll mult_mod(ll  a, ll   b, ll   c)
	{
		a %= c;
		b %= c;
		ll ret = 0;
		ll tmp = a;
		while (b)
		{
			if (b & 1)
			{
				ret += tmp;
				if (ret > c)
					ret -= c;
			}
			tmp <<= 1;
			if (tmp > c)
				tmp -= c;
			b >>= 1;
		}
		return ret;
	}
	Miller_Rabin() :S(10) {}
	bool isPrime(ull n)
	{
		if (n < 2)return false;
		if (n == 2)return true;
		if ((n & 1) == 0)return false;
		ull x = n - 1;
		ull t = 0;
		while ((x & 1) == 0) { x >>= 1; t++; }
		srand((unsigned int)time(NULL));
		register int i;
		for (i = 0; i < S; i++)
		{
			ull a = rand() % (n - 1) + 1;
			if (check(a, n, x, t))
				return false;
		}
		return true;
	}
};
class Pollard_Rho {
public:
	Pollard_Rho() {}
	std::vector<ull> factor;
	ull minfactor(ull n) {
		std::vector<ull>().swap(factor);
		findfac(n);
		if (!factor.size()) {
			return 1;
		}
		return factor[min_element(factor.begin(), factor.end()) - factor.begin()];
	}
private:
	Miller_Rabin mr;
	ll gcd(ll a, ll b)
	{
		if (a == 0)return 1;//???????
		if (a<0) return gcd(-a, b);
		if (b<0) return gcd(a, -b);
		while (b)
		{
			ll t = a%b;
			a = b;
			b = t;
		}
		return a;
	}
	ll mult_mod(ll  a, ll   b, ll   c)
	{
		return mr.mult_mod(a, b, c);
	}
	ull Pollard_rho(ull x, ull c)
	{
		ull i = 1, k = 2;
		ull x0 = rand() % x;
		ull y = x0;
		while (1)
		{
			i++;
			x0 = (mult_mod(x0, x0, x) + c) % x;
			ull d = gcd(y - x0, x);
			if (d != 1 && d != x) return d;
			if (y == x0) return x;
			if (i == k) { y = x0; k += k; }
		}
	}
	void findfac(ull n)
	{
		if (n == 1) {
			factor.push_back(n);
			return;
		}
		if (mr.isPrime(n))//素数
		{
			factor.push_back(n);
			return;
		}
		ull p = n;
		while (p >= n)
			p = Pollard_rho(p, rand() % (n - 1) + 1);
		findfac(p);
		findfac(n / p);
	}
};