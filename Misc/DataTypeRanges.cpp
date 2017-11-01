#include <cmath>
#include <climits>
#include <cstdio>
#include <iostream>
using namespace std;
void main()
{

	printf("             short取值范围:%d ~ %d\n", SHRT_MIN, SHRT_MAX);
	printf("    unsigned short取值范围:%d ~ %d\n", 0, USHRT_MAX);
	printf("               int取值范围:%d ~ %d\n", INT_MIN, INT_MAX);
	printf("      unsigned int取值范围:%d ~ %u\n", 0, UINT_MAX);
	printf("              long取值范围:%d ~ %d\n", LONG_MIN, LONG_MAX);
	printf("     unsigned long取值范围:%d ~ %lu\n", 0, ULONG_MAX);
	printf("         long long取值范围:%I64d ~ %I64d\n", LLONG_MIN, LLONG_MAX);
	printf("unsigned long long取值范围:%d ~ %I64u\n", 0, ULLONG_MAX);
	printf("     (long) double取值范围:±%.16e之间\n最小精度：%.16e\n", DBL_MAX, DBL_MIN);
	printf("             float取值范围:±%.9e之间\n最小精度：%.9e\n", FLT_MAX, FLT_MIN);


	cout << "\n";
	system("pause");
}
/*
short取值范围:-32768 ~ 32767
unsigned short取值范围:0 ~ 65535
int取值范围:-2147483648 ~ 2147483647
unsigned int取值范围:0 ~ 4294967295
long取值范围:-2147483648 ~ 2147483647
unsigned long取值范围:0 ~ 4294967295
long long取值范围:-9223372036854775808 ~ 9223372036854775807
unsigned long long取值范围:0 ~ 18446744073709551615
(long) double取值范围:±1.7976931348623157e+308之间
最小精度：2.2250738585072014e-308
float取值范围:±3.402823466e+38之间
最小精度：1.175494351e-38
*/
