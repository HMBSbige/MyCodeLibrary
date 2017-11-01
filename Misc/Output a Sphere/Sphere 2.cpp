#include <iostream> 
#include <cmath>
#include <windows.h>
#define PI acos(-1)
#define SX 16
#define SY 32 
#define DX PI / SX 
#define DY PI * 2 / SY 
#define X(a, b) static_cast<int>(cx + v[a][b].x * r), static_cast<int>(cy + v[a][b].y * r) 
typedef struct { double x, y; } Vec;
void calc(double i, double j, double rot, Vec* v) {
	auto
		x = sin(i) * cos(j),
		y = sin(i) * sin(j),
		z = cos(i),
		s = sin(rot),
		c = cos(rot),
		c1 = 1 - c,
		u = 1 / sqrt(3),
		u2 = u * u;
	v->x = x * (c + u2 * c1) + y * (u2 * c1 - u * s) + z * (u2 * c1 + u * s);
	v->y = x * (u2 * c1 + u * s) + y * (c + u2 * c1) + z * (u2 * c1 - u * s);
}
int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
	auto hwnd = GetConsoleWindow();
	auto hdc1 = GetDC(hwnd);
	double rot = 0;
	register size_t i, j;
	while (true) {
		RECT rect;
		GetClientRect(hwnd, &rect);
		int w = rect.right, 
		h = rect.bottom, 
		cx = w / 2, 
		cy = h / 2, 
		r = static_cast<int>(h * 0.375);
		auto hdc2 = CreateCompatibleDC(hdc1);
		auto bmp = CreateCompatibleBitmap(hdc1, w, h);
		SelectObject(hdc2, bmp);
		SelectObject(hdc2, GetStockObject(6));//6=WHITE_PEN
		Vec v[SX + 1][SY + 1];
		for (i = 0; i <= SX; ++i)
			for (j = 0; j <= SY; ++j)
				calc(i * DX, j * DY, rot, &v[i][j]);
		for (i = 0; i < SX; ++i)
			for (j = 0; j < SY; ++j) {
				MoveToEx(hdc2, X(i, j),nullptr);
				LineTo(hdc2, X(i + 1, j));
				MoveToEx(hdc2, X(i, j), nullptr);
				LineTo(hdc2, X(i, j + 1));
			}
		BitBlt(hdc1, 0, 0, w, h, hdc2, 0, 0, static_cast<DWORD>(0x00CC0020));//0x00CC0020=SRCCOPY
		DeleteObject(bmp); 
		DeleteDC(hdc2);
		rot += 0.01;
		Sleep(5);
	}
	return 0;
}