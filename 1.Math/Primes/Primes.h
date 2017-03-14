#pragma once
#include <vector>
#include <set>
#include <new>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
typedef uintmax_t ull;

class Primes
{
private:
	set<ull> Prime;
	bool *isPrime= NULL;
	ull *vecPrime= NULL;
	void release();
public:
	Primes(ull);
	~Primes();
	void MakePrime(ull);//膜改筛法素数生成器
	ull Number();//返回生成的素数个数
	ull Number(ull n);//返回<=n的素数的个数
	ull at(ull n);//返回第n个素数，错误返回0
	bool isPrimeNumer(ull);//判断是否是素数
	ull find(ull);//返回n是第几个素数，错误返回0
	vector<pair<ull, ull> >factor(ull n);//将n分解质因数
	ull Euler(ull n);//返回欧拉函数
};
