#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Base64.h"
#include "character_encoding_conversion.h"
using namespace std;
string textfile2str(const string& PATH)
{
	ifstream file(PATH);
	ostringstream oss;
	oss << file.rdbuf();
	file.close();
	return oss.str();
}
void str2file(const string& str,const string& PATH)
{
	ofstream file(PATH, std::ios::trunc);
	file << str;
	file.close();
}

int main() {
	std::ios::sync_with_stdio(false);
	_wsetlocale(LC_ALL, L"");

	CharacterEncodingConversion cec;
	string u8string = u8"高风险，高回报，恶名昭彰的 AWP 因其标志性的枪声和—枪—个的准则而为人熟知。";
	string encodestr = "6auY6aOO6Zmp77yM6auY5Zue5oql77yM5oG25ZCN5pit5b2w55qEIEFXUCDlm6DlhbbmoIflv5fmgKfnmoTmnqrlo7DlkozigJTmnqrigJTkuKrnmoTlh4bliJnogIzkuLrkurrnhp/nn6XjgII=";
	
	cout << "开始解码：" << endl;
	string decodestr = Base64::Decode(encodestr);
	
	
	if (decodestr == u8string)
	{
		cout << "解码成功,结果为：" << endl;
		wcout << cec.U8stringToWstring(decodestr) << endl;
	}	
	else 
		cout << "解码失败" << endl;
	cout << endl;

	cout << "开始编码：" << endl;
	if (Base64::Encode(u8string) == encodestr)
		cout << "编码正确"<<endl;
	else
		cout << "编码错误" << endl;
	cout << endl;

	cout << "测试从文件解码：" << endl;
	string PATH = R"(C:\Users\Bruce Wayne\Desktop\in.txt)";
	string OUTPATH = R"(C:\Users\Bruce Wayne\Desktop\out.txt)";

	string instr = textfile2str(PATH);//read

	str2file(Base64::Decode(instr), OUTPATH);//write

	system("pause");
	return 0;
}