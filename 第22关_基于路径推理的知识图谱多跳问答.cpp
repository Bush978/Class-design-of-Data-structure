#include <bits/stdc++.h>
#define MVNum 10000
using namespace std;

string Relationship[] = { "�й�Ч","��ʳ��","���Ƽ�ʳ��","��֤����Ҫ" };
typedef struct ArcNode {
	int adjvex;                     // �ñ���ָ�򶥵��λ��
	int relationship;               // ��ʾ�ߵ����ͣ�����ϵ�����ͣ���ӦΪ�����±� 
	struct ArcNode* nextarc;        // ��һ����
} ArcNode;                          // �߽��

string Entity[] = { "ʳ��","����","��Ч","ʳ��","֤����Ҫ" };
typedef struct VNode {
	int entity;                     // ��ʾ��������ͣ���ʵ������ͣ���ӦΪ�����±�
	string info;                    // ��ʾ��������ݣ���ʵ�������
	ArcNode* firstarc;              // ָ���һ�������ö���ıߵ�ָ��
} VNode, AdjList[MVNum];

typedef struct ALGraph {
	AdjList vertices;               // �ڽӱ�
	int vexnum, arcnum;             // ͼ�ĵ�ǰ�������ͱ���
} ALGraph;

int LocateVex(ALGraph& G, string str) {
	// ����str��AdjList�е�λ��
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].info == str) return i;
	return -1;
}

int LocateEntity(string str) {
	// ����str��Entity�����е�λ��
	int i = 0;
	while (i < 5)
	{
		if (Entity[i] == str) return i;
		i++;
	}
	return -1;
}

int LocateRelationship(string str) {
	// ����str��Relationship�����е�λ��
	int i = 0;
	while (i < 4)
	{
		if (Relationship[i] == str) return i;
		i++;
	}
	return -1;
}

void InitALGraph(ALGraph& G) {
	// ��ʼ���ڽӱ�
	G.vexnum = 0;
	G.arcnum = 0;
	for (int i = 0; i < MVNum; i++)
		G.vertices[i].firstarc = NULL;
}

void CreateAdjList(ALGraph& G, string inputFile) {
	// ��filename�а�˳���ȡʵ������ڽӱ�
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
	// ��filename�а�˳����Ԫ������ڽӱ�
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
//string Entity[] = { "ʳ��","����","��Ч","ʳ��","֤����Ҫ" };
void DFS(ALGraph& G, int i, bool visited[], string path) {
	// ����������������ʴ�·����iΪ�����֤����Ҫ��AdjList�е��±꣬pathΪ�ʴ�·��
	// ���������Ӷ���Ĳ���
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
	// ����DFS����������ͼG������ʴ����У�symptomΪ֤����Ҫ
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