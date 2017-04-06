typedef int64_t ll;
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll r = ex_gcd(b, a%b, y, x);
	y -= x*(a / b);
	return r;
}