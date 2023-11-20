#include <bits/stdc++.h>
#define MVNum 10000
using namespace std;

string Relationship[] = { "�й�Ч","��ʳ��","���Ƽ�ʳ��","��֤����Ҫ" };
typedef struct ArcNode{
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

typedef struct ALGraph{
	AdjList vertices;               // �ڽӱ�
	int vexnum, arcnum;             // ͼ�ĵ�ǰ�������ͱ���
} ALGraph;

int LocateVex(ALGraph& G, string str) {
	// ����str��AdjList�е�λ��
	for(int i = 0; i < G.vexnum; i++)
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
	for(int i = 0; i < MVNum; i++)
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
		int rpos = LocateVex(G,rightPart);
		if (lpos != -1)
		{
			ArcNode* p = new ArcNode;
			p->adjvex = rpos;
			p->relationship = LocateRelationship(middlePart);
			p->nextarc = G.vertices[lpos].firstarc;
			G.vertices[lpos].firstarc = p;
			G.arcnum++;
		}
		if(rpos != -1){
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


void PrintGraph(ALGraph& G) {
	for (int i = 0; i < G.vexnum; i++) {
		ArcNode* p = G.vertices[i].firstarc;
		if (p == NULL) {
			continue;
		}
		else {
			while (p) {
				cout << G.vertices[i].info << ' ';
				cout << p->relationship << " ";
				cout << G.vertices[p->adjvex].info << " ";
				cout << endl;
				p = p->nextarc;
			}
		}
	}
}

int main() {
	ALGraph G;
	InitALGraph(G);
	CreateAdjList(G, "entity.txt");
	CreateUDG(G, "relationship.txt");
	PrintGraph(G);
	return 0;
}