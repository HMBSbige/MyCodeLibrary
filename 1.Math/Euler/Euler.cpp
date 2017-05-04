typedef uintmax_t ull;
ull Euler(ull n)
{
	ull a = n;
	for (int i = 2; i*i <= a; i++) {
		if (a%i == 0) {
			n = n / i*(i - 1);   
			while (a%i == 0) a /= i;
		}
	}
	if (a>1) n = n / a*(a - 1);
	return n;
}
vector<ull> MakeEuler(ull N)
{
	vector<ull> phi(N+1);
	int i, j;
	for (i = 1; i <= N; ++i)
		phi[i] = i;
	for (i = 2; i <= N; i += 2)
		phi[i] /= 2;
	for (i = 3; i <= N; i += 2)
		if (phi[i] == i) {
			for (j = i; j <= N; j += i)
				phi[j] = phi[j] / i * (i - 1);
		}
	return phi;
}