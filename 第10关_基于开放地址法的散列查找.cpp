#include <bits/stdc++.h>
#define m 200
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
	// 开放地址法散列表的存储表示
	Food* key;
	int length;
} HashTable;
string  allfilename;
int len = strlen("中文名称：");
int sumcount = 0;

void InitHT(HashTable& HT) {
	// 散列表初始化
	HT.length = m;
	HT.key = new Food[m];
	for (int i = 0; i < m; i++) {
		HT.key[i] = Food(); 
	}
}

int Hash(char* sname) {
	// 实现散列函数：字符串sname中各字符的下标（从0开始）的平方乘以字符对应的ASCII码值，相加后与199取余
	int sum = 0;
	for (int i = 0; i < strlen(sname); i++)
	{
		sum += ((i) * (i) * int(sname[i]));
	}
	return sum % 199;
}

void HTInsert(HashTable& HT, Food f, int& sumCmp) {
	// 往散列表中插入新的食材f
	// 在插入的过程中统计总的比较次数sumCmp

	int hashVal = Hash(f.sname);
	// 计算食物名称的哈希值

	int i = 0;
	sumCmp += 1;
	// 初始化插入次数，并累加总的比较次数

	while (HT.key[(hashVal + i) % m].sname[0] != '\0') {
		// 当散列表位置不为空时，发生冲突
		i++;
		sumCmp++;
		// 插入次数和总的比较次数递增
	}

	HT.key[(hashVal + i) % m] = f;
	// 将食物信息插入到空的散列表位置
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

void ReadFile(HashTable& HT, int& sumCmp, string filename) {
	// 读取文件，调用HTInsert函数将每条食材数据插入散列表
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
	// 输出食材信息
	cout << HT.key[pos].name << endl;
	cout << "英文名称："<<HT.key[pos].sname << endl;
	cout << HT.key[pos].health << endl;
	cout << HT.key[pos].nutrition << endl;
	cout << HT.key[pos].expert << endl;
	cout << HT.key[pos].link << endl;
	if(HT.key[pos].recipe_size != 0)
	cout << "养生保健食谱：" << endl;
	for (int i = 0; i < HT.key[pos].recipe_size; i++) {
		cout << HT.key[pos].recipe[i] << endl;
	}
	if (HT.key[pos].therapy_size != 0)
	cout << "食疗验方：" << endl;
	for (int i = 0; i < HT.key[pos].therapy_size; i++) {
		cout << HT.key[pos].therapy[i] << endl;
	}
}

int SearchHash(HashTable HT, char* key) {
	// 在散列表HT中查找食材英文名称等于key的元素
	// 若找到，则返回散列表的单元标号，否则返回-1

	int hashVal = Hash(key);
	// 计算目标食物名称的哈希值

	int i = 0;
	// 初始化查找次数

	while (HT.key[(hashVal + i) % m].sname[0] != '\0') {
		// 当散列表位置不为空时，进行查找
		if (strcmp(HT.key[(hashVal + i) % m].sname, key) == 0) {
			// 如果找到目标食物名称，返回散列表的单元标号
			return (hashVal + i) % m;
		}
		i++;
		// 未找到时，继续查找下一个位置
	}

	return -1;
	// 若遍历完仍未找到目标食物名称，则返回-1
}

double GetASL(HashTable HT, int sumCmp) {
	// 返回基于开放地址法的散列查找的ASL

	cout << sumCmp << endl;
	// 输出总的比较次数

	return (double)sumCmp / (double)sumcount;
	// 返回平均查找长度（ASL）
}


int main() {
	HashTable HT;
	InitHT(HT);
	string filename = "food.txt";
	int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
	ReadFile(HT, sumCmp, filename);
	char sname[100]; // 输入要查找的食材英文名称
	cin.getline(sname, 100);
	int pos = SearchHash(HT, sname);
	if (pos != -1) {
		Print(HT, pos);
		double ASL = GetASL(HT, sumCmp);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else {
		cout << "查找失败" << endl;
	}
	return 0;
}
