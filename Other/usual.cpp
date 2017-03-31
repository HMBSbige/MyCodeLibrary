#include <iostream> 
#define DEBUG
#ifdef DEBUG
#include <fstream>	
std::ofstream outfile;
#endif
//////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
#ifdef DEBUG	
	outfile.open("C:\\Users\\Bruce Wayne\\Desktop\\out.txt", std::ios::trunc);
	std::cout.rdbuf(outfile.rdbuf());
#endif
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
#ifdef DEBUG
	outfile.close();
	system("pause");
#endif // DEBUG
	return 0;
}