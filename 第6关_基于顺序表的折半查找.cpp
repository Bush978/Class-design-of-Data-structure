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
		outfile  << L.elem[i].sname << endl;
		outfile << L.elem[i].health << endl;
		outfile << L.elem[i].nutrition << endl;
		outfile << L.elem[i].expert << endl;
		outfile << L.elem[i].link << endl;
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

bool cmp(Food a, Food b) {
	// 比较函数，按照食材英文名称从小到大排序
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
	// 从小到大排序
	//冒泡排序
	for(int i = 0; i < L.length - 1; i++)
		for(int j = 0; j < L.length - i - 1; j++)
			if(!cmp(L.elem[j], L.elem[j + 1]))
				swap(L.elem[j], L.elem[j + 1]);
	SaveFile(L, "new_food.txt");
}

void Print(SqList& L, int pos) {
	// 输出食材信息
	cout << L.elem[pos].name << endl;
	cout << L.elem[pos].sname << endl;
	cout << L.elem[pos].health << endl;
	cout << L.elem[pos].nutrition << endl;
	cout << L.elem[pos].expert << endl;
	cout << L.elem[pos].link << endl;
	if(L.elem[pos].recipe_size != 0)
	cout << "养生保健食谱：" << endl;
	for (int i = 0; i < L.elem[pos].recipe_size; i++) {
		cout << L.elem[pos].recipe[i] << endl;
	}
	if(L.elem[pos].therapy_size != 0)
	cout << "食疗验方：" << endl;
	for (int i = 0; i < L.elem[pos].therapy_size; i++) {
		cout << L.elem[pos].therapy[i] << endl;
	}
}

int BinarySearch(SqList& L, char* sname) {
	// 在顺序表L中折半查找食材英文名称等于sname的数据元素
	// 若找到，则返回该元素在表中的下标，否则返回-1
	string s = sname;
	string s1 = "英文名称：";
	s = s1 + s;
	//string s转为char类型
	char s2[100] = {'\0'};
	for(int i =0; i < s.length(); i++)
		s2[i] = s[i];
	int low = 0, high = L.length - 1, mid;
	// 定义变量low表示搜索范围的起始位置，high表示搜索范围的结束位置，mid表示中间位置
	while (low <= high) {
		// 当搜索范围仍然有效时，执行以下循环
		mid = (low + high) / 2;
		// 计算当前搜索范围的中间位置
		if (strcmp(L.elem[mid].sname, s2) == 0)
			// 如果中间位置的元素与目标元素相等，返回中间位置
			return mid;
		else if (strcmp(L.elem[mid].sname, s2) < 0)
			// 如果中间位置的元素小于目标元素，调整搜索范围为右半部分
			low = mid + 1;
		else
			// 如果中间位置的元素大于目标元素，调整搜索范围为左半部分
			high = mid - 1;
	}
	// 当搜索范围无效时，表示目标元素不在数组中，返回-1

   return -1;
}



double GetASL(SqList& L) {
	// 返回基于顺序表的折半查找的ASL 
	// 返回基于顺序表的折半查找的平均搜索长度（ASL）

	double asl = 0;
	// 初始化平均搜索长度为0

	int total = 0, level = 0;
	// 初始化总节点数和层级

	for (int i = 0; total != L.length; i++) {
		// 循环直到遍历所有节点

		level = pow(2, i);
		// 计算当前层级的节点数

		total += level;
		// 更新总节点数

		if (total < L.length)
			// 如果总节点数未超过顺序表长度，累加平均搜索长度
			asl += (i + 1) * level;
		else {
			// 如果总节点数已经超过顺序表长度，调整总节点数为顺序表长度
			total = L.length;
			// 累加平均搜索长度，考虑超出部分
			asl += (i + 1) * (total - level + 1);
		}
	}

	return asl / total;
	// 返回平均搜索长度除以总节点数的结果
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
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else {
		cout << "查找失败" << endl;
	}
	FreeList(L);
	return 0;
}