#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
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
int len = strlen("中文名称：");

void InitList(SqList& L) {
	// 使用动态内存分配new进行初始化
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void FreeList(SqList& L) {
	// 释放内存
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
		else if (line == "养生保健食谱：") {
			while (getline(infile, line)) {
				if (line == "食疗验方：")
					break;
				else if (line == "#") return;
				f.recipe[i++] = line;
			}
		}
		else if (line == "食疗验方: ") {
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
		cout << "文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}

	while (!infile.eof()) {
		Food f;
		for (int i = 0; i < 100; i++)
			f.sname[i] = '\0';
		ReadFood(f, infile);
		for (int i = 0; i < 100 - len; i++)
			f.sname[i] = f.sname[i + len];
		//cout << f.sname << endl;
		L.elem[L.length++] = f;
	}

	infile.close();
}


int cmp(Food a, Food b) {
	// 比较函数，按照食材英文名称从小到大排序
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
	//将左边的值给到右边
	strcpy(f1.name, f2.name);
	//f1清空
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

int Partition(SqList& L, int low, int high, int& kcn, int& rmn)
{
	Lcopy(L.elem[low], L.elem[0]);
	rmn++;
	while (low < high)
	{
		while (low < high && cmp(L.elem[high], L.elem[0]) == 1) {
			high--;
			kcn++;
			if (low < high && cmp(L.elem[high], L.elem[0]) != 1)kcn++;
		}
		Lcopy(L.elem[high], L.elem[low]);
		rmn++;
		while (low < high && cmp(L.elem[low], L.elem[0]) == -1) {
			low++;
			kcn++;
			if(low < high && cmp(L.elem[high], L.elem[0]) != -1)kcn++;
		}
		Lcopy(L.elem[low], L.elem[high]);
		rmn++;
	}
	Lcopy(L.elem[0], L.elem[low]);
	rmn++;
	return low;
}

void QSort(SqList& L, int low, int high, int& kcn, int &rmn)
{
	if (low < high)
	{
		int pivotloc = Partition(L, low, high, kcn, rmn);
		QSort(L, low, pivotloc - 1, kcn, rmn);
		QSort(L, pivotloc + 1, high, kcn, rmn);
	}
}


void QuickSort(SqList& L) {
	// 对顺序表做快速排序
	// 输出排序后的食材英文名称、KCN和RMN
	int kcn = 0, rmn = 0;
	for (int i = L.length; i >= 1; i--)
		Lcopy(L.elem[i - 1], L.elem[i]);
	QSort(L, 1, L.length, kcn, rmn);
	for (int k = 1; k <= L.length; k++)
		cout << L.elem[k].sname << endl;
	cout << "总的关键字比较次数KCN为：" << kcn << endl;
	cout << "总的记录移动次数RMN为：" << rmn << endl;
}

int main() {
	SqList L;
	InitList(L);
	ReadFile(L, "food.txt");
	QuickSort(L);
	return 0;
}