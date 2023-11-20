#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
string allfilename;
typedef struct Food{
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
typedef struct LNode {
	Food data;			        // 食材信息
	struct LNode* next;         // 指向下一级结点
} LNode, * LinkList;

void InitList(LinkList& L) {
	// 使用动态内存分配new进行初始化
	L = new LNode;
	L->next = nullptr;
}

void FreeList(LinkList& L) {
	// 释放内存
	LNode* p = L;
	LNode* q;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
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

void ReadFile(LinkList& L, string filename) {
	string line;
	allfilename = filename;
	int i = 0;
	ifstream infile(filename);
	if (!infile) {
		cout << "文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	LNode *current = L;
	while (!infile.eof()) {
		LNode* newnode = new LNode;
		ReadFood(newnode->data, infile);
		newnode->next = current->next;
	    current->next = newnode;
	}
	infile.close();
}

LNode* SearchList(LinkList& L, char* sname) {
	// 在带头结点的单链表L中查找食材英文名称为sname的元素
	LNode *p = L->next;
	string s = sname;
	string s1 = "英文名称：";
	s = s1 + s;
	//string s转为char类型
	char s2[100] = { '\0' };
	for (int i = 0; i < s.length(); i++)
		s2[i] = s[i];
	while (p) {
		if (strcmp(p->data.sname, s2) == 0) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void Print(LNode* p) {
	// 输出食材信息
	cout  << p->data.name << endl;
	cout << p->data.sname << endl;
	cout << p->data.health << endl;
	cout << p->data.nutrition << endl;
	cout << p->data.expert << endl;
	cout << p->data.link << endl;
	if(p->data.recipe_size != 0)
	cout << "养生保健食谱：" << endl;
	for (int i = 0; i < p->data.recipe_size; i++) {
		cout << p->data.recipe[i] << endl;
	}
	if(p->data.therapy_size != 0)
	cout << "食疗验方：" << endl;
	for (int i = 0; i < p->data.therapy_size; i++) {
		cout << p->data.therapy[i] << endl;
	}


}

double GetASL(LinkList& L) {
	// 返回基于链表的顺序查找的ASL
	int n = 0;
	LNode* p = L->next;
	while (p) {
		n++;
		p = p->next;
	}
	return (n + 1) / 2.0;
}

int main() {
	LinkList L;
	InitList(L);
	string originFilename = "food.txt";
	ReadFile(L, originFilename);
	char sname[100];
	cin.getline(sname, 100);
	LNode* node = SearchList(L, sname);
	if (node) {
		Print(node);
		double ASL = GetASL(L);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else {
		cout << "查找失败" << endl;
	}
	FreeList(L);
	return 0;
}