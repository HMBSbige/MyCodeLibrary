//https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
typedef uint64_t ull;
class RandomINT {
private:
	std::mt19937 gen;
public:
	RandomINT() :gen(unsigned(time(nullptr))) {};
	template<class T = long long>
	T GetRandomInteger(T a, T b) {///return random integer in [a,b]
		if (a>b)
			swap(a, b);
		std::uniform_int_distribution<T> dis(a, b);
		return dis(gen);
	}
};
class Miller_Rabin {
private:
	const size_t S;
	static ull pow_mod(ull base, ull exp, ull modulus) {///return base**exp%modulus
		base %= modulus;
		ull result = 1;
		while (exp > 0) {
			if (exp & 1)
				result = mult_mod(result, base, modulus);
			base = mult_mod(base, base, modulus);
			exp >>= 1;
		}
		return result;
	}

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
	//以a为基,n-1=x*2^t    a^(n-1)=1(mod n)    验证n是不是合数
	//一定是合数返回true,不一定返回false
	static bool check(ull a, ull n, ull x, ull t)
	{
		auto ret = pow_mod(a, x, n);
		auto last = ret;
		for (ull i = 1; i <= t; ++i)
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
	Miller_Rabin() :S(10) {}
	//素数返回true 可能是伪素数,但概率极小(2^(-S))
	//合数返回false
	bool isPrime(ull n) const
	{
		if (n < 2)return false;
		if (n == 2)return true;
		if ((n & 1) == 0)return false;//偶数
		auto x = n - 1;
		ull t = 0;
		while ((x & 1) == 0) {
			x >>= 1;
			++t;
		}
		RandomINT r;
		for (size_t i = 0; i < S; ++i)
		{
			auto a = r.GetRandomInteger<ull>(1, n - 1);//[1,n-1]的随机数
			if (check(a, n, x, t))
				return false;
		}
		return true;
	}
};