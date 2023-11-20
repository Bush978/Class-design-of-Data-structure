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
typedef struct LNode {
	Food data;			        // 食材信息
	struct LNode* next;         // 指向下一级结点
} LNode, * LinkList;
int len = strlen("中文名称：");
int sumcount = 0;

void InitList(LinkList* H) {
	// 链表初始化
	for (int i = 0; i < m; i++) {
		H[i] = new LNode;
		H[i]->next = nullptr;
	}
}

int Hash(char* sname) {
	// 实现散列函数：字符串sname中各字符的下标（从0开始）的平方乘以字符对应的ASCII码值，相加后与199取余
	int sum = 0;
	for (int i = 0; i < strlen(sname); i++) {
		sum += ((i) * (i) * int(sname[i]));
	}
	return sum % 199;
}

void ListInsert(LinkList* H, Food f, int& sumCmp) {
	// 往散列表中插入新的食材f
	// 在插入的过程中统计总的比较次数sumCmp

	sumCmp++;
	// 插入次数递增

	int index = Hash(f.sname);
	// 计算食物名称的哈希值，确定插入的位置

	LNode* p = H[index];
	// 获取对应位置的链表头指针

	while (p->next != nullptr) {
		// 遍历链表直到尾部
		p = p->next;
		sumCmp++;
		// 插入次数和总的比较次数递增
	}

	LNode* q = new LNode;
	// 创建新的节点
	q->data = f;
	q->next = nullptr;
	// 初始化新节点的数据和指针

	p->next = q;
	// 将新节点插入到链表尾部
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

int ReadFile(LinkList* H, int& sumCmp, string filename) {
	// 读取文件，调用ListInsert函数将每条食材数据插入散列表
	// 返回食材数据的总数
	ifstream file(filename);
	string line;
	//sumcount += 3;
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
		for (int i = 0; i < 30 - len; i++)
			f.sname[i] = f.sname[i + len];
		//cout << f.sname << endl;
		ListInsert(H, f, sumCmp);
		sumcount++;
	}

	infile.close();

}

int SearchHL(LinkList* H, char* key) {
	// 在散列表HT中查找食材英文名称等于key的元素
	// 若找到，则返回散列表的单元标号，否则返回-1

	int hashVal = Hash(key);
	// 计算目标食物名称的哈希值

	LinkList p = H[hashVal]->next;
	// 获取对应位置的链表头指针

	while (p != nullptr) {
		// 遍历链表
		if (strcmp(p->data.sname, key) == 0) {
			// 如果找到目标食物名称，返回散列表的单元标号
			return hashVal;
		}
		p = p->next;
		// 移动到下一个节点
	}

	return -1;
	// 若遍历完仍未找到目标食物名称，则返回-1
}

double GetASL(int sumCmp, int count) {
	// 返回基于链地址法的散列查找的ASL

	count = sumcount;
	// 更新count为全局变量sumcount的值

	return (double)sumCmp / count;
	// 返回平均查找长度（ASL）
}


void Print(LNode* p, char* sname) {
	// 输出食材信息
	// 若食材信息中不包含某项内容，则输出“无”
	cout << p->data.name << endl;

	cout << "英文名称：" << p->data.sname << endl;
	cout << p->data.health << endl;
	cout << p->data.nutrition << endl;
	cout << p->data.expert << endl;
	cout << p->data.link << endl;
	if (p->data.recipe_size != 0)
		cout << "养生保健食谱：" << endl;
	for (int i = 0; i < p->data.recipe_size; i++)
		cout << p->data.recipe[i] << endl;
	if (p->data.therapy_size != 0)
		cout << "食疗验方：" << endl;
	for (int i = 0; i < p->data.therapy_size; i++)
		cout << p->data.therapy[i] << endl;
}

int main() {
	LinkList H[m];
	InitList(H);
	string filename = "food.txt";
	int count = 0;	// 记录食材数据的总数
	int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
	count = ReadFile(H, sumCmp, filename);
	char sname[100]; // 输入要查找的食材英文名称
	cin.getline(sname, 100);
	int pos = SearchHL(H, sname);
	if (pos != -1) {
		LinkList p = H[pos]->next; // 查找成功，将p指向单链表头结点
		Print(p, sname);
		double ASL = GetASL(sumCmp, count);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else {
		cout << "查找失败" << endl;
	}
	return 0;
}