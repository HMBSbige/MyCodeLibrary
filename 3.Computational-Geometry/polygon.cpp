class polygon {
public:
	size_t n;
	vector<point> a;//多边形的点，顺时针顺序
	polygon(size_t _n);
	double perimeter();//返回多边形的周长
	double area();//返回多边形的面积
	int isPointIn(point t);//判断点t是否在多边形的内部，0在多边形外，1在多边形内，2在多边形上
	point MassCenter();//返回多边形的重心坐标
};
polygon::polygon(size_t _n) :n(_n) {
	vector<point>(n).swap(a);
}
double polygon::perimeter() {
	double sum = 0;
	for (size_t i = 0; i<n - 1; ++i)
		sum += (a[i + 1] - a[i]).norm();
	sum += (a[0] - a[n - 1]).norm();
	return sum;
}
double polygon::area() {
	double sum = 0;
	for (size_t i = 0; i<n - 1; ++i)
		sum += det(a[i + 1], a[i]);
	sum += det(a[0], a[n - 1]);
	return sum / 2.0;
}
int polygon::isPointIn(point t) {
	int num = 0, d1, d2, k;
	for (size_t i = 0; i<n - 1; ++i) {
		if (PointOnSegment(t, a[i], a[i + 1]))
			return 2;
		k = cmp(det(a[i + 1] - a[i], t - a[i]));
		d1 = cmp(a[i].y - t.y);
		d2 = cmp(a[i + 1].y - t.y);
		if (k>0 && d1 <= 0 && d2>0)
			++num;
		if (k<0 && d2 <= 0 && d1>0)
			--num;
	}
	if (PointOnSegment(t, a[n - 1], a[0]))
		return 2;
	k = cmp(det(a[0] - a[n - 1], t - a[n - 1]));
	d1 = cmp(a[n - 1].y - t.y);
	d2 = cmp(a[0].y - t.y);
	if (k>0 && d1 <= 0 && d2>0)
		++num;
	if (k<0 && d2 <= 0 && d1>0)
		--num;
	return num != 0;
}
point polygon::MassCenter()
{
	point ans;
	if (cmp(area()) == 0)//面积为0时无定义
		return ans;
	for (size_t i = 0; i < n - 1; ++i)
		ans = ans + (a[i] + a[i + 1])*det(a[i + 1], a[i]);
	ans = ans + (a[n-1] + a[0])*det(a[0], a[n-1]);
	return ans / area() / 6;
}