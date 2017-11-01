std::string sub(std::string s1, std::string s2)//s1,s2>0 返回abs(s1-s2)
{
	if (s1.size()<s2.size()||(s1 < s2 && s1.size()==s2.size()))
		swap(s1, s2);
	std::string t;
	size_t i;
	size_t l1= s1.size(),l2= s2.size();
	t.resize(l1);
	for (i = 0; i <= l2 - 1; ++i)
	{
		if (s1[l1 - 1-i] - s2[l2 - 1 - i] >= 0)
			t[l1 - 1 - i] = s1[l1 - 1 - i] - s2[l2 - 1 - i] + '0';
		else
		{
			t[l1 - 1 - i] = 10 + s1[l1 - 1 - i] - s2[l2 - 1 - i] + '0';
			--s1[l1 - 1 - i - 1];
		}
	}
	if(l1>l2)
		for (size_t j = 0; j <= l1-l2 - 1; ++j) {
			t[l1 - l2 - 1-j] = s1[l1 - l2 - 1 - j];
		}
	while (t[0] == '0')
		t.erase(t.begin());
	if (t.size() == 0) 
		return "0";
	return t;
}