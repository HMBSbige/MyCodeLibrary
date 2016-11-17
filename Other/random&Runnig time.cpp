#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int random(int start, int end);
int main() {
	clock_t start, finish;
	double totaltime;
	start = clock();


	srand(unsigned(time(0)));
	for (int icnt = 0; icnt != 10; ++icnt)
		cout << "No." << icnt + 1 << ": " << int(random(0, 10)) << endl;

	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n此程序的运行时间为" << totaltime << "秒！" << endl;

	system("pause");
	return 0;
}

int random(int start, int end) {
	return start + (int)rand() % (end - start + 1);
}
