class factorial {
private:
	std::vector<size_t> a;
public:
	factorial() {}
	factorial(size_t n) {calc(n);}
	size_t calc(size_t n)
	{
		a= std::vector<size_t>(1, 1);
		size_t i, j, c, w;

		for (i = 1; i <= n; i++)
		{
			c = 0;
			for (j = 0; j < a.size(); ++j)
			{
				a[j] = a[j] * i + c;
				c = a[j] / 10000;
				a[j] = a[j] % 10000;
			}
			if (c>0) {
				a.push_back(c);
			}
		}

		w = (a.size() - 1) * 4 + (size_t)log10(a[a.size() - 1]) + 1;
		return w;
	}
	void output(std::ostream& os) {
		os << a.at(a.size() - 1);
		for (size_t i = 1; i < a.size(); ++i) {
			os.fill('0');
			os.width(4);
			std::setiosflags(std::ios::right);
			os << a.at(a.size() - 1 - i);
		}
	}
};