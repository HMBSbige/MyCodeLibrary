std::string NumberBaseConversion(const uint8_t& x, const uint8_t& y,const std::string& s) //2<=x,y<=36
{
	std::string res;
	int sum = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] >= '0' && s[i] <= '9')
			sum = sum*x + s[i] - '0';
		else if(s[i] >= 'A' && s[i] <= 'Z')
			sum = sum*x + s[i] - 'A' + 10;
		else if (s[i] >= 'a' && s[i] <= 'z')
			sum = sum*x + s[i] - 'a' + 10;
	}
	while (sum){
		char tmp = sum%y;
		sum /= y;
		if (tmp <= 9)
			tmp += '0';
		else
			tmp -= 10 - 'A';
		res = tmp + res;
	}
	if (!res.size())
		return "0";
	if (s[0] == '-')
		return '-' + res;
	return res;
}