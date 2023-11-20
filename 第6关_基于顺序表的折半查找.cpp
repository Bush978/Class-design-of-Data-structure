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
		outfile  << L.elem[i].sname << endl;
		outfile << L.elem[i].health << endl;
		outfile << L.elem[i].nutrition << endl;
		outfile << L.elem[i].expert << endl;
		outfile << L.elem[i].link << endl;
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

bool cmp(Food a, Food b) {
	// �ȽϺ���������ʳ��Ӣ�����ƴ�С��������
	//11
	string s1 = "", s2 = "";
	for(int i = 10; i < strlen(a.sname); i++)
		s1 += tolower(a.sname[i]);
	for(int i = 10; i < strlen(b.sname); i++)
		s2 += tolower(b.sname[i]);
	if(s1 <= s2)
		return true;
	else
		return false;
}

void SortFood(SqList& L) {
	// ��С��������
	//ð������
	for(int i = 0; i < L.length - 1; i++)
		for(int j = 0; j < L.length - i - 1; j++)
			if(!cmp(L.elem[j], L.elem[j + 1]))
				swap(L.elem[j], L.elem[j + 1]);
	SaveFile(L, "new_food.txt");
}

void Print(SqList& L, int pos) {
	// ���ʳ����Ϣ
	cout << L.elem[pos].name << endl;
	cout << L.elem[pos].sname << endl;
	cout << L.elem[pos].health << endl;
	cout << L.elem[pos].nutrition << endl;
	cout << L.elem[pos].expert << endl;
	cout << L.elem[pos].link << endl;
	if(L.elem[pos].recipe_size != 0)
	cout << "��������ʳ�ף�" << endl;
	for (int i = 0; i < L.elem[pos].recipe_size; i++) {
		cout << L.elem[pos].recipe[i] << endl;
	}
	if(L.elem[pos].therapy_size != 0)
	cout << "ʳ���鷽��" << endl;
	for (int i = 0; i < L.elem[pos].therapy_size; i++) {
		cout << L.elem[pos].therapy[i] << endl;
	}
}

int BinarySearch(SqList& L, char* sname) {
	// ��˳���L���۰����ʳ��Ӣ�����Ƶ���sname������Ԫ��
	// ���ҵ����򷵻ظ�Ԫ���ڱ��е��±꣬���򷵻�-1
	string s = sname;
	string s1 = "Ӣ�����ƣ�";
	s = s1 + s;
	//string sתΪchar����
	char s2[100] = {'\0'};
	for(int i =0; i < s.length(); i++)
		s2[i] = s[i];
	int low = 0, high = L.length - 1, mid;
	// �������low��ʾ������Χ����ʼλ�ã�high��ʾ������Χ�Ľ���λ�ã�mid��ʾ�м�λ��
	while (low <= high) {
		// ��������Χ��Ȼ��Чʱ��ִ������ѭ��
		mid = (low + high) / 2;
		// ���㵱ǰ������Χ���м�λ��
		if (strcmp(L.elem[mid].sname, s2) == 0)
			// ����м�λ�õ�Ԫ����Ŀ��Ԫ����ȣ������м�λ��
			return mid;
		else if (strcmp(L.elem[mid].sname, s2) < 0)
			// ����м�λ�õ�Ԫ��С��Ŀ��Ԫ�أ�����������ΧΪ�Ұ벿��
			low = mid + 1;
		else
			// ����м�λ�õ�Ԫ�ش���Ŀ��Ԫ�أ�����������ΧΪ��벿��
			high = mid - 1;
	}
	// ��������Χ��Чʱ����ʾĿ��Ԫ�ز��������У�����-1

   return -1;
}



double GetASL(SqList& L) {
	// ���ػ���˳�����۰���ҵ�ASL 
	// ���ػ���˳�����۰���ҵ�ƽ���������ȣ�ASL��

	double asl = 0;
	// ��ʼ��ƽ����������Ϊ0

	int total = 0, level = 0;
	// ��ʼ���ܽڵ����Ͳ㼶

	for (int i = 0; total != L.length; i++) {
		// ѭ��ֱ���������нڵ�

		level = pow(2, i);
		// ���㵱ǰ�㼶�Ľڵ���

		total += level;
		// �����ܽڵ���

		if (total < L.length)
			// ����ܽڵ���δ����˳����ȣ��ۼ�ƽ����������
			asl += (i + 1) * level;
		else {
			// ����ܽڵ����Ѿ�����˳����ȣ������ܽڵ���Ϊ˳�����
			total = L.length;
			// �ۼ�ƽ���������ȣ����ǳ�������
			asl += (i + 1) * (total - level + 1);
		}
	}

	return asl / total;
	// ����ƽ���������ȳ����ܽڵ����Ľ��
}

int main() {
	SqList L;
	InitList(L);
	string originFilename = "food.txt";
	ReadFile(L, originFilename);
	char sname[100];
	cin.getline(sname, 100);
	SortFood(L);
	int pos = BinarySearch(L, sname);
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