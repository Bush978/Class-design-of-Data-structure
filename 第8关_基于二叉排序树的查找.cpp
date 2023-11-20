#include <bits/stdc++.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#define MAXSIZE 10000
using namespace std;
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
typedef struct BSTNode {
	Food data;				    // 食材信息
	struct BSTNode* lchild;     // 左孩子指针
	struct BSTNode* rchild;     // 右孩子指针
} BSTNode, * BSTree;
Food food[MAXSIZE];

void InitBSTree(BSTree& T) {
	// 二叉排序树初始化
	T = nullptr;
}

int cmp(char* sname1, char* sname2) {
	// 比较函数，按照食材英文名称从小到大排序
	//11
	string s1 = "", s2 = "";
	for (int i = 10; i < strlen(sname1); i++)
		s1 += tolower(sname1[i]);
	for (int i = 10; i < strlen(sname2); i++)
		s2 += tolower(sname2[i]);
	if (s1 < s2)
		return -1;
	else if (s1 > s2)
		return 1;
	else return 0;
}

void copy(Food* dst, Food* src) {
	//src给dst
	strcpy(dst->name, src->name);
	strcpy(dst->sname, src->sname);
	strcpy(dst->health, src->health);
	strcpy(dst->nutrition, src->nutrition);
	strcpy(dst->expert, src->expert);
	strcpy(dst->link, src->link);

	dst->recipe_size = src->recipe_size;
	dst->therapy_size = src->therapy_size;

	for (int i = 0; i != src->recipe_size; i++)
		dst->recipe[i] = string(src->recipe[i].begin(), src->recipe[i].end());
	for (int i = 0; i != src->therapy_size; i++)
		dst->therapy[i] = string(src->therapy[i].begin(), src->therapy[i].end());
}


BSTree InsertBST(BSTree& T, Food e) {
	// 当二叉排序树T中不存在关键字等于e.sname的数据元素时，则插入该元素

	if (T == nullptr) {
		// 如果当前节点为空，表示找到了插入位置
		BSTree newnode = new BSTNode;
		// 创建一个新节点

		copy(&newnode->data, &e);
		// 复制元素数据到新节点

		newnode->lchild = nullptr;
		newnode->rchild = nullptr;
		// 初始化新节点的左右子树为空

		return newnode;
		// 返回新节点作为插入的结果
	}

	if (strcmp(e.sname, T->data.sname) < 0) {
		// 如果待插入元素关键字小于当前节点关键字
		T->lchild = InsertBST(T->lchild, e);
		// 递归插入到左子树
	}
	else if (strcmp(e.sname, T->data.sname) > 0) {
		// 如果待插入元素关键字大于当前节点关键字
		T->rchild = InsertBST(T->rchild, e);
		// 递归插入到右子树
	}

	return T;
	// 返回当前节点（未发生插入）
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

int ReadFile(BSTree& T, string filename) {
	// 读取文件，调用InsertBST函数将每个食材数据插入二叉排序树
	// 返回食材的总数
	ifstream infile(filename);
	if (!infile) {
		cout << "文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	BSTree current = T, head = nullptr;
	int n = 0;
	while (!infile.eof()) {
		Food f;
		ReadFood(f, infile);
		food[n] = f;
		n++;
		T = InsertBST(T, f);
		//		cout<<T->data.name<<endl;
	}
	if (T == nullptr)
		cout << "空树" << endl;
	infile.close();
	return n;
}

void Print(BSTNode* T) {
	// 输出食材信息
	cout << T->data.name << endl;
	cout << T->data.sname << endl;
	cout << T->data.health << endl;
	cout << T->data.nutrition << endl;
	cout << T->data.expert << endl;
	cout << T->data.link << endl;
	if (T->data.recipe_size != 0)
		cout << "养生保健食谱：" << endl;
	for (int i = 0; i < T->data.recipe_size; i++)
		cout << T->data.recipe[i] << endl;
	if (T->data.therapy_size != 0)
		cout << "食疗验方：" << endl;
	for (int i = 0; i < T->data.therapy_size; i++)
		cout << T->data.therapy[i] << endl;
}


BSTNode* SearchBST(BSTree& T, char* sname) {
    // 查找对应食材

    string s = sname;
    // 将输入的char数组转换为string类型
    string s1 = "英文名称：";
    s = s1 + s;
    // 在食材名称前加上"英文名称："，组成完整的字符串

    char s2[100] = { '\0' };
    // 初始化char数组

    for (int i = 0; i < s.length(); i++)
        s2[i] = s[i];
    // 将string类型的字符串复制到char数组

    if (T == nullptr || cmp(T->data.sname, s2) == 0) {
        // 如果当前节点为空或者节点关键字与目标字符串相等，返回当前节点
        return T;
    }

    if (cmp(s2, T->data.sname) < 0) {
        // 如果目标字符串小于当前节点关键字，递归在左子树中查找
        return SearchBST(T->lchild, sname);
    }
    else {
        // 如果目标字符串大于当前节点关键字，递归在右子树中查找
        return SearchBST(T->rchild, sname);
    }
}

int GetSumCmp(BSTree T, int sumCmp) {
	// 统计查找成功时的总比较次数

	int left = 0, right = 0, level = 1;
	// 初始化左右边界和层级

	BSTNode* queue[10000];
	// 定义一个队列用于层序遍历二叉搜索树

	queue[0] = T;
	// 初始化队列，根节点入队

	while (right >= left) {
		// 当队列不为空时，执行以下循环

		int currentwidth = right - left + 1;
		// 当前层的节点数

		sumCmp += level * currentwidth;
		// 更新总比较次数

		int constant = right, i = left;
		// 记录当前层节点数的常量，初始化遍历变量

		while (i <= constant) {
			// 层序遍历当前层的节点

			BSTNode* node = queue[left++];
			// 出队一个节点

			if (node->lchild != NULL)
				// 如果左子树不为空，左子树入队
				queue[++right] = node->lchild;

			if (node->rchild != NULL)
				// 如果右子树不为空，右子树入队
				queue[++right] = node->rchild;

			i++;
		}

		level++;
		// 层级递增
	}

	return sumCmp;
	// 返回总比较次数
}

double GetASL(BSTree& T, int count) {
	// 计算基于二叉搜索树的平均搜索长度（ASL）

	double addition = GetSumCmp(T, 0);
	// 调用GetSumCmp函数获取总比较次数

	return addition / count;
	// 返回平均搜索长度
}


int main() {
	BSTree T = NULL;
	InitBSTree(T);
	int count = 0;
	string originFilename = "food.txt";
	count = ReadFile(T, originFilename);
	char sname[100];
	cin.getline(sname, 100);
	BSTNode* t = SearchBST(T, sname);
	if (t != NULL) {
		Print(t);
		double ASL = GetASL(T, count);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else
		cout << "查找失败" << endl;
	return 0;
}