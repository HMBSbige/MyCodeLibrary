typedef int64_t ll;
typedef uint64_t ull;
/*
https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
*/
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