#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
string allfilename;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
int len = sizeof("英文名称：") / sizeof(char);
typedef struct Food {
	char name[100];		        // 中文名称
	char sname[100];	        // 英文名称
	char health[10000];	        // 养生功效
	char nutrition[10000];      // 营养与功效
	char expert[10000];	        // 专家提醒
	char link[10000];	        // 相关链接
	string recipe[30];	        // 养生保健食谱
	int recipe_size = 0;        // 食谱数量
	string therapy[30];	        // 食疗验方
	int therapy_size = 0;       // 验方数量
} Food;
typedef struct {
	Food* elem;                 // 指向数组的指针
	int length;                 // 数组的长度
} SqList;
typedef struct TNode {
	// 定义字典树结构体
	Food* foodPtr;		        // 食材指针
	struct TNode* child[53];    // 子结点的指针数组，由26个小写字母，26个大写字母，1个空格组成
} TNode, * TrieTree;
TNode* root1 = NULL;

void InitList(SqList& L) {
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void FreeList(SqList& L) {
	// 释放内存
	delete[] L.elem;
	L.length = 0;
}

void ReadFood(Food& f, ifstream& infile) {
	infile.getline(f.name, 100);
	infile.getline(f.sname, 100);
	infile.getline(f.health, 10000);
	infile.getline(f.nutrition, 10000);
	infile.getline(f.expert, 10000);
	infile.getline(f.link, 10000);

	string line;
	int i = 0, j = 0;
b:while (getline(infile, line)) {
	if (line == "#") {
		break;
	}
	else if (line == "养生保健食谱：") {
		streampos previousPosition = infile.tellg();
		while (getline(infile, line)) {
			if (line == "食疗验方：")
				goto a;
			else if (line == "#") return;
			f.recipe[i++] = line;
			f.recipe_size++;
		}
	}
	else if (line == "食疗验方: ") {
	a:streampos previousPosition = infile.tellg();
		while (getline(infile, line)) {
			if (line == "#")
			{
				infile.seekg(previousPosition);
				goto b;
			}
			f.therapy_size++;
			f.therapy[j++] = line;
		}
	}
}
}

void ReadFile(SqList& L, string filename) {
	ifstream file(filename);
	allfilename = filename;
	string line;
	int i = 0;
	L.length = 0;
	ifstream infile(filename);
	if (!infile) {
		cout << "文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}

	while (!infile.eof()) {
		Food f;
		ReadFood(f, infile);
		L.elem[L.length++] = f;
	}
	infile.close();
}

TNode* InitTNode() {
	// 初始化Trie树结点
	TNode* newNode = new TNode;
	newNode->foodPtr = nullptr;
	for (int i = 0; i < 53; ++i) {
		newNode->child[i] = nullptr;
	}
	return newNode;
}

void InsertTrie(TNode* root, const Food& f) {
	TNode* p = root;
	char* sname = new char[30];
	for (int i = 0; i < 30; i++)
		sname[i] = '\0';
	string s = "";
	for (int i = len - 1; i < strlen(f.sname); i++)
		s += tolower(f.sname[i]);
	strcpy(sname, s.c_str());
	//cout<<sname<<endl;
	for (int i = 0; i < strlen(sname); ++i) {
		//cout << sname << endl;
		int index = (sname[i] == ' ') ? 52 : (sname[i] - 'a');
		if (p->child[index] == nullptr) {
			// 如果节点不存在，初始化节点
			p->child[index] = new TNode();
		}
		p = p->child[index];
	}
	p->foodPtr = new Food(f); // 将食物信息保存到叶子节点
}

TrieTree BuildTree(SqList& L) {
	TrieTree root = InitTNode();
	root1 = root;
	for (int i = 0; i < L.length; ++i) {
		InsertTrie(root, L.elem[i]);
	}
	return root;
}

Food* TrieSearch(TrieTree root, char* sname) {
	TNode* p = root;
	int len = strlen(sname);
	for (int i = 0; i < len; ++i) {
		int index = (sname[i] == ' ') ? 52 : (sname[i] - 'a');
		if (p->child[index] == nullptr) {
			return nullptr;
		}
		p = p->child[index];
	}
	return p->foodPtr;
}

void Print(Food* food) {
	// 输出Trie树中指针food指向的结点
	cout << food->name << endl;
	cout << food->sname << endl;
	cout << food->health << endl;
	cout << food->nutrition << endl;
	cout << food->expert << endl;
	cout << food->link << endl;
	if (food->recipe_size != 0)
		cout << "养生保健食谱：" << endl;
	for (int i = 0; i < food->recipe_size; ++i) {
		cout << food->recipe[i] << endl;
	}
	if (food->therapy_size != 0)
		cout << "食疗验方：" << endl;
	for (int i = 0; i < food->therapy_size; ++i) {
		cout << food->therapy[i] << endl;
	}
}

double GetASL(SqList& L) {
	// 计算查找成功时的平均查找长度ASL
	double ASL = 0;
	for (int i = 0; i < L.length; ++i) {
		char sname[30] = { '\0' };
		string s = "";
		for (int j = len - 1; j < strlen(L.elem[i].sname); j++) {
			if (L.elem[i].sname[j] > 'A' && L.elem[i].sname[j] < 'Z') {
				char c = L.elem[i].sname[j] + 32;
				s += c;
			}
			else
				s += L.elem[i].sname[j];
		}
		for (int j = 0; j < s.length(); j++)
			sname[j] = s[j];
		Food* food = TrieSearch(root1, sname);
		if (food != nullptr) {
			ASL += strlen(sname);
		}
	}
	return ASL / L.length;
}


int main() {
	SqList L;
	InitList(L);
	ReadFile(L, "food.txt");
	TNode* root = BuildTree(L);
	char* sname = new char[100];
	cin.getline(sname, 100);
	Food* food = TrieSearch(root, sname);
	if (food != NULL) {
		Print(food);
		double ASL = GetASL(L);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else
		puts("查找失败");
	FreeList(L);
	return 0;
}