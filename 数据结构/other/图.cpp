#include<iostream>
#include <queue>

#define MAXINT 32767 //����ֵ
#define MVNUM 10 //��󶥵���
struct Graph {
	int vexs[MVNUM]; //�����
	int mat[MVNUM][MVNUM]; //�ڽӾ���
	int size{ 0 };
};

//���캯��
Graph* newGraph() {
	Graph* g = new Graph;
	for (int i = 0; i < MVNUM; ++i) {
		for (int j = 0; j < MVNUM; ++j) {
			g->mat[i][j] = 0;
		}
	}
	return g;
}

//��������
void delGraph(Graph* g) {
	free(g);
}

//��Ӷ���
void addVertex(Graph* g, int val) {
	if (g->size == MVNUM) {
		std::cout << "ͼ�Ķ��������Ѵ����ֵ" << std::endl;
		return;
	}
	int n = g->size;
	g->vexs[n] = val;
	for (int i = 0; i <= n; ++i) {
		g->mat[n][i] = g->mat[i][n] = 0;
	}
	g->size++;
}

//ɾ������
void removeVertex(Graph* g, int index) {
	if (index < 0 || index >= g->size) {
		std::cout << "��������Խ��" << std::endl;
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

//��ӱ�
void addEdge(Graph* g, int i, int j) {
	if (i < 0 || j < 0 || i >= g->size || j >= g->size || i == j) {
		std::cout << "������Խ������" << std::endl;
		return;
	}
	g->mat[i][j] = g->mat[j][i] = 1;
}

//ɾ����
void removeEdge(Graph* g, int i, int j) {
	if (i < 0 || j < 0 || i >= g->size || j >= g->size || i == j) {
		std::cout << "������Խ������" << std::endl;
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

//��ӡ�ڽӾ���
void printGraph(Graph* g) {
	std::cout << "~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "�����б� = ";
	printArray(g->vexs, g->size);
	std::cout << "�ڽӾ������£�" << std::endl;
	for (int i = 0; i < g->size; ++i) {
		printArray(g->mat[i], g->size);
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

//�����������
void dfs(Graph* g, bool* visited, int i) {
	for (int j = 0; j < g->size; ++j) {
		if (!visited[j] && g->mat[i][j] == 1) {
			visited[j] = true;
			dfs(g, visited, j);
		}
	}
}

//�����������
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

//ͳ����ͨ�����ĸ���
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

	std::cout << "ʹ�ù������������ʽ����ʱ����" << countConnected(g) << "����ͨ����" << std::endl;

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