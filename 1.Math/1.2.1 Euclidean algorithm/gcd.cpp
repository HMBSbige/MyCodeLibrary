int64_t gcd(int64_t a, int64_t b) {
	return b == 0 ? a : gcd(b, a%b);
}
int64_t lcm(int64_t a, int64_t b)
{
	return a * b / gcd(a, b);
}