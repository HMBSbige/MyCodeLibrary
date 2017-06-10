vector<vector<int> > table;
set<T> setOfLCS;
template <class T> T Reverse(T str)
{
	reverse(str.begin(), str.end());
	return str;
}
template <class T> int lcs(T X, T Y)
{
	size_t m = X.size();
	size_t n = Y.size();
	table = vector<vector<int> >(m + 1, vector<int>(n + 1));
	for (int i = 0; i<m + 1; ++i)
	{
		for (int j = 0; j<n + 1; ++j)
		{
			if (i == 0 || j == 0)
				table[i][j] = 0;

			else if (X[i - 1] == Y[j - 1])
				table[i][j] = table[i - 1][j - 1] + 1;

			else
				table[i][j] = max(table[i - 1][j], table[i][j - 1]);
		}
	}
	return table[m][n];
}
template <class T> void traceBack(size_t i, size_t j, T X, T Y, T lcs_str)
{
	while (i>0 && j>0)
	{
		if (X[i - 1] == Y[j - 1])
		{
			lcs_str.push_back(X[i - 1]);
			--i;
			--j;
		}
		else
		{
			if (table[i - 1][j] > table[i][j - 1])
				--i;
			else if (table[i - 1][j] < table[i][j - 1])
				--j;
			else
			{
				traceBack<T>(i - 1, j, X, Y, lcs_str);
				traceBack<T>(i, j - 1, X, Y, lcs_str);
				return;
			}
		}
	}
	setOfLCS.insert(Reverse<T>(lcs_str));
}