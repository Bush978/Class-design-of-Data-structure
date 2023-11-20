#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
string allfilename;
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
	string line;
	allfilename = filename;
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

int SeqSearch(SqList& L, char* sname) {
	// ��˳���L��˳�����ʳ��Ӣ�����Ƶ���sname������Ԫ��
	// ���ҵ����򷵻ظ�Ԫ���ڱ��е��±꣬���򷵻�-1
	string strname = sname;
	string strname2 = "Ӣ�����ƣ�";
	strname = strname2 + strname;
	cout << strname << endl;
	for (int i = 0; i < L.length; i++) {
		if (strname == L.elem[i].sname) 
			return i;
	}
	return -1;
}

double GetASL(SqList& L) {
	// ���ػ���˳����˳����ҵ�ASL
	return (double)(L.length + 1) / 2.0;
}

void Print(SqList& L, int pos) {
	// ���ʳ����Ϣ
	cout << "�������ƣ�" << L.elem[pos].name << endl;
	cout << "Ӣ�����ƣ�" << L.elem[pos].sname << endl;
	cout << "������Ч��" << L.elem[pos].health << endl;
	cout << "Ӫ���빦Ч��" << L.elem[pos].nutrition << endl;
	cout << "ר�����ѣ�" << L.elem[pos].expert << endl;
	cout << "������ӣ�" << L.elem[pos].link << endl;
	cout << "��������ʳ�ף�" << endl;
	for (int i = 0; i < L.elem[pos].recipe_size; i++) {
		cout << L.elem[pos].recipe[i] << endl;
	}
	cout << "ʳ���鷽��" << endl;
	for (int i = 0; i < L.elem[pos].therapy_size; i++) {
		cout << L.elem[pos].therapy[i] << endl;
	}
}

int main() {
	SqList L;
	InitList(L);
	string originFilename = "food.txt";
	ReadFile(L, originFilename);
	char sname[100];
	cin.getline(sname, 100);
	int pos = SeqSearch(L, sname);
	if (pos != -1) {
		Print(L, pos);
		double ASL = GetASL(L);
		cout << "ASLΪ��" << fixed << setprecision(2) << ASL << endl;
	}
	else {
		cout << "����ʧ��" << endl;
	}
	FreeList(L);
	return 0;
}