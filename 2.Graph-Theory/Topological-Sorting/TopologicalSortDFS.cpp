/*
拓扑排序
类 TopologicalSortDFS
变量：
N           //点的个数
map         //记录偏序关系
degree      //度
EXIT		    //还没输出的点
sss         //当前排列
ans         //记录所有排列
成员函数：
init()      //初始化
readmap(a,b)//a<b
readdu(a,b) //b的度+1
DFS()       //执行DFS
*/
class TopologicalSortDFS {
private:
	size_t N;
	vector<int> *map=NULL;
	vector<int> degree, EXIT, sss;
public:
	vector< vector<int> > ans;
	TopologicalSortDFS(){}
	TopologicalSortDFS(size_t n) {init(n);}
	void init(size_t n) {
		this->N = n;
		ans.clear();
		if(map!=NULL)
			delete[] map;
		degree.resize(n);
		EXIT.resize(n);
		sss.resize(n);
		map = new vector<int>[n];
		for (int i = 0; i<n; ++i) {
			map[i].resize(n);
			degree[i] = 0;
			EXIT[i] = 1;
			for (int j = 0; j<n; ++j)
				map[i][j] = 0;
		}
	}
	~TopologicalSortDFS() {
		delete[] map;
	}
	void readmap(size_t a, size_t b) {
		map[a][b] = 1;
	}
	void readdu(size_t a) {
		degree[a]++;
	}
	void DFS(int step) {
		int i, j;
		if (step == N) {
			ans.push_back(sss);
			return;
		}
		for (i = 0; i<N; i++) {
			if (EXIT[i] && degree[i] == 0) {
				EXIT[i] = 0;
				sss[step] = i;
				for (j = 0; j<N; j++) {
					if (map[i][j])
						degree[j]--;
				}
				DFS(step + 1);
				for (j = 0; j<N; j++) {
					if (map[i][j])
						degree[j]++;
				}
				EXIT[i] = 1;
			}
		}
	}
};
