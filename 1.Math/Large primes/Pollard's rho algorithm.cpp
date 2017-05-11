typedef int64_t ll;
typedef uint64_t ull;
/*
https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm.
*/
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