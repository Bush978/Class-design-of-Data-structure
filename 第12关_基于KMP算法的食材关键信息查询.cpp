#include <bits/stdc++.h>
#define MAXSIZE 10000
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int len = strlen("��");
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

void InitList(SqList& L) {
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void FreeList(SqList& L) {
	delete[] L.elem;
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
	while (getline(infile, line)) {
		if (line == "#") {
			break;
		}
		else if (line == "��������ʳ�ף�") {
			while (getline(infile, line)) {
				if (line == "ʳ���鷽��")
					break;
				else if (line == "#") return;
				f.recipe[i++] = line;
			}
		}
		else if (line == "ʳ���鷽: ") {
			while (getline(infile, line)) {
				if (line == "#")
					break;
				f.therapy[j++] = line;
			}
		}
	}
}

void ReadFile(SqList& L, string filename) {
	ifstream file(filename);
	string line;
	int i = 0;
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

void GetNext(const char* T, int next[]) {
	int m = strlen(T);
    next[0] = -1;
	next[1] = 0;
	int i = 1, j = 0;
	while (i < m) {
		if (j == -1 || T[i] == T[j]) {
			i += 1;
			j += 1;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}

bool KMP(const char* S,const char* T, int next[]) {
	//�ַ���ÿ�������ƶ�һλ
	int n = strlen(S);
	int m = strlen(T);
	int i = 0, j = 1;
	while (i <= n && j < m) {
		if (j == -1 || S[i] == T[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j >= m) 
		return true;
	else
		return false;
}

bool SearchList(SqList& L,const char* keyword, int next[]) {
	int flag = 0;
	for (int i = 0; i < L.length; ++i) {
		if (KMP(L.elem[i].health, keyword, next) == true || KMP(L.elem[i].nutrition, keyword, next) == true) {
			flag = 1;
			string s1 = "";
			string s2 = "�������ƣ�";
			for (int j = 0; j < strlen(L.elem[i].name); j++)
				s1 += tolower(L.elem[i].name[j]);
			s1.erase(0, s2.length());
			cout << s1 << endl;
		}
	}
	if (flag == 1) return true;
	else return false;
}

int main() {
	SqList L;
	InitList(L);
	ReadFile(L, "food.txt");
	char* keyword = new char[100];
	cin >> keyword;
	int next[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++)
		next[i] = 0;
	GetNext(keyword, next);
	if (!SearchList(L, keyword, next))
		cout << "��ƥ��" << endl;
	FreeList(L);
	return 0;
}
