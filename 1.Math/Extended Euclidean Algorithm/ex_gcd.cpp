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
ll exgcd(ll m,ll n,ll &x,ll &y)
{
    ll x1,y1,x0,y0;
    x0=1; y0=0;
    x1=0; y1=1;
    x=0; y=1;
    ll r=m%n;
    ll q=(m-r)/n;
    while(r)
    {
        x=x0-q*x1; y=y0-q*y1;
        x0=x1; y0=y1;
        x1=x; y1=y;
        m=n; n=r; r=m%n;
        q=(m-r)/n;
    }
    return n;
}