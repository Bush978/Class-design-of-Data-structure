#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
string allfilename;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
int len = sizeof("Ӣ�����ƣ�") / sizeof(char);
typedef struct Food {
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
typedef struct {
	Food* elem;                 // ָ�������ָ��
	int length;                 // ����ĳ���
} SqList;
typedef struct TNode {
	// �����ֵ����ṹ��
	Food* foodPtr;		        // ʳ��ָ��
	struct TNode* child[53];    // �ӽ���ָ�����飬��26��Сд��ĸ��26����д��ĸ��1���ո����
} TNode, * TrieTree;
TNode* root1 = NULL;

void InitList(SqList& L) {
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void FreeList(SqList& L) {
	// �ͷ��ڴ�
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

void ReadFile(SqList& L, string filename) {
	ifstream file(filename);
	allfilename = filename;
	string line;
	int i = 0;
	L.length = 0;
	ifstream infile(filename);
	if (!infile) {
		cout << "�ļ���ʧ��" << endl;
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
	// ��ʼ��Trie�����
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
			// ����ڵ㲻���ڣ���ʼ���ڵ�
			p->child[index] = new TNode();
		}
		p = p->child[index];
	}
	p->foodPtr = new Food(f); // ��ʳ����Ϣ���浽Ҷ�ӽڵ�
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
	// ���Trie����ָ��foodָ��Ľ��
	cout << food->name << endl;
	cout << food->sname << endl;
	cout << food->health << endl;
	cout << food->nutrition << endl;
	cout << food->expert << endl;
	cout << food->link << endl;
	if (food->recipe_size != 0)
		cout << "��������ʳ�ף�" << endl;
	for (int i = 0; i < food->recipe_size; ++i) {
		cout << food->recipe[i] << endl;
	}
	if (food->therapy_size != 0)
		cout << "ʳ���鷽��" << endl;
	for (int i = 0; i < food->therapy_size; ++i) {
		cout << food->therapy[i] << endl;
	}
}

double GetASL(SqList& L) {
	// ������ҳɹ�ʱ��ƽ�����ҳ���ASL
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
		cout << "ASLΪ��" << fixed << setprecision(2) << ASL << endl;
	}
	else
		puts("����ʧ��");
	FreeList(L);
	return 0;
}