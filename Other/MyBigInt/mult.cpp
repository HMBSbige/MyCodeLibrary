std::string mult(std::string a, std::string b)
{
	
	register size_t i, j;
	size_t alen = a.size(), blen = b.size();
	size_t maxn = alen + blen - 1;
	int sum = 0, flag = 0;
	std::vector<std::vector<int> > res(maxn, std::vector<int>(blen,0));
	std::string result;
	
	for (i = 0; i<alen; i++)
		for (j = 0; j<blen; j++) 
			res[i][j] = (a[i] - '0')*(b[j] - '0');

	for (i = 0; i <= alen - 1; ++i)
	{
		for (j = 0; j <= blen - 1; ++j)
			sum = sum + res[alen - 1 - i + j][blen - 1 - j];
		result.push_back(sum % 10) ;
		sum = sum / 10;
	}

	if (blen >= 2)
		for (i = 0; i <= blen - 2; ++i)
		{
			for (j = 0; j <= blen - 2 - i; ++j)
				sum = sum + res[blen - 2 - i - j][j];
			result.push_back(sum % 10);
			sum = sum / 10;
		}

	if (sum != 0) 
		result.push_back(sum);

	for (i = 0; i<result.size(); ++i)
		result[i] += '0';
	reverse(result.begin(), result.end());

	while (1)
	{
		if (result.size() != a.size() && result[0] == '0')
			result.erase(result.begin());
		else
			break;
	}
	return result;
}