#include<iostream>
#include <queue>

#define MAXINT 32767 //极大值
#define MVNUM 10 //最大顶点数
struct Graph {
	int vexs[MVNUM]; //顶点表
	int mat[MVNUM][MVNUM]; //邻接矩阵
	int size{ 0 };
};

//构造函数
Graph* newGraph() {
	Graph* g = new Graph;
	for (int i = 0; i < MVNUM; ++i) {
		for (int j = 0; j < MVNUM; ++j) {
			g->mat[i][j] = 0;
		}
	}
	return g;
}

//析构函数
void delGraph(Graph* g) {
	free(g);
}

//添加顶点
void addVertex(Graph* g, int val) {
	if (g->size == MVNUM) {
		std::cout << "图的顶点数量已达最大值" << std::endl;
		return;
	}
	int n = g->size;
	g->vexs[n] = val;
	for (int i = 0; i <= n; ++i) {
		g->mat[n][i] = g->mat[i][n] = 0;
	}
	g->size++;
}

//删除顶点
void removeVertex(Graph* g, int index) {
	if (index < 0 || index >= g->size) {
		std::cout << "顶点索引越界" << std::endl;
		return;
	}
	for (int i = index; i < g->size - 1; ++i) {
		g->vexs[i] = g->vexs[i + 1];
	}
	for (int i = index; i < g->size - 1; ++i) {
		for (int j = 0; j < g->size; ++j) {
			g->mat[i][j] = g->mat[i + 1][j];
		}
	}
	for (int i = 0; i < g->size; ++i) {
		for (int j = index; j < g->size - 1; ++j) {
			g->mat[i][j] = g->mat[i][j + 1];
		}
	}
	g->size--;
}

//添加边
void addEdge(Graph* g, int i, int j) {
	if (i < 0 || j < 0 || i >= g->size || j >= g->size || i == j) {
		std::cout << "边索引越界或相等" << std::endl;
		return;
	}
	g->mat[i][j] = g->mat[j][i] = 1;
}

//删除边
void removeEdge(Graph* g, int i, int j) {
	if (i < 0 || j < 0 || i >= g->size || j >= g->size || i == j) {
		std::cout << "边索引越界或相等" << std::endl;
		return;
	}
	g->mat[i][j] = g->mat[j][i] = 0;
}

void printArray(int* nums, int n) {
	for (int i = 0; i < n; ++i) {
		std::cout << nums[i] << " ";
	}
	std::cout << std::endl;
}

//打印邻接矩阵
void printGraph(Graph* g) {
	std::cout << "~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "顶点列表 = ";
	printArray(g->vexs, g->size);
	std::cout << "邻接矩阵如下：" << std::endl;
	for (int i = 0; i < g->size; ++i) {
		printArray(g->mat[i], g->size);
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

//深度优先搜索
void dfs(Graph* g, bool* visited, int i) {
	for (int j = 0; j < g->size; ++j) {
		if (!visited[j] && g->mat[i][j] == 1) {
			visited[j] = true;
			dfs(g, visited, j);
		}
	}
}

//广度优先搜索
void bfs(Graph* g, bool* visited, int i) {
	std::queue<int> que;
	que.push(i);
	visited[i] = true;
	while (!que.empty()) {
		int cur = que.front();
		que.pop();
		for (int j = 0; j < g->size; ++j) {
			if (g->mat[cur][j] == 1 && !visited[j]) {
				que.push(j);
				visited[j] = true;
			}
		}
	}
}

//统计连通分量的个数
int countConnected(Graph* g) {
	int ans = 0;
	bool* visited = new bool[g->size];
	for (int i = 0; i < g->size; ++i) {
		visited[i] = false;
	}
	for (int i = 0; i < g->size; ++i) {
		if (!visited[i]) {
			bfs(g, visited, i);
			ans++;
		}
	}
	delete visited;
	visited = nullptr;
	return ans;
}

int main() {
	Graph* g = newGraph();
	addVertex(g, 0);
	addVertex(g, 1);
	addVertex(g, 2);
	addVertex(g, 3);
	addVertex(g, 4);
	addVertex(g, 5);
	addVertex(g, 6);

	addEdge(g, 0, 1);
	addEdge(g, 1, 2);
	addEdge(g, 2, 3);
	addEdge(g, 5, 6);
	addEdge(g, 1, 3);
	addEdge(g, 1, 3);
	//addEdge(g, 2, 4);
	//addEdge(g, 3, 5);
	printGraph(g);

	std::cout << "使用广度优先搜索方式，此时共有" << countConnected(g) << "个连通分量" << std::endl;

	removeVertex(g, 2);
	printGraph(g);

	removeEdge(g, 0, 1);
	printGraph(g);
	return 0;
}

//Graph* newGraph()
//void delGraph(Graph* g)
//void addVertex(Graph* g, int val)
//void removeVertex(Graph* g, int index)
//void addEdge(Graph* g, int i, int j)
//void removeEdge(Graph* g, int i, int j)
//void printGpaph(Graph* g)