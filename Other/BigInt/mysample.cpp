#include <iostream> 
#include "bignumber\bigInt.h"
#define DEBUG
#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
#ifdef ofile	
	outfile.open("C:\\Users\\Bruce Wayne\\Desktop\\out.txt", std::ios::trunc);
	std::cout.rdbuf(outfile.rdbuf());
#endif
	//////////////////////////////////////////////////////////////////////
	
	for (size_t i = 64; i <= 128; ++i) {
		BigInt::Rossi n1(1);
		n1 <<= i;
		if (i != 64)
			std::cout << ",";
		std::cout <<  "\""<<n1.toStrDec() << "\"";
	}

	//////////////////////////////////////////////////////////////////////
#ifdef ofile
	outfile.close();
#endif
#ifdef DEBUG
	system("pause");
#endif
	return 0;
}