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

void SaveFile(SqList& L, string filename) {
	ofstream outfile(filename);
	if (!outfile) {
		cout << "文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < L.length; ++i) {
		outfile << L.elem[i].name << endl;
		outfile <<  L.elem[i].sname << endl;
		outfile << L.elem[i].health << endl;
		outfile <<  L.elem[i].nutrition << endl;
		outfile << L.elem[i].expert << endl;
		outfile <<  L.elem[i].link << endl;
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
bool ModifyFood(SqList& L, int type, char* name, string lines[], int n) {
	// 食材信息修改，如果type是0，则修改养生保健食谱，否则修改食疗验方信息
	// 如果修改成功，返回true，否则，返回false
	Food* food = new Food;
	string strname = name;
	string strname2 = "中文名称：";
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
	// 获取修改后的食材信息
	ReadFile(L, allfilename);
	string strname = name;
	string strname2 = "中文名称：";
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
	// 输出食材信息
	cout << food->name << endl;
	cout << food->sname << endl;
	cout << food->health << endl;
	cout << food->nutrition << endl;
	cout << food->expert << endl;
	cout << food->link << endl;
	cout << "养生保健食谱：" << endl;
	for (int j = 0; j < food->recipe_size; ++j) {
		cout << food->recipe[j] << endl;
	}
	cout << "食疗验方：" << endl;
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
			cout << "修改失败" << endl;
	}
	else {
		cout << "修改失败" << endl;
	}
	FreeList(L);
	return 0;
}