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
		if (i != L.length - 1)
			outfile << "#" << endl;
	}

	outfile.close();
}

Food* DeleteFood(SqList& L, char* name) {
	// ������������ɾ��ָ��ʳ����Ϣ
	// ���ɾ���ɹ������ظ�ʳ�ĵ���Ϣ�����򣬷���NULL
	string strname = name;
	string strname2 = "�������ƣ�";
	strname = strname2 + strname;
	for (int i = 0; i < L.length; i++) {
		if (strname == L.elem[i].name) {
			Food* food = new Food;
			*food = L.elem[i];
			for (int j = i; j < L.length - 1; j++) {
				L.elem[j] = L.elem[j + 1];
			}
			L.length--;
			return food;
		}
	}
}

void Print(Food* food) {
	// ���ʳ����Ϣ
	cout << food->name << endl;
	cout << food->sname << endl;
	cout << food->health << endl;
	cout << food->nutrition << endl;
	cout << food->expert << endl;
	cout << food->link << endl;
	for (int j = 0; j < food->recipe_size; ++j) {
		cout << food->recipe[j] << endl;
	}
	cout << "ʳ���鷽��" << endl;
	for (int j = 0; j < food->therapy_size; ++j) {
		cout << food->therapy[j] << endl;
	}
}

bool check(SqList& L, char* name) {
	for (int i = 0; i < L.length; i++) {
		if (strcmp(name, L.elem[i].name) == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	SqList L;
	InitList(L);
	string originFilename = "food.txt";
	string newFilename = "new_food.txt";
	char name[100];
	cin >> name;
	ReadFile(L, originFilename);
	Food* food = DeleteFood(L, name);
	if (food) {
		SaveFile(L, newFilename);
		ReadFile(L, newFilename);
		if (check(L, name))
			Print(food);
		else
			cout << "ɾ��ʧ��" << endl;
	}
	else {
		cout << "ɾ��ʧ��" << endl;
	}
	FreeList(L);
	return 0;
}