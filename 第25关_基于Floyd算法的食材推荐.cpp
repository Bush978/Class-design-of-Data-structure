#include <bits/stdc++.h>
#define MVNum 10000
using namespace std;
#define INF 65535
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

typedef struct {
    int vexs[100];                  // 顶点表
    double arcs[100][100];          // 邻接矩阵
    int vexnum, arcnum;             // 图的当前顶点数和边数
} AMGraph;

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

void InitAMGraph(AMGraph& G) {
    // 初始化邻接矩阵
    G.vexnum = 0;
    G.arcnum = 0;
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            G.arcs[i][j] = INF;


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

int LevenshteinDistance(string s1, string s2) {
    // 定义一个函数，计算两个字符串的莱文斯坦距离
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
            }
        }
    }
    return dp[m][n];
}

double TextSimilarity(string s1, string s2) {
    // 定义一个函数，计算两个字符串的文本相似度，文本相似度 = 1 - 莱文斯坦距离 / 最大字符串长度
    int dist = LevenshteinDistance(s1, s2);
    int max_len = max(s1.length(), s2.length());
    double s = 1.0 - (double)dist / max_len;
    return s;
}

void CreateAMG(AMGraph& GM, ALGraph& G) {
    // 调用编辑距离算法计算相似度，构建食材之间的邻接矩阵
    GM.vexnum = 100;
    GM.arcnum = 0;
    for (int i = 0; i < 100; i++) 
        GM.vexs[i] = i;

    for (int i = 0; i < 100; i++) {
        string foodstring;
        ArcNode* p = G.vertices[i].firstarc;
        while (p != NULL) {
            if (p->relationship == 0)
            {
                foodstring += G.vertices[p->adjvex].info;
                if (p->relationship == 0 && p->nextarc != NULL)
                    foodstring += "#";
            }
            p = p->nextarc;
        }
        for (int j = 0; j < 100; j++) {
            string  foodstring1;
            ArcNode* p = G.vertices[j].firstarc;
            while (p != NULL) {
                if (p->relationship == 0)
                {
                    foodstring1 += G.vertices[p->adjvex].info;
                    if (p->relationship == 0 && p->nextarc != NULL)
                        foodstring1 += "#";
                }
                p = p->nextarc;
            }
            GM.arcs[i][j] = 1 - TextSimilarity(foodstring, foodstring1);
        }
    }
}


void ShortestPathFloyd(AMGraph& G, double D[][100]) {
    // 使用弗洛伊德算法求最短路径，D表示最短路径长度

    for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++)
            if(i == j)
                D[i][j] = 0;
			else
			    D[i][j] = G.arcs[i][j];
	}
    for (int k = 0; k < 100; k++) {
        for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++)
				if (D[i][j] > D[i][k] + D[k][j])
					D[i][j] = D[i][k] + D[k][j];
		}
	}

}

int main() {
    ALGraph G;
    InitALGraph(G);
    CreateAdjList(G, "entity.txt");
    CreateUDG(G, "relationship.txt");
    AMGraph GM;
    InitAMGraph(GM);
    CreateAMG(GM, G);
    double T;
    string food;
    cin >> food >> T;
    int v0 = LocateVex(G, food);
    double M[100][100];
    ShortestPathFloyd(GM, M);
    for (int i = 0; i < 100; i++) {
        if (M[v0][i] <= T) {
            cout << G.vertices[GM.vexs[i]].info << ' ';
        }
    }
    return 0;
}