#include <bits/stdc++.h>
#define MAXSIZE 10000
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
string allfilename;
int allsize;
typedef struct Food{
	char name[100];		        // ��������
	char sname[100];	        // Ӣ������
	char health[10000] ;	        // ������Ч
	char nutrition[10000];      // Ӫ���빦Ч
	char expert[10000] ;	        // ר������
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

void SaveFile(SqList& L, string filename) {
	ofstream outfile(filename);
	if (!outfile) {
		cout << "�ļ���ʧ��" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < L.length; ++i) {
		outfile << "�������ƣ�" << L.elem[i].name << endl;
		outfile << "Ӣ�����ƣ�" << L.elem[i].sname << endl;
		outfile << "������Ч��" << L.elem[i].health << endl;
		outfile << "Ӫ���빦Ч��" << L.elem[i].nutrition << endl;
		outfile << "ר�����ѣ� " << L.elem[i].expert << endl;
		outfile << "������ӣ�" << L.elem[i].link << endl;
		outfile << "��������ʳ�ף�" << endl;
		for (int j = 0; j < L.elem[i].recipe_size; ++j) {
			outfile << L.elem[i].recipe[j] << endl;
		}
		outfile << "ʳ���鷽��" << endl;
		for (int j = 0; j < L.elem[i].therapy_size; ++j) {
			outfile << L.elem[i].therapy[j] << endl;
		}
		if(i != L.length - 1)
		outfile << "#" << endl;
	}

	outfile.close();
}

bool InsertFood(SqList& L) {
	// ����ʳ����Ϣ������ʳ���������ơ�Ӣ�����ơ�������Ч��Ӫ���빦Ч����������ʳ�׺�ʳ���鷽��Ϣ
	// �������ɹ�������true�����򣬷���false
	Food f;
	cin.getline(f.name, 100);

	ifstream file(allfilename);
	string line;
	string s1 = "�������ƣ�";
	string s2 = f.name;
	s1 = s1 + s2;
	while (getline(file, line)) {
		char* name = new char[line.length()];
		if (line == s1) {
			return false;
		}
	}
	cin.getline(f.sname, 100);
	cin.getline(f.health, 10000);
	cin.getline(f.nutrition, 10000);
	cin.getline(f.expert, 10000);
	cin.getline(f.link, 10000);
	char l[10];
	cin.getline(l,10);
	f.recipe_size = atoi(l);

	for (int i = 0; i < f.recipe_size; ++i) {
		getline(cin, f.recipe[i]);
	}

	cin.getline(l, 10);
	f.therapy_size = atoi(l);
	allsize = f.therapy_size;
	for (int i = 0; i < f.therapy_size; ++i)
		getline(cin, f.therapy[i]);

	L.elem[L.length++] = f;
	return true;
}

void Print(SqList& L) {
	cout << L.elem[L.length-1].name << endl;
	cout << L.elem[L.length-1].sname << endl;
	cout << L.elem[L.length-1].health << endl;
	cout << L.elem[L.length-1].nutrition << endl;
	cout << L.elem[L.length-1].expert << endl;
	cout << L.elem[L.length-1].link << endl;
	cout << "��������ʳ�ף�" << endl;
	for (int j = 0; j < L.elem[L.length-1].recipe_size; ++j) {
		cout << L.elem[L.length-1].recipe[j] << endl;
	}

	cout << "ʳ���鷽��" << endl;
	for (int j = 0; j < L.elem[L.length-1].therapy_size; ++j) {
		cout << L.elem[L.length-1].therapy[j] << endl;
	}
}

int main() {
	SqList L;
	InitList(L);
	string originFilename = "food.txt";
	string newFilename = "new_food.txt";
	ReadFile(L, originFilename);
	if (InsertFood(L)) {
		SaveFile(L, newFilename);
		ReadFile(L, newFilename);
		Print(L);
	}
	else {
		cout << "����ʧ��" << endl;
	}
	FreeList(L);
	return 0;
}