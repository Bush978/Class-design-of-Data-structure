#include <bits/stdc++.h>
#define MVNum 10000
using namespace std;

string Relationship[] = { "有功效","有食谱","有推荐食材","有证机概要" };
typedef struct ArcNode {
	int adjvex;                     // 该边所指向顶点的位置
	int relationship;               // 表示边的类型，即关系的类型，对应为数组下标 
	struct ArcNode* nextarc;        // 下一条边
} ArcNode;                          // 边结点

string Entity[] = { "食材","疾病","功效","食谱","证机概要" };
typedef struct VNode {
	int entity;                     // 表示顶点的类型，即实体的类型，对应为数组下标
	string info;                    // 表示顶点的内容，即实体的内容
	ArcNode* firstarc;              // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum];

typedef struct ALGraph {
	AdjList vertices;               // 邻接表
	int vexnum, arcnum;             // 图的当前顶点数和边数
} ALGraph;

int LocateVex(ALGraph& G, string str) {
	// 返回str在AdjList中的位置
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].info == str) return i;
	return -1;
}

int LocateEntity(string str) {
	// 返回str在Entity数组中的位置
	int i = 0;
	while (i < 5)
	{
		if (Entity[i] == str) return i;
		i++;
	}
	return -1;
}

int LocateRelationship(string str) {
	// 返回str在Relationship数组中的位置
	int i = 0;
	while (i < 4)
	{
		if (Relationship[i] == str) return i;
		i++;
	}
	return -1;
}

void InitALGraph(ALGraph& G) {
	// 初始化邻接表
	G.vexnum = 0;
	G.arcnum = 0;
	for (int i = 0; i < MVNum; i++)
		G.vertices[i].firstarc = NULL;
}

void CreateAdjList(ALGraph& G, string inputFile) {
	// 从filename中按顺序读取实体存入邻接表
	ifstream fin(inputFile);
	string line;
	while (getline(fin, line)) {
		istringstream iss(line);
		string leftPart, rightPart;
		iss >> leftPart >> rightPart;
		int i = LocateEntity(rightPart);
		string temp = leftPart;
		G.vertices[G.vexnum].entity = i;
		G.vertices[G.vexnum].info = temp;
		G.vertices[G.vexnum].firstarc = NULL;
		G.vexnum++;
	}
}

void CreateUDG(ALGraph& G, string filename) {
	// 从filename中按顺序三元组存入邻接表
	ifstream fin(filename);
	string line;
	while (getline(fin, line)) {
		istringstream iss(line);
		string leftPart, middlePart, rightPart;
		iss >> leftPart >> middlePart >> rightPart;
		int lpos = LocateVex(G, leftPart);
		int rpos = LocateVex(G, rightPart);
		if (lpos != -1)
		{
			ArcNode* p = new ArcNode;
			p->adjvex = rpos;
			p->relationship = LocateRelationship(middlePart);
			p->nextarc = G.vertices[lpos].firstarc;
			G.vertices[lpos].firstarc = p;
			G.arcnum++;
		}
		if (rpos != -1) {
			ArcNode* p = new ArcNode;
			//cout << rightPart << endl;
			p->adjvex = lpos;
			p->relationship = LocateRelationship(middlePart);
			p->nextarc = G.vertices[rpos].firstarc;
			G.vertices[rpos].firstarc = p;
			G.arcnum++;
		}
	}

}

void AuxDFS(ALGraph& G, int i, bool visited[], string path) {
	ArcNode* p = G.vertices[i].firstarc;
	while (p != NULL) {
		if (G.vertices[p->adjvex].entity == 3) {
			AuxDFS(G, p->adjvex, visited, path + "->" + G.vertices[p->adjvex].info);
			cout << path << "->" << G.vertices[p->adjvex].info << endl;
		}
		p = p->nextarc;
	}
}
//string Entity[] = { "食材","疾病","功效","食谱","证机概要" };
void DFS(ALGraph& G, int i, bool visited[], string path) {
	// 深度优先搜索多跳问答路径，i为输入的证机概要在AdjList中的下标，path为问答路径
	// 函数可增加额外的参数
	ArcNode* p = G.vertices[i].firstarc;
    visited[i] = true;
	while (p != NULL) {
		if (!visited[p->adjvex]) {
			if (G.vertices[p->adjvex].entity == 0) {
				ArcNode* p1 = G.vertices[p->adjvex].firstarc;
				int flag1 = 0;
				while (p1 != NULL) {
					if (!visited[p1->adjvex]) {
						if (G.vertices[p1->adjvex].entity == 3) {
							AuxDFS(G, p->adjvex, visited, path + "->" + G.vertices[p->adjvex].info);
							flag1 = 1;
							break;
						}
					}
					p1 = p1->nextarc;
				}
				p1 = G.vertices[p->adjvex].firstarc;
				if(flag1 == 0)
				cout << path << "->" << G.vertices[p->adjvex].info << endl;
			}
			else if (G.vertices[p->adjvex].entity == 1) 
					DFS(G, p->adjvex, visited, path + "->" + G.vertices[p->adjvex].info);
			else if (G.vertices[p->adjvex].entity == 2) 
					DFS(G, p->adjvex, visited, path + "->" + G.vertices[p->adjvex].info);
			else if (G.vertices[p->adjvex].entity == 3) 
					DFS(G, p->adjvex, visited, path + "->" + G.vertices[p->adjvex].info);
		}
		p = p->nextarc;
	}

}

void QuestionAnswering(ALGraph& G, string symptom) {
	// 调用DFS函数，遍历图G，输出问答序列，symptom为证机概要
	bool visited[MVNum];
	for (int i = 0; i < G.vexnum; i++)
		visited[i] = false;
	int i = LocateVex(G, symptom);
	DFS(G, i, visited, symptom);
}

int main() {
	ALGraph G;
	InitALGraph(G);
	CreateAdjList(G, "entity.txt");
	CreateUDG(G, "relationship.txt");
	string symptom;
	cin >> symptom;
	QuestionAnswering(G, symptom);
	return 0;
}