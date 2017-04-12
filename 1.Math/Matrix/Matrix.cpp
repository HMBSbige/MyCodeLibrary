class Matrix{
typedef long double ll;
private:
public:
    std::vector<std::vector<ll> > a;
    Matrix(){};
    Matrix(const Matrix&);
    Matrix(ll,ll);
    void clear();
    void reset(ll);
    void print(std::ostream& os);
    Matrix operator +(const Matrix &b) const;
    Matrix operator -(const Matrix &b) const;
    Matrix operator *(const Matrix &b) const;
};
Matrix::Matrix(ll m,ll n):a(m,std::vector<ll>(n,0)){}
Matrix::Matrix(const Matrix& b){
    a=b.a;
}
void Matrix::clear(){
    std::vector<std::vector<ll> >().swap(a);
}
void Matrix::reset(ll n=0){
    register size_t i,j;
    for(i=0;i<a.size();++i)
        for(j=0;j<a[i].size();++j)
            a[i][j]=n;
}
void Matrix::print(std::ostream& os){
    register size_t i,j;
    for(i=0;i<a.size();++i){
        for(j=0;j<a[i].size();++j){
            if(j) os<<" ";
            os<<std::setw(5)<<std::setprecision(2)<<std::fixed<<a[i][j];
        }
        os<<std::endl;
    }
}
Matrix Matrix::operator +(const Matrix &b) const{
    register size_t i,j;
    Matrix ans(*this);
    for(i=0;i<this->a.size();++i)
        for(j=0;j<this->a[i].size();++j)
            ans.a[i][j]=ans.a[i][j]+b.a[i][j];
    return ans;
}
Matrix Matrix::operator -(const Matrix &b) const{
    register size_t i,j;
    Matrix ans(*this);
    for(i=0;i<this->a.size();++i)
        for(j=0;j<this->a[i].size();++j)
            ans.a[i][j]=ans.a[i][j]-b.a[i][j];
    return ans;
}
Matrix Matrix::operator *(const Matrix &b) const{
    register size_t i,j,k;
    Matrix ans(this->a.size(),b.a[0].size());
    for(i=0;i<this->a.size();++i)
        for(j=0;j<b.a[0].size();++j)
            for(k=0;k<this->a[i].size();++k)
                ans.a[i][j]=ans.a[i][j]+a[i][k]*b.a[k][j];
    return ans;
}