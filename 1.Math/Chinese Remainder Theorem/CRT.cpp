typedef uint64_t ull;
typedef int64_t ll;
inline ll mul_inv(ll a, ll b)// returns x where (a * x) % b == 1
{
	ll b0 = b, t, q;
	ll x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
ull chinese_remainder(std::vector<ull> n, std::vector<ull> a)//x=a[i](mod n[i])
{
	ull p, prod = 1, sum = 0;
	register size_t i;
	for (i = 0; i < n.size(); ++i) prod *= n[i];

	for (i = 0; i < n.size(); ++i) {
		p = prod / n[i];
		sum += a[i] * mul_inv(p, n[i]) * p;
		sum %= prod;
	}
	return (sum+ prod) % prod;
}