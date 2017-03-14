#pragma once
#include <vector>
#include <set>
#include <new>
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
	void MakePrime(ull);
	ull Number();
	ull at(ull);
	bool isPrimeNumer(ull);
	ull find(ull);
	vector<pair<ull, ull> >factor(ull n);
};
