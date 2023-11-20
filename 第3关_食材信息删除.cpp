#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
string allfilename;
typedef struct Food{
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
	ifstream file(filename);
	allfilename = filename;
	string line;
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

void SaveFile(SqList& L, string filename) {
	ofstream outfile(filename);
	if (!outfile) {
		cout << "文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < L.length; ++i) {
		outfile << "中文名称：" << L.elem[i].name << endl;
		outfile << "英文名称：" << L.elem[i].sname << endl;
		outfile << "养生功效：" << L.elem[i].health << endl;
		outfile << "营养与功效：" << L.elem[i].nutrition << endl;
		outfile << "专家提醒： " << L.elem[i].expert << endl;
		outfile << "相关链接：" << L.elem[i].link << endl;
		outfile << "养生保健食谱：" << endl;
		for (int j = 0; j < L.elem[i].recipe_size; ++j) {
			outfile << L.elem[i].recipe[j] << endl;
		}
		outfile << "食疗验方：" << endl;
		for (int j = 0; j < L.elem[i].therapy_size; ++j) {
			outfile << L.elem[i].therapy[j] << endl;
		}
		if (i != L.length - 1)
			outfile << "#" << endl;
	}

	outfile.close();
}

Food* DeleteFood(SqList& L, char* name) {
	// 根据中文名称删除指定食材信息
	// 如果删除成功，返回该食材的信息，否则，返回NULL
	string strname = name;
	string strname2 = "中文名称：";
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
	// 输出食材信息
	cout << food->name << endl;
	cout << food->sname << endl;
	cout << food->health << endl;
	cout << food->nutrition << endl;
	cout << food->expert << endl;
	cout << food->link << endl;
	for (int j = 0; j < food->recipe_size; ++j) {
		cout << food->recipe[j] << endl;
	}
	cout << "食疗验方：" << endl;
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
			cout << "删除失败" << endl;
	}
	else {
		cout << "删除失败" << endl;
	}
	FreeList(L);
	return 0;
}