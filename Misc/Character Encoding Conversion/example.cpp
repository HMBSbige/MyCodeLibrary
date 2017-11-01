#include <iostream>
#include <vector>
#include "character_encoding_conversion.h"
#include <fstream>

using namespace std;
CharacterEncodingConversion Convert;
inline void test()
{
	wofstream woutfile(R"(C:\Users\Bruce Wayne\Desktop\wout.txt)",std::ios::trunc);
	ofstream outfile(R"(C:\Users\Bruce Wayne\Desktop\out.txt)", std::ios::trunc);
		
	//使wofstream用UTF-8输出
	try {
		woutfile.imbue(locale("zh_CN.UTF8"));//runtime_error in VS2017
	}
	catch (std::runtime_error) {
		woutfile.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));
	}
	
	char *test_c = "中文char*";
	wchar_t *test_wc = L"中文wchar_t*";
	string test_string = "中文string";
	wstring test_wstring = L"中文wstring";
	string test_u8string = u8"中文 utf-8 string";

	woutfile << Convert.U8stringToWstring(test_u8string) << endl;
	outfile << Convert.WstringToU8string(test_wstring) << endl;

	outfile.close();
	woutfile.close();
}
int main() {
	_wsetlocale(LC_ALL, L"");
	std::ios::sync_with_stdio(false);
	test();
	system("pause");
	return 0;
}