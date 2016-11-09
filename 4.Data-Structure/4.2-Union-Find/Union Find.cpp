/*
并查集
结构体：DisjoinSet
成员变量：
    vector<int> father //元素的父亲节点，树根元素的父亲为自身
    vector<int> rank   //树根元素所代表集合的rank
成员函数：
    DisjoinSet(int n);       //初始化，n个元素，处于单独集合
    复杂度：O(n)
    int find(int v);         //查找v所在集合的代表元
    复杂度：均摊O(1)
    void merge(int x,int y); //合并x所在的集合与y所在集合
    复杂度：均摊O(1)
*/
struct DisjoinSet{
    std::vector<int> father,rank;

    DisjoinSet(int n):father(n),rank(n){
        for(int i=0;i<n;++i)
            father[i]=i;
    }
    int find(int v){
        return father[v]=father[v]==v?v:find(father[v]);
    }

    void merge(int x,int y){
        int a=find(x),b=find(y);
        if(rank[a]<rank[b])
            father[a]=b;
        else{
            father[b]=a;
            if(rank[b]==rank[a])
                ++rank[a];
        }
    }
};