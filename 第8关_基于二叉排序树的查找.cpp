#include <bits/stdc++.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#define MAXSIZE 10000
using namespace std;
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
typedef struct BSTNode {
	Food data;				    // ʳ����Ϣ
	struct BSTNode* lchild;     // ����ָ��
	struct BSTNode* rchild;     // �Һ���ָ��
} BSTNode, * BSTree;
Food food[MAXSIZE];

void InitBSTree(BSTree& T) {
	// ������������ʼ��
	T = nullptr;
}

int cmp(char* sname1, char* sname2) {
	// �ȽϺ���������ʳ��Ӣ�����ƴ�С��������
	//11
	string s1 = "", s2 = "";
	for (int i = 10; i < strlen(sname1); i++)
		s1 += tolower(sname1[i]);
	for (int i = 10; i < strlen(sname2); i++)
		s2 += tolower(sname2[i]);
	if (s1 < s2)
		return -1;
	else if (s1 > s2)
		return 1;
	else return 0;
}

void copy(Food* dst, Food* src) {
	//src��dst
	strcpy(dst->name, src->name);
	strcpy(dst->sname, src->sname);
	strcpy(dst->health, src->health);
	strcpy(dst->nutrition, src->nutrition);
	strcpy(dst->expert, src->expert);
	strcpy(dst->link, src->link);

	dst->recipe_size = src->recipe_size;
	dst->therapy_size = src->therapy_size;

	for (int i = 0; i != src->recipe_size; i++)
		dst->recipe[i] = string(src->recipe[i].begin(), src->recipe[i].end());
	for (int i = 0; i != src->therapy_size; i++)
		dst->therapy[i] = string(src->therapy[i].begin(), src->therapy[i].end());
}


BSTree InsertBST(BSTree& T, Food e) {
	// ������������T�в����ڹؼ��ֵ���e.sname������Ԫ��ʱ��������Ԫ��

	if (T == nullptr) {
		// �����ǰ�ڵ�Ϊ�գ���ʾ�ҵ��˲���λ��
		BSTree newnode = new BSTNode;
		// ����һ���½ڵ�

		copy(&newnode->data, &e);
		// ����Ԫ�����ݵ��½ڵ�

		newnode->lchild = nullptr;
		newnode->rchild = nullptr;
		// ��ʼ���½ڵ����������Ϊ��

		return newnode;
		// �����½ڵ���Ϊ����Ľ��
	}

	if (strcmp(e.sname, T->data.sname) < 0) {
		// ���������Ԫ�عؼ���С�ڵ�ǰ�ڵ�ؼ���
		T->lchild = InsertBST(T->lchild, e);
		// �ݹ���뵽������
	}
	else if (strcmp(e.sname, T->data.sname) > 0) {
		// ���������Ԫ�عؼ��ִ��ڵ�ǰ�ڵ�ؼ���
		T->rchild = InsertBST(T->rchild, e);
		// �ݹ���뵽������
	}

	return T;
	// ���ص�ǰ�ڵ㣨δ�������룩
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

int ReadFile(BSTree& T, string filename) {
	// ��ȡ�ļ�������InsertBST������ÿ��ʳ�����ݲ������������
	// ����ʳ�ĵ�����
	ifstream infile(filename);
	if (!infile) {
		cout << "�ļ���ʧ��" << endl;
		exit(EXIT_FAILURE);
	}
	BSTree current = T, head = nullptr;
	int n = 0;
	while (!infile.eof()) {
		Food f;
		ReadFood(f, infile);
		food[n] = f;
		n++;
		T = InsertBST(T, f);
		//		cout<<T->data.name<<endl;
	}
	if (T == nullptr)
		cout << "����" << endl;
	infile.close();
	return n;
}

void Print(BSTNode* T) {
	// ���ʳ����Ϣ
	cout << T->data.name << endl;
	cout << T->data.sname << endl;
	cout << T->data.health << endl;
	cout << T->data.nutrition << endl;
	cout << T->data.expert << endl;
	cout << T->data.link << endl;
	if (T->data.recipe_size != 0)
		cout << "��������ʳ�ף�" << endl;
	for (int i = 0; i < T->data.recipe_size; i++)
		cout << T->data.recipe[i] << endl;
	if (T->data.therapy_size != 0)
		cout << "ʳ���鷽��" << endl;
	for (int i = 0; i < T->data.therapy_size; i++)
		cout << T->data.therapy[i] << endl;
}


BSTNode* SearchBST(BSTree& T, char* sname) {
    // ���Ҷ�Ӧʳ��

    string s = sname;
    // �������char����ת��Ϊstring����
    string s1 = "Ӣ�����ƣ�";
    s = s1 + s;
    // ��ʳ������ǰ����"Ӣ�����ƣ�"������������ַ���

    char s2[100] = { '\0' };
    // ��ʼ��char����

    for (int i = 0; i < s.length(); i++)
        s2[i] = s[i];
    // ��string���͵��ַ������Ƶ�char����

    if (T == nullptr || cmp(T->data.sname, s2) == 0) {
        // �����ǰ�ڵ�Ϊ�ջ��߽ڵ�ؼ�����Ŀ���ַ�����ȣ����ص�ǰ�ڵ�
        return T;
    }

    if (cmp(s2, T->data.sname) < 0) {
        // ���Ŀ���ַ���С�ڵ�ǰ�ڵ�ؼ��֣��ݹ����������в���
        return SearchBST(T->lchild, sname);
    }
    else {
        // ���Ŀ���ַ������ڵ�ǰ�ڵ�ؼ��֣��ݹ����������в���
        return SearchBST(T->rchild, sname);
    }
}

int GetSumCmp(BSTree T, int sumCmp) {
	// ͳ�Ʋ��ҳɹ�ʱ���ܱȽϴ���

	int left = 0, right = 0, level = 1;
	// ��ʼ�����ұ߽�Ͳ㼶

	BSTNode* queue[10000];
	// ����һ���������ڲ����������������

	queue[0] = T;
	// ��ʼ�����У����ڵ����

	while (right >= left) {
		// �����в�Ϊ��ʱ��ִ������ѭ��

		int currentwidth = right - left + 1;
		// ��ǰ��Ľڵ���

		sumCmp += level * currentwidth;
		// �����ܱȽϴ���

		int constant = right, i = left;
		// ��¼��ǰ��ڵ����ĳ�������ʼ����������

		while (i <= constant) {
			// ���������ǰ��Ľڵ�

			BSTNode* node = queue[left++];
			// ����һ���ڵ�

			if (node->lchild != NULL)
				// �����������Ϊ�գ����������
				queue[++right] = node->lchild;

			if (node->rchild != NULL)
				// �����������Ϊ�գ����������
				queue[++right] = node->rchild;

			i++;
		}

		level++;
		// �㼶����
	}

	return sumCmp;
	// �����ܱȽϴ���
}

double GetASL(BSTree& T, int count) {
	// ������ڶ�����������ƽ���������ȣ�ASL��

	double addition = GetSumCmp(T, 0);
	// ����GetSumCmp������ȡ�ܱȽϴ���

	return addition / count;
	// ����ƽ����������
}


int main() {
	BSTree T = NULL;
	InitBSTree(T);
	int count = 0;
	string originFilename = "food.txt";
	count = ReadFile(T, originFilename);
	char sname[100];
	cin.getline(sname, 100);
	BSTNode* t = SearchBST(T, sname);
	if (t != NULL) {
		Print(t);
		double ASL = GetASL(T, count);
		cout << "ASLΪ��" << fixed << setprecision(2) << ASL << endl;
	}
	else
		cout << "����ʧ��" << endl;
	return 0;
}