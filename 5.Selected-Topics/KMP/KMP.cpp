/*
复杂度：O(N+M)
输入：pattern 模式串
      text    文本串
输出：所有匹配点的下标
*/
template <class T> vector <int> find_substring(T pattern,T text){
    int n=pattern.size();
    vector <int> next(n+1,0);
    for(int i=1;i<n;++i){
        int j=i;
        while (j>0){
            j=next[j];
            if(pattern[j]==pattern[i]){
                next[i+1]=j+1;
                break;
            }
        }
    }
    vector <int> positions;
    int m=text.size();
    for(int i=0,j=0;i<m;++i){
        if(j<n && text[i]==pattern[j]){
            ++j;
        }else{
            while(j>0){
                j=next[j];
                if(text[i]==pattern[j]){
                    ++j;
                    break;
                }
            }
        }
        if(j==n){
            positions.push_back(i-n+1);
        }
    }
    return positions;
}
