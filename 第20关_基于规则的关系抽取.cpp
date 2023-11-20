#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
typedef struct Food{
	string relation;    //关系名称
	string rule[10];    //规则数组
} Relation;
int length = strlen("。");

int BFSearch(const char* S, const char* T, int pos)
{
	// S为非结构化文本，T为规则
	// 如果匹配成功返回true，否则返回false
	// 输出所有匹配到的实体
	int i = pos, j = 0;
	int len = strlen(T);
	while (i < strlen(S)) {
		if (S[i] == T[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
		if (j == len)
			return i - j;
	}
	return -1;
}

bool RelationExtraction(char* text, char* entity1, char* entity2, Relation* r) {
	// 如果实体之间存在关系返回true，否则返回false
	// 输出所有存在的三元组
	int i = 0;
	int pos1 = BFSearch(text, entity1, 0);
	int pos2 = BFSearch(text, entity2, 0);
	if (pos1 == -1 || pos2 == -1) return false;
	else {
		int startpoint;
		int endpoint = max(pos1, pos2);
		if(pos1 < pos2) startpoint = pos1 + strlen(entity1);
		else return false;
		char* temp = new char[100];
		for (i = 0; i < 100; i++)
			temp[i] = '\0';
		for (i = startpoint; i < endpoint; i++)
			temp[i - startpoint] = text[i];
		//cout << temp << endl;
		i = 0;
		while (i < 4) {
			int j = 0;
			if (i == 0)
			{
				while (j < 5)
				{
					r[i].rule[j].erase(0, 1);
					r[i].rule[j].erase(r[i].rule[j].length() - 1, 1);
					if (BFSearch(temp, r[i].rule[j].c_str(), 0) != -1)
					{
						cout << entity1 << "-" << r[i].relation << "-" << entity2 << endl;
						return true;
					}
					j++;
				}
			}
			else if (i == 1)
			{
				while (j < 4)
				{
					r[i].rule[j].erase(0, 1);
					r[i].rule[j].erase(r[i].rule[j].length() - 1, 1);
					if (BFSearch(temp, r[i].rule[j].c_str(), 0) != -1)
					{
						cout << entity1 << "-" << r[i].relation << "-" << entity2 << endl;
						return true;
					}
					j++;
				}
			}
			else if (i == 2)
			{
				while (j < 2)
				{
					r[i].rule[j].erase(0, 1);
					r[i].rule[j].erase(r[i].rule[j].length() - 1, 1);
					if (BFSearch(temp, r[i].rule[j].c_str(),0) == 0)
					{
						cout << entity1 << "-" << r[i].relation << "-" << entity2 << endl;
						return true;
					}
					j++;
				}

			}
			else if (i == 3)
			{
				while (j < 3)
				{
					r[i].rule[j].erase(0, 1);
					r[i].rule[j].erase(r[i].rule[j].length() - 1, 1);
					if (BFSearch(temp, r[i].rule[j].c_str(), 0) != -1)
					{
						cout << entity1 << "-" << r[i].relation << "-" << entity2 << endl;
						return true;
					}
					j++;
				}

			}
			i++;
		}
	}
	return false;
}

void InitRelation(Relation* r) {
	r[0].relation = "功效";
	r[0].rule[0] = "A具有B";
	r[0].rule[1] = "A功效为B";
	r[0].rule[2] = "A有利于B";
	r[0].rule[3] = "A有益于B";
	r[0].rule[4] = "A可以B";

	r[1].relation = "防治";
	r[1].rule[0] = "A可防治B";
	r[1].rule[1] = "A具备了防治B";
	r[1].rule[2] = "A可以治疗B";
	r[1].rule[3] = "A有利于预防B";

	r[2].relation = "性味";
	r[2].rule[0] = "A的性味是B";
	r[2].rule[1] = "A的性味为B";

	r[3].relation = "防治";
	r[3].rule[0] = "A包括B";
	r[3].rule[1] = "A主要有B";
	r[3].rule[2] = "A分解成B";
}

int main() {
	char* entity1 = new char[100];
	char* entity2 = new char[100];
	char text[10000];
	Relation* r = new Relation[10];;
	InitRelation(r);
	cin >> entity1;
	getchar();
	cin >> entity2;
	getchar();
	cin >> text;
	if (!RelationExtraction(text, entity1, entity2, r))
		cout << "实体之间不存在关系" << endl;
	return 0;
}