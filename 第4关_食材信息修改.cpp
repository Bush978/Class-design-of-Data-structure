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

void SaveFile(SqList& L, string filename) {
	ofstream outfile(filename);
	if (!outfile) {
		cout << "�ļ���ʧ��" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < L.length; ++i) {
		outfile << L.elem[i].name << endl;
		outfile <<  L.elem[i].sname << endl;
		outfile << L.elem[i].health << endl;
		outfile <<  L.elem[i].nutrition << endl;
		outfile << L.elem[i].expert << endl;
		outfile <<  L.elem[i].link << endl;
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
bool ModifyFood(SqList& L, int type, char* name, string lines[], int n) {
	// ʳ����Ϣ�޸ģ����type��0�����޸���������ʳ�ף������޸�ʳ���鷽��Ϣ
	// ����޸ĳɹ�������true�����򣬷���false
	Food* food = new Food;
	string strname = name;
	string strname2 = "�������ƣ�";
	strname = strname2 + strname;
	for (int i = 0; i < L.length; i++) {
		food = &L.elem[i];
		if (strname == L.elem[i].name) {
			if (type == 0) {
				for (int i = 0; i < 30; i++)
					food->recipe[i] = "";
				food->recipe_size = n;
				//cout << food->recipe_size << endl;
				for (int i = 0; i < n; i++) {
					food->recipe[i] = lines[i];
				}
			}
			else {
				food->therapy_size = n;
				//cout << food->therapy_size << endl;
	            for (int i = 0; i < n; i++)
					food->therapy[i] = lines[i];
			}
		    return true;
		}
	}

	return false;
}

Food* getFood(SqList& L, char* name) {
	// ��ȡ�޸ĺ��ʳ����Ϣ
	ReadFile(L, allfilename);
	string strname = name;
	string strname2 = "�������ƣ�";
	strname = strname2 + strname;
	for (int i = 0; i < L.length; i++) {
		if (strname == L.elem[i].name) {
			Food* food;
			food = &L.elem[i];
			return food;
		}
	}
	return NULL;
}

void Print(Food* food) {
	// ���ʳ����Ϣ
	cout << food->name << endl;
	cout << food->sname << endl;
	cout << food->health << endl;
	cout << food->nutrition << endl;
	cout << food->expert << endl;
	cout << food->link << endl;
	cout << "��������ʳ�ף�" << endl;
	for (int j = 0; j < food->recipe_size; ++j) {
		cout << food->recipe[j] << endl;
	}
	cout << "ʳ���鷽��" << endl;
	for (int j = 0; j < food->therapy_size; ++j) {
		cout << food->therapy[j] << endl;
	}
}

int main() {
	SqList L;
	InitList(L);
	string originFilename = "food.txt";
	string newFilename = "new_food.txt";
	int type;
	cin >> type;
	char name[100];
	cin >> name;
	int n;
	string lines[30];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> lines[i];
	}
	ReadFile(L, originFilename);
	if (ModifyFood(L, type, name, lines, n)) {
		SaveFile(L, newFilename);
		ReadFile(L, newFilename);
		Food* food = getFood(L, name);
		if (food)
			Print(food);
		else
			cout << "�޸�ʧ��" << endl;
	}
	else {
		cout << "�޸�ʧ��" << endl;
	}
	FreeList(L);
	return 0;
}