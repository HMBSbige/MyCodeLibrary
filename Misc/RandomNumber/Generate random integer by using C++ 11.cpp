class RandomINT{
private:
    /*maybe wrong in g++
    std::random_device rd;
    std::mt19937 gen(rd());
    */
    std::mt19937 gen;
public:
    RandomINT():gen((unsigned)time(nullptr)){};
    template<class T=long long>
    T GetRandomInteger(T a, T b) {///return random integer in [a,b]
        if(a>b)
            swap(a,b);
        std::uniform_int_distribution<T> dis(a, b);
        return dis(gen);
    }
};