typedef uint64_t ull;
ull Permutation(const ull& m, const ull& n) {
	if (m > n) return 0;
	register ull i,ans=1;
	for (i = n - m + 1; i <= n; ++i)
		ans *= i;
	return ans;
}
ull Combination(const ull& m, const ull& n) {
	if (m > n) return 0;
	register ull i, ans = Permutation(m,n);
	for (i = 2; i <= m; ++i)
		ans /= i;
	return ans;
}