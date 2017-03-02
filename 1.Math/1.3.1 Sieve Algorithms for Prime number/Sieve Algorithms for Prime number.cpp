#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>
#define ull unsigned long long//<=18446744073709551615
using namespace std;
vector<bool> isPrime;
vector<ull> Primes;
void _MakePrime(ull N)//一般线性筛法
{
	isPrime = vector<bool>(N+1,true);
	vector<ull>().swap(Primes);
	isPrime[0] = false;
	isPrime[1] = false;
	for (ull i = 2; i<=N; ++i)
		if (isPrime[i]) {
			Primes.push_back(i);
			for (ull k = i*i; k<=N; k += i)
				isPrime[k] = false;
		}
}
void __MakePrime(ull N)//快速线性筛法
{
	++N;
	isPrime = vector<bool>(N + 1, true);
	vector<ull>().swap(Primes);
	isPrime[0] = false;
	isPrime[1] = false;

	for (ull i = 2; i <N; ++i)
	{
		if (isPrime[i])
			Primes.push_back(i);
		for (ull j = 0; j < Primes.size() && i * Primes[j] < N; j++)
		{
			isPrime[i * Primes[j]] = 0;
			if (!(i % Primes[j]))
				break;
		}
	}
}
void ___MakePrime(ull N)//魔改快速线性筛法
{
	--N;
	ull half = N / 2;
	ull sn = (ull)sqrt(N);
	vector<bool> p(half,1);// 初始化全部奇数为素数。p[0]对应3，即p[i]对应2*i+3   
	for (ull i = 0; i < sn; i++) {
		if (p[i])//如果 2*i+3 是素数  
		{
			for (ull k = i + i + 3, j = k*i + k + i; j < half; j += k)
				// 筛法起点是 p[i]所对应素数的平方 k^2                                          
				// k^2在 p 中的位置是 k*i+k+i  
				//    下标 i         k*i+k+i  
				//对应数值 k=i+i+3   k^2           
				p[j] = false;
		}
	}
	//素数都存放在 p 数组中，p[i]=true代表 i+i+3 是素数。  
	vector<ull>(1,2).swap(Primes);
	isPrime = vector<bool>(N + 1, true);
	for (ull i = 0;i<half;++i) {
		if (p[i]) {
			Primes.push_back(i + i + 3);
		}
	}
}
void ____MakePrime(ull N)//膜改快速线性筛法
{
	--N;
	N/= 2;
	ull sn = (ull)(sqrt(2*N)/2);
	vector<bool> p(N, 1);  
	for (ull i = 0; i < sn; i++) {
		if (p[i]) 
		{
			for (ull j=i*(2*i+6)+3;j<N;j+=2*i+3)          
				p[j] = false;
		}
	}

	vector<ull>(1, 2).swap(Primes);
	isPrime = vector<bool>(N + 1, true);
	for (ull i = 0; i<N; ++i) {
		if (p[i]) {
			Primes.push_back(i + i + 3);
		}
	}
}
void output() {
	/*for (ull &x : Primes)
		cout << x << " ";
	cout << endl;*/
	cout<< "个数：" << Primes.size() << endl;
}
int main()
{
	ull N = 5000000;
	clock_t start, finish;
	double totaltime;
	
	start = clock();
	_MakePrime(N);
	//output();
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << totaltime << "秒！" << endl;

	start = clock();
	__MakePrime(N);
	//output();
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << totaltime << "秒！" << endl;

	start = clock();
	___MakePrime(N);
	//output();
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << totaltime << "秒！" << endl;

	start = clock();
	____MakePrime(N);
	//output();
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << totaltime << "秒！" << endl;

	system("pause");
	return 0;
}