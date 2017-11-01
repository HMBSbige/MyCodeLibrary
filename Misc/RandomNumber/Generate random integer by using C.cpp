class CRandomINT{
public:
    CRandomINT(){srand((unsigned)time(nullptr));}
    template<class T=long long>
    T GetRandomInteger(T a, T b) {///return random integer in [a,b]
        if(a>b)
            swap(a,b);
        return (rand()<<15|rand())%(b-a+1)+a;
    }
};