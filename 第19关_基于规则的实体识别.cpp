#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
int length = strlen("。");

int BFSearch(const char *S, const char *T, int pos)
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

bool EntityRecognition(char* S, char* T) {
	// S为非结构化文本，T为规则
	// 如果匹配成功返回true，否则返回false
	// 输出所有匹配到的实体
	int i = 0; 
	int len = strlen(T);
	string s1 = "", s2 = "";
	i = 0;
	while (i < strlen(T)) {
		if (T[i] != '*')
			s1 += T[i++];
		else break;
	}

	while (i < strlen(T)) {
		if (T[i] == '*') i++;
		else s2 += T[i++];
	}

	i = 0;
	int number = 0;
	while (i < strlen(S))
	{
		if (T[i] == '*') number++;
			i++;
	}

	int judge = 0;
	char *p1 = new char[100];
	char *p2 = new char[100];
	for (i = 0; i < 100; i++) {
		p1[i] = '\0';
		p2[i] = '\0';
	}
	for(i = 0; i<s1.length(); i++)
		p1[i] = s1[i];
	//cout<< p1 << endl;
	for(i = 0; i<s2.length(); i++)
		p2[i] = s2[i];
	//cout << p2 << endl;
	if(BFSearch(S, p1, 0) != -1) judge++;
	if(BFSearch(S, p2, 0) != -1) judge++;
	//cout << judge << endl;
	if (judge == 2)
	{
		int x = 0, judge = 1;
		if (s2.length() == 0) {
			while (x < strlen(S)) {
				if (BFSearch(S, p1, x) == x)
				{
					//cout<<BFSearch(S, p1, x)<<endl;
					int pos = BFSearch(S, p1, x);
					i = min(BFSearch(S, "。", pos), BFSearch(S, "、", pos));
					i = min(BFSearch(S, "，", pos), i);
					if(i - pos - s1.length() < number *length)
						i = pos + s1.length() + number* length;
					for (int j = pos + s1.length(); j < i; j++)
						cout << S[j];
					cout << endl;
					x = x + s1.length();
				}
				else x++;
			}
		}
		else if (s1.length() == 0)
		{
			char *p = new char[10000];
			for (i = 0; i < 10000; i++) 
				p[i] = '\0';
			while (x < strlen(S)) {
				if (BFSearch(S, p2, x) == x)
				{
					//cout<<BFSearch(S, p1, x)<<endl;
					for(i = 0; i< BFSearch(S,p2,x); i++)
						p[i] = S[i];
					//cout << p << endl;
					int m = 0, finalpos;
					int pos = BFSearch(S, p2, x);
					while (m < strlen(p)) {
						if (BFSearch(S, "。", m) == m || BFSearch(S, "、", m) == m || BFSearch(S, "，", m) == m)
							finalpos = m;
						m++;
					}
					if(pos - finalpos > number * length)
						finalpos = pos - (number+1) * length;
					for (int j = finalpos + length; j < pos; j++)
						cout << p[j];
					cout << endl;
					x = x + s2.length();
				}
				else x++;
			}
		}
		else {
			int pos = BFSearch(S, p1, x);
			for (int j = pos + s1.length(); j < BFSearch(S,p2,x); j++)
				cout << S[j];
			cout << endl;
		}
		return true;
	}
	else return false;
}


int main() {
	char* keyword = new char[100];
	char text[10000];
	cin >> keyword >> text;
	if (!EntityRecognition(text, keyword))
		cout << "无匹配" << endl;;
	return 0;
}