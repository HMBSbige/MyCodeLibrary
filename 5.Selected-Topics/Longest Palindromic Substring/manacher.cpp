//返回最长回文子串的长度
size_t manacher(const string& s)
{
	string str="#";//specical char
	for (auto&x : s)
	{
		str.push_back(x);
		str +="#";
	}
	auto n = str.size();
	size_t mx = 0,id=0;
	vector<size_t> p(n,1);
	for (size_t i = 1;i<n;++i)
	{
		if (mx > i)
			p[i] = min(p[2 * id - i], mx - i);
		else
			p[i] = 1;
		while (i >= p[i] && i + p[i]<n && str[i + p[i]] == str[i - p[i]])
			++p[i];
		if (p[i] + i > mx)
		{
			mx = p[i] + i;
			id = i;
		}
	}
	return *max_element(p.begin(), p.end()) - 1;
}