const double pi = acos(-1.0);

class line {
public:
	point a, b;
	line(): a(0,0),b(0,0){}
	line(point _a, point _b) :a(_a), b(_b) {}
};
double dis_point_segment(const point p, const point s, const point t)//返回点p到线段st的距离
{
	if (cmp(dot(p - s, t - s))<0)
		return (p - s).norm();
	if (cmp(dot(p - t, s - t)<0))
		return (p - t).norm();
	return fabs(det(s - p, t - p) / dist(s, t));
}
point PointProjLine(const point p, const point s, const point t)//返回点p到线段st的垂足
{
	double r = dot(t - s, p - s) / dot(t - s, t - s);
	return s + r*(t - s);
}
bool PointOnSegment(point p, point s, point t)//点p是否在线段st上（包括端点）
{
	return cmp(det(p - s, t - s)) == 0 && cmp(dot(p - s, p - t)) <= 0;
}
bool isCoincident(line a, line b)//a,b是否重合
{
	double s1 = det(a.a - b.a, b.b - b.a);
	double s2 = det(a.b - b.a, b.b - b.a);
	if (cmp(s1 - s2) == 0 && cmp(s1) == 0)
		return true;
	return false;
}
bool isParallel(line a, line b)//a,b是否平行(不包括重合)
{
	//return !cmp(det(a.a-a.b,b.a-b.b));
	double s1 = det(a.a - b.a, b.b - b.a);
	double s2 = det(a.b - b.a, b.b - b.a);
	if (cmp(s1 - s2) == 0 && cmp(s1))
		return true;
	return false;
}
bool isIntersecting(line a, line b, point &res)//直线a,b是否相交,保存交点在res
{
	if (isParallel(a, b) || isCoincident(a, b))
		return false;
	double s1 = det(a.a - b.a, b.b - b.a);
	double s2 = det(a.b - b.a, b.b - b.a);
	res = (s1*a.b - s2*a.a) / (s1 - s2);
	return true;
}
bool cross(line a, line b, point &res)//线段a,b是否相交
{
	return isIntersecting(a, b, res) && PointOnSegment(res, a.a, a.b) && PointOnSegment(res, b.a, b.b);
}
line move_d(line a, const double &len)//将直线a沿法向量方向平移len得到的直线
{
	point d = a.b - a.a;
	d = d / d.norm();
	d = rotate_point(d, pi / 2);
	return line(a.a + d*len, a.b + d*len);
}
bool if3PointAreCollinear(const point &a, const point &b, const point &c)//三点共线
{
	return isCoincident(line(a, b), line(b, c));
}