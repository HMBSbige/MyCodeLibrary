/*
拓扑排序
类 TopologicalSort
复杂度：O(|V|+|E|)
变量：
	g[i]	 //表示从i点连出去的边
	n		 //表示点数
	L		 //拓扑排序的结果
成员函数：
	isSort() //排序并返回是否可以拓扑排序
	void readg(vector<int> *g) //读点的信息
*/
class TopologicalSort {
private:
	vector<int> *g, du;
	int n;
public:
	vector<int> L;
	TopologicalSort(int n) :du(n, 0), L(n, 0) {
		this->n = n;
	}
	void readg(vector<int> *g) {
		this->g = g;
	}
	bool isSort() {
		for (int i = 0; i<n; ++i)
			for (int j = 0; j<g[i].size(); j++)
				++du[g[i][j]];
		int tot = 0;
		queue <int> Q;
		for (int i = 0; i<n; ++i)
			if (!du[i])
				Q.push(i);
		while (!Q.empty()) {
			int x = Q.front();
			Q.pop();
			L[tot++] = x;
			for (int j = 0; j<g[x].size(); ++j) {
				int t = g[x][j];
				--du[t];
				if (!du[t])
					Q.push(t);
			}
		}
		if (tot == n)
			return 1;
		return 0;
	}
};
