#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
typedef struct Food{
	string relation;    //��ϵ����
	string rule[10];    //��������
} Relation;
int length = strlen("��");

int BFSearch(const char* S, const char* T, int pos)
{
	// SΪ�ǽṹ���ı���TΪ����
	// ���ƥ��ɹ�����true�����򷵻�false
	// �������ƥ�䵽��ʵ��
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
	// ���ʵ��֮����ڹ�ϵ����true�����򷵻�false
	// ������д��ڵ���Ԫ��
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
	r[0].relation = "��Ч";
	r[0].rule[0] = "A����B";
	r[0].rule[1] = "A��ЧΪB";
	r[0].rule[2] = "A������B";
	r[0].rule[3] = "A������B";
	r[0].rule[4] = "A����B";

	r[1].relation = "����";
	r[1].rule[0] = "A�ɷ���B";
	r[1].rule[1] = "A�߱��˷���B";
	r[1].rule[2] = "A��������B";
	r[1].rule[3] = "A������Ԥ��B";

	r[2].relation = "��ζ";
	r[2].rule[0] = "A����ζ��B";
	r[2].rule[1] = "A����ζΪB";

	r[3].relation = "����";
	r[3].rule[0] = "A����B";
	r[3].rule[1] = "A��Ҫ��B";
	r[3].rule[2] = "A�ֽ��B";
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
		cout << "ʵ��֮�䲻���ڹ�ϵ" << endl;
	return 0;
}