#include <iostream>
#include <ctime>
#include <random>
using namespace std;
class RandomNum {
private:
	random_device rd;
public:
	RandomNum() {};
	int getNum(int a, int b) {
		if (a > b)
			swap(a, b);
		mt19937 gen(rd());
		uniform_int_distribution<> dis(a, b);
		return dis(gen);
	}
};
class Timer {
private:
	clock_t s, f;
public:
	Timer() {};
	void start() {s = clock();}
	void finish() {f = clock();}
	double totaltime() {return (double)(f - s) / CLOCKS_PER_SEC;}
};
int main()
{
	Timer t;
	t.start();

	RandomNum r;
	for (int n = 0; n<100; ++n)
		std::cout << r.getNum(10,0) << ' ';
	std::cout << '\n';

	t.finish();
	cout << "\n此程序的运行时间为" << t.totaltime() << "秒！" << endl;

	system("pause");
	return 0;
}