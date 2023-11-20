#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
string allfilename;
typedef struct Food {
	char name[100];		        // 中文名称
	char sname[100];	        // 英文名称
	char health[10000];	        // 养生功效
	char nutrition[10000];      // 营养与功效
	char expert[10000];	        // 专家提醒
	char link[10000];	        // 相关链接
	string recipe[30];	        // 养生保健食谱
	int recipe_size = 0;        // 食谱数量
	string therapy[30];	        // 食疗验方
	int therapy_size = 0;       // 验方数量
} Food;
typedef struct {
	Food* elem;                 // 指向数组的指针
	int length;                 // 数组的长度
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
	else if (line == "养生保健食谱：") {
		streampos previousPosition = infile.tellg();
		while (getline(infile, line)) {
			if (line == "食疗验方：")
				goto a;
			else if (line == "#") return;
			f.recipe[i++] = line;
			f.recipe_size++;
		}
	}
	else if (line == "食疗验方: ") {
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
		cout << "文件打开失败" << endl;
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
	// 在顺序表L中顺序查找食材英文名称等于sname的数据元素
	// 若找到，则返回该元素在表中的下标，否则返回-1
	string strname = sname;
	string strname2 = "英文名称：";
	strname = strname2 + strname;
	cout << strname << endl;
	for (int i = 0; i < L.length; i++) {
		if (strname == L.elem[i].sname) 
			return i;
	}
	return -1;
}

double GetASL(SqList& L) {
	// 返回基于顺序表的顺序查找的ASL
	return (double)(L.length + 1) / 2.0;
}

void Print(SqList& L, int pos) {
	// 输出食材信息
	cout << "中文名称：" << L.elem[pos].name << endl;
	cout << "英文名称：" << L.elem[pos].sname << endl;
	cout << "养生功效：" << L.elem[pos].health << endl;
	cout << "营养与功效：" << L.elem[pos].nutrition << endl;
	cout << "专家提醒：" << L.elem[pos].expert << endl;
	cout << "相关链接：" << L.elem[pos].link << endl;
	cout << "养生保健食谱：" << endl;
	for (int i = 0; i < L.elem[pos].recipe_size; i++) {
		cout << L.elem[pos].recipe[i] << endl;
	}
	cout << "食疗验方：" << endl;
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
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else {
		cout << "查找失败" << endl;
	}
	FreeList(L);
	return 0;
}