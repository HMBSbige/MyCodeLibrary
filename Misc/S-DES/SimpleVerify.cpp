#include <iostream>
#include <string>

using namespace std;

int p10[] = { 3,5,2,7,4,10,1,9,8,6 };
int p8[] = { 6,3,7,4,8,5,10,9 };
int p4[] = { 2,4,3,1 };
int ip[] = { 2,6,3,1,4,8,5,7 };
int ip1[] = { 4,1,3,5,7,2,8,6 };
int ep[] = { 4,1,2,3,2,3,4,1 };
int s0[][4] = {
	{ 1,0,3,2 },
	{ 3,2,1,0 },
	{ 0,2,1,3 },
	{ 3,1,3,2 },
};
int S1[][4] = {
	{ 0,1,2,3 },
	{ 2,0,1,3 },
	{ 3,0,1,0 },
	{ 2,1,0,3 },
};
string plaintext = "11010100";
string key = "0111111101";
string k1, k2;//定义两个子密钥 
int get_num(const string str)
{
	if (str == "11")
		return 3;
	else if (str == "10")
		return 2;
	else if (str == "01")
		return 1;
	else
		return 0;
}
string get_binary(const int num)
{
	switch (num) {
		case 3:
			return "11";
		case 2:
			return "10";
		case 1:
			return "01";
		case 0:
			return "00";
		default: 
			return nullptr;//impossible
	}
}
string p10_swap(string key)
{
	//P10置换 
	string t;
	for (int i = 0; i<10; ++i)
		t += key[p10[i] - 1];
	return t;
}
string p8_swap(string key)
{
	//P8置换 
	string t;
	for (int i = 0; i<8; ++i)
		t += key[p8[i] - 1];
	return t;
}
string p4_swap(string key)
{
	//P4置换 
	string t;
	for (int i = 0; i<4; ++i)
		t += key[p4[i] - 1];
	return t;
}
string rsl(string s, const int offset)
{
	//循环左移
	string t = s.substr(offset) + s.substr(0, offset);
	return t;
}
string ip_swap(string key)
{
	//IP置换 
	string t;
	for (int i = 0; i<8; ++i)
		t += key[ip[i] - 1];
	return t;
}
string ip1_swap(string key)
{
	//IP逆置换 
	string t;
	for (int i = 0; i<8; ++i)
		t += key[ip1[i] - 1];
	return t;
}
string ep_swap(string key)
{
	//EP置换 
	string t;
	for (int i = 0; i<8; ++i)
		t += key[ep[i] - 1];
	return t;
}
string xor(string key1, string key2)
{
	//异或
	string t;
	for (int i = 0; i<key1.length(); ++i) {
		if (key1[i] != key2[i])
			t += '1';
		else
			t += '0';
	}
	return t;
}
string s0_swap(string key)
{
	string row, col;
	row += key[0];
	row += key[3];
	col += key[1];
	col += key[2];
	return get_binary(s0[get_num(row)][get_num(col)]);
}
string s1_swap(string key)
{
	string row, col;
	row += key[0];
	row += key[3];
	col += key[1];
	col += key[2];
	return get_binary(S1[get_num(row)][get_num(col)]);
}
string swap(string key)
{
	return key.substr(4) + key.substr(0, 4);
}
string fk(string m, const string subkey) {//fk函数 
	const string ep_r = ep_swap(m.substr(4));
	string xor_result = xor(ep_r, subkey);
	const string result = s0_swap(xor_result.substr(0, 4)) + s1_swap(xor_result.substr(4));//得到的四位输出
	return xor(p4_swap(result), m.substr(0, 4)) + m.substr(4);
}
int main() {
	//获取子密钥 
	string t0 = p10_swap(key);
	cout << "t0:" << t0 << endl;
	//高低位循环左移一位并合并 
	string t1 = rsl(t0.substr(0, 5), 1) + rsl(t0.substr(5), 1);
	cout << "t1:"<<t1 << endl;
	k1 = p8_swap(t1);//子密钥K1
	//高低位循环左移两位并合并
	const string t2 = rsl(t1.substr(0, 5), 2) + rsl(t1.substr(5), 2);
	cout << "t2:" << t2 << endl;
	k2 = p8_swap(t2);//子密钥K2
	cout << "子密钥k1：" << k1 << endl << "子密钥k2：" << k2 << endl;
	//第一轮fk函数
	const string m = ip_swap(plaintext);
	cout << "m:" << m << endl;
	const string fk1_result = fk(m, k2);
	cout << "第一轮fk函数结果：" << fk1_result << endl;
	const string after_swap = swap(fk1_result);
	//第二轮fk函数
	const string fk2_result = fk(after_swap, k1);
	cout << "第二轮fk函数结果：" << fk2_result << endl;
	cout << "最终得到的密文为：" << ip1_swap(fk2_result) << endl;
	return 0;
}