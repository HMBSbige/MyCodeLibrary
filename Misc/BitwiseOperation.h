#pragma once
#include <iostream> 
using namespace std;
typedef int64_t ull;
typedef long double lb;

void bitswap(ull* a, ull* b)//不用中间变量，交换两整形变量
{
	*a = *a^*b;
	*b = *b^*a; //b = b^(a^b),thus b becomes the earlier a
	*a = *a^*b; //a = (a^b)^a,thus a becomes the earlier b
}
void Myswap(lb* a, lb* b)//不用中间变量，交换两数
{
	*a = *a - *b; // 有可能溢出
	*b = *a + *b; // b = (a - b)+ b, thus b becomes the earlier a
	*a = *b - *a; // a = a - (a - b),  thus a becomes the earlier b
}
ull bitaverage(ull x,ull y)
{
	return ((x&y) + ((x^y) >> 1));
}