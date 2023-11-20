#include <bits/stdc++.h>
#define m 200
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
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
int len = strlen("�������ƣ�");
int sumcount = 0;

void InitList(LinkList* H) {
	// �����ʼ��
	for (int i = 0; i < m; i++) {
		H[i] = new LNode;
		H[i]->next = nullptr;
	}
}

int Hash(char* sname) {
	// ʵ��ɢ�к������ַ���sname�и��ַ����±꣨��0��ʼ����ƽ�������ַ���Ӧ��ASCII��ֵ����Ӻ���199ȡ��
	int sum = 0;
	for (int i = 0; i < strlen(sname); i++) {
		sum += ((i) * (i) * int(sname[i]));
	}
	return sum % 199;
}

void ListInsert(LinkList* H, Food f, int& sumCmp) {
	// ��ɢ�б��в����µ�ʳ��f
	// �ڲ���Ĺ�����ͳ���ܵıȽϴ���sumCmp

	sumCmp++;
	// �����������

	int index = Hash(f.sname);
	// ����ʳ�����ƵĹ�ϣֵ��ȷ�������λ��

	LNode* p = H[index];
	// ��ȡ��Ӧλ�õ�����ͷָ��

	while (p->next != nullptr) {
		// ��������ֱ��β��
		p = p->next;
		sumCmp++;
		// ����������ܵıȽϴ�������
	}

	LNode* q = new LNode;
	// �����µĽڵ�
	q->data = f;
	q->next = nullptr;
	// ��ʼ���½ڵ�����ݺ�ָ��

	p->next = q;
	// ���½ڵ���뵽����β��
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

int ReadFile(LinkList* H, int& sumCmp, string filename) {
	// ��ȡ�ļ�������ListInsert������ÿ��ʳ�����ݲ���ɢ�б�
	// ����ʳ�����ݵ�����
	ifstream file(filename);
	string line;
	//sumcount += 3;
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
		for (int i = 0; i < 30 - len; i++)
			f.sname[i] = f.sname[i + len];
		//cout << f.sname << endl;
		ListInsert(H, f, sumCmp);
		sumcount++;
	}

	infile.close();

}

int SearchHL(LinkList* H, char* key) {
	// ��ɢ�б�HT�в���ʳ��Ӣ�����Ƶ���key��Ԫ��
	// ���ҵ����򷵻�ɢ�б�ĵ�Ԫ��ţ����򷵻�-1

	int hashVal = Hash(key);
	// ����Ŀ��ʳ�����ƵĹ�ϣֵ

	LinkList p = H[hashVal]->next;
	// ��ȡ��Ӧλ�õ�����ͷָ��

	while (p != nullptr) {
		// ��������
		if (strcmp(p->data.sname, key) == 0) {
			// ����ҵ�Ŀ��ʳ�����ƣ�����ɢ�б�ĵ�Ԫ���
			return hashVal;
		}
		p = p->next;
		// �ƶ�����һ���ڵ�
	}

	return -1;
	// ����������δ�ҵ�Ŀ��ʳ�����ƣ��򷵻�-1
}

double GetASL(int sumCmp, int count) {
	// ���ػ�������ַ����ɢ�в��ҵ�ASL

	count = sumcount;
	// ����countΪȫ�ֱ���sumcount��ֵ

	return (double)sumCmp / count;
	// ����ƽ�����ҳ��ȣ�ASL��
}


void Print(LNode* p, char* sname) {
	// ���ʳ����Ϣ
	// ��ʳ����Ϣ�в�����ĳ�����ݣ���������ޡ�
	cout << p->data.name << endl;

	cout << "Ӣ�����ƣ�" << p->data.sname << endl;
	cout << p->data.health << endl;
	cout << p->data.nutrition << endl;
	cout << p->data.expert << endl;
	cout << p->data.link << endl;
	if (p->data.recipe_size != 0)
		cout << "��������ʳ�ף�" << endl;
	for (int i = 0; i < p->data.recipe_size; i++)
		cout << p->data.recipe[i] << endl;
	if (p->data.therapy_size != 0)
		cout << "ʳ���鷽��" << endl;
	for (int i = 0; i < p->data.therapy_size; i++)
		cout << p->data.therapy[i] << endl;
}

int main() {
	LinkList H[m];
	InitList(H);
	string filename = "food.txt";
	int count = 0;	// ��¼ʳ�����ݵ�����
	int sumCmp = 0; // �ڲ���Ĺ�����ͳ�ƱȽϴ��������ڼ���ASL
	count = ReadFile(H, sumCmp, filename);
	char sname[100]; // ����Ҫ���ҵ�ʳ��Ӣ������
	cin.getline(sname, 100);
	int pos = SearchHL(H, sname);
	if (pos != -1) {
		LinkList p = H[pos]->next; // ���ҳɹ�����pָ������ͷ���
		Print(p, sname);
		double ASL = GetASL(sumCmp, count);
		cout << "ASLΪ��" << fixed << setprecision(2) << ASL << endl;
	}
	else {
		cout << "����ʧ��" << endl;
	}
	return 0;
}