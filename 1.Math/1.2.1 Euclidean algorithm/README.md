# [欧几里德算法](https://zh.wikipedia.org/zh-hans/輾轉相除法)
## 任务
求两个数a,b的最大公约数gcd(a,b)。
## 说明
由[贝祖定理](https://zh.wikipedia.org/wiki/貝祖等式)得，gcd(a,b)=gcd(b,a-b)，其中a≥b。通过这样不断的迭代，直到b=0，a就是原来数对的最大公约数。考虑到只使用减法会超时，我们观察到如果a-b仍然大于b的话，要进行一次同样的操作，就把a减到不足b为止，所以有gcd(a,b)=gcd(b,a mod b)。由此可以在log的时间内求出两个数的gcd。
## 接口
int gcd(int a,int b);

复杂度：O(logN)，其中N和a,b同阶

输入：a,b 两个整数

输出：a,b的最大公约数
