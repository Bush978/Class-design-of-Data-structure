#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
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
		for(int i = 0; i < 30; i++)
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
	// 比较函数，按照食材英文名称从小到大排序
	//11
	char *s1 = new char[30], *s2 = new char[30];
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
	//Food f2的值给Food f1
	strcpy(f1.name, f2.name);
	//f1清空
	for(int i = 0; i<strlen(f1.sname);i++)
		f1.sname[i] = '/0';
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



void InsertSort(SqList& L, int& kcn, int& rmn) {
	L.elem[L.length].sname;
	// 未定义操作，可能是拼写错误或者无用语句

	for (int i = 0; i < 30; i++)
		L.elem[L.length].sname[i] = '\0';
	// 初始化字符串数组为'\0'

	for (int i = L.length; i >= 1; i--)
		Lcopy(L.elem[i - 1], L.elem[i]);
	// 将顺序表元素依次向后移动一位

	// 直接插入排序
	for (int i = L.length - 1; i >= 1; i--) {
		// 从最后一个元素开始向前遍历，进行直接插入排序
		if (i >= 0 && cmp(L.elem[i], L.elem[i + 1]) == 1) {
			// 如果当前元素大于下一个元素，需要进行插入排序
			Lcopy(L.elem[i], L.elem[0]);
			// 将当前元素备份到哨兵节点
			Lcopy(L.elem[i + 1], L.elem[i]);
			// 将下一个元素复制到当前位置，记录移动次数+2
			rmn += 2;
			int j;
			for (j = i + 2; j <= L.length && cmp(L.elem[j], L.elem[0]) == -1; j++) {
				// 在有序子表中找到插入位置
				kcn++;
				// 关键字比较次数+1
				Lcopy(L.elem[j], L.elem[j - 1]);
				// 将元素后移一位，记录移动次数+1
				rmn++;
			}
			kcn++;
			rmn++;
			Lcopy(L.elem[0], L.elem[j - 1]);
			// 将备份的元素插入到正确位置
		}
		kcn++;
		// 关键字比较次数+1
	}


	// 输出排序后的食材英文名称、KCN和RMN
	for (int k = 1; k <= L.length; k++)
		cout << L.elem[k].sname << endl;
	cout << "总的关键字比较次数KCN为：" << kcn << endl;
	cout << "总的记录移动次数RMN为：" << rmn << endl;
}


int main() {
	SqList L;
	InitList(L);
	string filename = "food.txt";
	ReadFile(L, filename);
	int kcn = 0;
	int rmn = 0;
	InsertSort(L, kcn, rmn);
	FreeList(L);
	return 0;
}