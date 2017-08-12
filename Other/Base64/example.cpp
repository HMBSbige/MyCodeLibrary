#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Base64.h"
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

	string PATH = R"(C:\Users\Bruce Wayne\Desktop\in.txt)";
	string OUTPATH = R"(C:\Users\Bruce Wayne\Desktop\out.txt)";
	string instr = textfile2str(PATH);
	str2file(Base64::Decode(instr),OUTPATH);
	system("pause");
	return 0;
}
