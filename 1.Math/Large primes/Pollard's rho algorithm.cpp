//https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm.
typedef uint64_t ull;
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
		return *min_element(factor.begin(), factor.end());
	}
private:
	static ull mult_mod(ull a, ull b, ull c) {/// return a*b%c
		a %= c;
		b %= c;
		ull ret = 0;
		auto tmp = a;
		while (b) {
			if (b & 1) {
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
	Miller_Rabin mr;
	RandomINT r;
	static ull gcd(ull a, ull b)
	{
		if (a == 0)
			return 1;
		while (b)
		{
			auto t = a%b;
			a = b;
			b = t;
		}
		return a;
	}
	ull Pollard_rho(ull x, ull c)
	{
		ull i = 1, k = 2;
		auto x0 = r.GetRandomInteger<ull>(0, x - 1);//[0,x-1]
		auto y = x0;
		while (true) {
			++i;
			x0 = (mult_mod(x0, x0, x) + c) % x;
			ull d;
			if (y<x0)
				d = gcd(x0 - y, x);
			else
				d = gcd(y - x0, x);
			if (d != 1 && d != x)
				return d;
			if (y == x0)
				return x;
			if (i == k) {
				y = x0;
				k += k;
			}
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
		auto p = n;
		while (p >= n)
			p = Pollard_rho(p, r.GetRandomInteger<ull>(1, n - 1));
		findfac(p);
		findfac(n / p);
	}
};