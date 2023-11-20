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
typedef struct {
	// ���ŵ�ַ��ɢ�б�Ĵ洢��ʾ
	Food* key;
	int length;
} HashTable;
string  allfilename;
int len = strlen("�������ƣ�");
int sumcount = 0;

void InitHT(HashTable& HT) {
	// ɢ�б��ʼ��
	HT.length = m;
	HT.key = new Food[m];
	for (int i = 0; i < m; i++) {
		HT.key[i] = Food(); 
	}
}

int Hash(char* sname) {
	// ʵ��ɢ�к������ַ���sname�и��ַ����±꣨��0��ʼ����ƽ�������ַ���Ӧ��ASCII��ֵ����Ӻ���199ȡ��
	int sum = 0;
	for (int i = 0; i < strlen(sname); i++)
	{
		sum += ((i) * (i) * int(sname[i]));
	}
	return sum % 199;
}

void HTInsert(HashTable& HT, Food f, int& sumCmp) {
	// ��ɢ�б��в����µ�ʳ��f
	// �ڲ���Ĺ�����ͳ���ܵıȽϴ���sumCmp

	int hashVal = Hash(f.sname);
	// ����ʳ�����ƵĹ�ϣֵ

	int i = 0;
	sumCmp += 1;
	// ��ʼ��������������ۼ��ܵıȽϴ���

	while (HT.key[(hashVal + i) % m].sname[0] != '\0') {
		// ��ɢ�б�λ�ò�Ϊ��ʱ��������ͻ
		i++;
		sumCmp++;
		// ����������ܵıȽϴ�������
	}

	HT.key[(hashVal + i) % m] = f;
	// ��ʳ����Ϣ���뵽�յ�ɢ�б�λ��
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

void ReadFile(HashTable& HT, int& sumCmp, string filename) {
	// ��ȡ�ļ�������HTInsert������ÿ��ʳ�����ݲ���ɢ�б�
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
		HTInsert(HT, f, sumCmp);
		sumcount++;
	}

	infile.close();
}

void Print(HashTable HT, int pos) {
	// ���ʳ����Ϣ
	cout << HT.key[pos].name << endl;
	cout << "Ӣ�����ƣ�"<<HT.key[pos].sname << endl;
	cout << HT.key[pos].health << endl;
	cout << HT.key[pos].nutrition << endl;
	cout << HT.key[pos].expert << endl;
	cout << HT.key[pos].link << endl;
	if(HT.key[pos].recipe_size != 0)
	cout << "��������ʳ�ף�" << endl;
	for (int i = 0; i < HT.key[pos].recipe_size; i++) {
		cout << HT.key[pos].recipe[i] << endl;
	}
	if (HT.key[pos].therapy_size != 0)
	cout << "ʳ���鷽��" << endl;
	for (int i = 0; i < HT.key[pos].therapy_size; i++) {
		cout << HT.key[pos].therapy[i] << endl;
	}
}

int SearchHash(HashTable HT, char* key) {
	// ��ɢ�б�HT�в���ʳ��Ӣ�����Ƶ���key��Ԫ��
	// ���ҵ����򷵻�ɢ�б�ĵ�Ԫ��ţ����򷵻�-1

	int hashVal = Hash(key);
	// ����Ŀ��ʳ�����ƵĹ�ϣֵ

	int i = 0;
	// ��ʼ�����Ҵ���

	while (HT.key[(hashVal + i) % m].sname[0] != '\0') {
		// ��ɢ�б�λ�ò�Ϊ��ʱ�����в���
		if (strcmp(HT.key[(hashVal + i) % m].sname, key) == 0) {
			// ����ҵ�Ŀ��ʳ�����ƣ�����ɢ�б�ĵ�Ԫ���
			return (hashVal + i) % m;
		}
		i++;
		// δ�ҵ�ʱ������������һ��λ��
	}

	return -1;
	// ����������δ�ҵ�Ŀ��ʳ�����ƣ��򷵻�-1
}

double GetASL(HashTable HT, int sumCmp) {
	// ���ػ��ڿ��ŵ�ַ����ɢ�в��ҵ�ASL

	cout << sumCmp << endl;
	// ����ܵıȽϴ���

	return (double)sumCmp / (double)sumcount;
	// ����ƽ�����ҳ��ȣ�ASL��
}


int main() {
	HashTable HT;
	InitHT(HT);
	string filename = "food.txt";
	int sumCmp = 0; // �ڲ���Ĺ�����ͳ�ƱȽϴ��������ڼ���ASL
	ReadFile(HT, sumCmp, filename);
	char sname[100]; // ����Ҫ���ҵ�ʳ��Ӣ������
	cin.getline(sname, 100);
	int pos = SearchHash(HT, sname);
	if (pos != -1) {
		Print(HT, pos);
		double ASL = GetASL(HT, sumCmp);
		cout << "ASLΪ��" << fixed << setprecision(2) << ASL << endl;
	}
	else {
		cout << "����ʧ��" << endl;
	}
	return 0;
}
