#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
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
int len = strlen("�������ƣ�");

void InitList(SqList& L) {
	// ʹ�ö�̬�ڴ����new���г�ʼ��
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void FreeList(SqList& L) {
	// �ͷ��ڴ�
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
		for (int i = 0; i < 30; i++)
			f.sname[i] = '/0';
		ReadFood(f, infile);
		for (int i = 0; i < 100 - len; i++)
			f.sname[i] = f.sname[i + len];
		//cout << f.sname << endl;
		L.elem[L.length++] = f;
	}

	infile.close();
}


int cmp(Food a, Food b) {
	// �ȽϺ���������ʳ��Ӣ�����ƴ�С��������
	//11
	char* s1 = new char[30], * s2 = new char[30];
	for (int i = 0; i < 30; i++) {
		s1[i] = a.sname[i];
		s2[i] = b.sname[i];
	}
	string ss1(s1), ss2(s2);
	if (ss1 >= ss2)
		return 1;
	else
		return -1;
}


void Lcopy(Food& f2, Food& f1)
{
	//����ߵ�ֵ�����ұ�
	strcpy(f1.name, f2.name);
	//f1���
	strcpy(f1.sname, f2.sname);
	strcpy(f1.health, f2.health);
	strcpy(f1.nutrition, f2.nutrition);
	strcpy(f1.expert, f2.expert);
	strcpy(f1.link, f2.link);
	f1.recipe_size = f2.recipe_size;
	f1.therapy_size = f2.therapy_size;
	for (int i = 0; i < f2.recipe_size; i++)
		f1.recipe[i] = f2.recipe[i];
	for (int i = 0; i < f2.therapy_size; i++)
		f1.therapy[i] = f2.therapy[i];
}

void BInsertSort(SqList& L, int& kcn, int& rmn) {
	// ��˳������۰��������
	// ע��L.elem[0]�����ڱ���Ԫ
	// ���������ʳ��Ӣ�����ơ�KCN��RMN

	// ��˳���Ԫ����������ƶ�һλ
	for (int i = L.length; i >= 1; i--)
		Lcopy(L.elem[i - 1], L.elem[i]);

	for (int i = 2; i <= L.length; i++)
	{
		// �ӵڶ���Ԫ�ؿ�ʼ�������۰��������
		Lcopy(L.elem[i], L.elem[0]);
		rmn++;
		// ���ݵ�ǰλ�õ�Ԫ�ص��ڱ���Ԫ����¼�ƶ�����+1
		int low = 1, high = i - 1;
		// ��ʼ���۰���ҵĵ�λ�͸�λ
		while (low <= high)
		{
			int m = (low + high) / 2;
			// �����м�λ��
			if (cmp(L.elem[0], L.elem[m]) == -1)
				high = m - 1;
			else
				low = m + 1;
			kcn++;
			// ÿ�αȽϹؼ��ִ���+1
		}
		for (int j = i - 1; j >= high + 1; j--) {
			Lcopy(L.elem[j], L.elem[j + 1]);
			rmn++;
			// ��Ԫ�غ���һλ����¼�ƶ�����+1
		}
		Lcopy(L.elem[0], L.elem[high + 1]);
		rmn++;
		// �����ݵ�Ԫ�ز��뵽��ȷλ�ã���¼�ƶ�����+1
	}

	// ���������ʳ��Ӣ������
	for (int k = 1; k <= L.length; k++)
		cout << L.elem[k].sname << endl;

	cout << "�ܵĹؼ��ֱȽϴ���KCNΪ��" << kcn << endl;
	cout << "�ܵļ�¼�ƶ�����RMNΪ��" << rmn << endl;
}


int main() {
	SqList L;
	InitList(L);
	int kcn = 0;
	int rmn = 0;
	ReadFile(L, "food.txt");
	BInsertSort(L, kcn, rmn);
	FreeList(L);
	return 0;
}