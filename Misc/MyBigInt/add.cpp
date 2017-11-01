std::string add(std::string a, std::string b)
{
	register size_t i, j;
	char x, y, z;
	std::string c;
	int up = 0;
	for (i = 0,j = 0;i <= a.size() - 1 || j <= b.size() - 1;++i,++j)
	{
		if (i>a.size() - 1)
			x = '0';
		else
			x = a[a.size() - 1-i];
		if (j>b.size() - 1)
			y = '0';
		else
			y = b[b.size() - 1-j];
		z = x - '0' + y - '0';
		if (up)
			z += 1;
		if (z>9) {
			up = 1;
			z %= 10;
		}
		else
			up = 0;
		c.push_back(z + '0');
	}
	if (up)
		c.push_back ('1');
	reverse(c.begin(), c.end());
	return c;
}