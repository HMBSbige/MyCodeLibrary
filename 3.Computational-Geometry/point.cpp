const double pi=acos(-1.0);
class point{
public:
    double x,y;
    point(double,double);
    void input(std::istream& is);
    void input(double,double);
    point operator +(const point &b) const;
    point operator -(const point &b) const;
    bool operator ==(const point &b) const;
    friend point operator *(const double &a,const point &b);
    friend point operator *(const point &a,const double &b);
    friend point operator /(const point &a,const double &b);
    double norm();//向量的模
    friend double det(const point &a,const point &b);//叉积
    friend double dot(const point &a,const point &b);//点积
    friend double dist(const point &a,const point &b);//两点间距离
    friend point rotate_point(const point &p,double A);// 向量op绕原点逆时针旋转A弧度
};
point::point(double a=0.0,double b=0.0):x(a),y(b){}
void point::input(std::istream& is){
    is>>x>>y;
}
void point::input(double a,double b){
    x=a;y=b;
}
point point::operator +(const point &b) const{
    return point(this->x+b.x,this->y+b.y);
}
point point::operator -(const point &b) const{
    return point(this->x-b.x,this->y-b.y);
}
bool point::operator ==(const point &b) const{
    return cmp(this->x-b.x)==0 && cmp(this->y-b.y)==0;
}
point operator *(const double &a,const point &b){
    return point(a*b.x,a*b.y);
}
point operator *(const point &a,const double &b){
    return point(b*a.x,b*a.y);
}
point operator /(const point &a,const double &b){
    return point(a.x/b,a.y/b);
}
double point::norm(){
    return sqrt(x*x+y*y);
}
double det(const point &a,const point &b)
{
    return a.x*b.y-a.y*b.x;
}
double dot(const point &a,const point &b)
{
    return a.x*b.x+a.y*b.y;
}
double dist(const point &a,const point &b)
{
    return (a-b).norm();
}
point rotate_point(const point &p,double A){
    return point(p.x*cos(A)-p.y*sin(A),p.x*sin(A)+p.y*cos(A));
}