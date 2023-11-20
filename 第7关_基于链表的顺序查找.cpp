#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
string allfilename;
typedef struct Food{
	char name[100];		        // ��������
	char sname[100];	        // Ӣ������
	char health[10000];	        // ������Ч
	char nutrition[10000];      // Ӫ���빦Ч
	char expert[10000];	        // ר������
	char link[10000];	        // �������
	string recipe[30];	        // ��������ʳ��
	int recipe_size = 0;        // ʳ������
	string therapy[30];	        // ʳ���鷽
	int therapy_size = 0;       // �鷽����
} Food;
typedef struct LNode {
	Food data;			        // ʳ����Ϣ
	struct LNode* next;         // ָ����һ�����
} LNode, * LinkList;

void InitList(LinkList& L) {
	// ʹ�ö�̬�ڴ����new���г�ʼ��
	L = new LNode;
	L->next = nullptr;
}

void FreeList(LinkList& L) {
	// �ͷ��ڴ�
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
	else if (line == "��������ʳ�ף�") {
		streampos previousPosition = infile.tellg();
		while (getline(infile, line)) {
			if (line == "ʳ���鷽��")
				goto a;
			else if (line == "#") return;
			f.recipe[i++] = line;
			f.recipe_size++;
		}
	}
	else if (line == "ʳ���鷽: ") {
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
		cout << "�ļ���ʧ��" << endl;
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
	// �ڴ�ͷ���ĵ�����L�в���ʳ��Ӣ������Ϊsname��Ԫ��
	LNode *p = L->next;
	string s = sname;
	string s1 = "Ӣ�����ƣ�";
	s = s1 + s;
	//string sתΪchar����
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
	// ���ʳ����Ϣ
	cout  << p->data.name << endl;
	cout << p->data.sname << endl;
	cout << p->data.health << endl;
	cout << p->data.nutrition << endl;
	cout << p->data.expert << endl;
	cout << p->data.link << endl;
	if(p->data.recipe_size != 0)
	cout << "��������ʳ�ף�" << endl;
	for (int i = 0; i < p->data.recipe_size; i++) {
		cout << p->data.recipe[i] << endl;
	}
	if(p->data.therapy_size != 0)
	cout << "ʳ���鷽��" << endl;
	for (int i = 0; i < p->data.therapy_size; i++) {
		cout << p->data.therapy[i] << endl;
	}


}

double GetASL(LinkList& L) {
	// ���ػ��������˳����ҵ�ASL
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
		cout << "ASLΪ��" << fixed << setprecision(2) << ASL << endl;
	}
	else {
		cout << "����ʧ��" << endl;
	}
	FreeList(L);
	return 0;
}