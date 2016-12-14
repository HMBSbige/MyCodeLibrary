# [并查集](https://zh.wikipedia.org/wiki/%E5%B9%B6%E6%9F%A5%E9%9B%86)

##任务

维护一些不相交的集合，支持两种操作：合并两个集合，查询一个元素所处的集合。

## 接口

并查集

结构体：DisjoinSet

成员变量：

    vector<int> father //元素的父亲节点，树根元素的父亲为自身
    
    vector<int> rank   //树根元素所代表集合的rank
    
    _max               //最大集合的元素个数
    
成员函数：

    DisjoinSet(int n);       //初始化，n个元素，处于单独集合
    
    复杂度：O(n)
    
    int find(int v);         //查找v所在集合的代表元
    
    复杂度：均摊O(1)
    
    void merge(int x,int y); //合并x所在的集合与y所在集合
    
    复杂度：均摊O(1)
