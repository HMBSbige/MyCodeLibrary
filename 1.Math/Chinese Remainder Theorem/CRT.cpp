typedef uint64_t ull;
typedef int64_t ll;
void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d){
    if (!b) {d = a, x = 1, y = 0;}
    else{
        ex_gcd(b, a % b, y, x, d);
        y -= x * (a / b);
    }
}
ll mul_inv(ll t, ll p){//如果不存在，返回-1 
    ll d, x, y;
    ex_gcd(t, p, x, y, d);
    return d == 1 ? (x % p + p) % p : -1;
}
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
{//n are relatively-prime
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
typedef std::pair<ll, ll> PLL;
PLL linear(std::vector<ll> A, std::vector<ll> B, std::vector<ll> M) //return x where A[i]*x = B[i] (mod M[i]) 
{
	ll x = 0, m = 1;
	register size_t i;
	for (i = 0; i < A.size(); i++) {
		ll a = A[i] * m, b = B[i] - A[i] * x, d = gcd(M[i], a);
		if (b % d != 0)  
			return PLL(0, -1);//if there are no possible values
		ll t = b / d * mul_inv(a / d, M[i] / d) % (M[i] / d);
		x = x + m*t;
		m *= M[i] / d;
	}
	x = (x % m + m) % m;
	return PLL(x, m);//m is lcm
}