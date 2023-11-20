#include <iostream>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <ios>
#include <algorithm>
#define MAXSIZE 10000
using namespace std;

typedef struct Food {
    char name[100];		        // ��������
    char sname[100];	            // Ӣ������
    char health[10000];	        // ������Ч
    char nutrition[10000];      // Ӫ���빦Ч
    char expert[10000];	        // ר������
    char link[10000];	        // �������
    string recipe[30];	        // ��������ʳ��
    int recipe_size = 0;        // ʳ������
    string therapy[30];	        // ʳ���鷽
    int therapy_size = 0;       // �鷽����
} Food;
typedef struct {
    Food* elem;                 // ָ�������ָ��
    int length;                 // ����ĳ���
} SqList;

void InitList(SqList& L) {
    L.elem = new Food[MAXSIZE];
    L.length = 0;
}

void FreeList(SqList& L) {
    delete[] L.elem;
    L.length = 0;
}

void ReadFile(SqList& L, string filename) {
    // ���ļ��ж�ȡʳ����Ϣ�����䰴˳�����L.elemָ��������У�L.elem[0]�����ڱ���Ԫ��������
    InitList(L);

    string line; int count = 0;
    ifstream inputFile(filename);

    while (getline(inputFile, line)) {
        if (line == "") return;

        if (line == "#") {
            count = 0;
            L.length += 1;
            continue;
        }

        if (line.substr(0, 12) == "��������") {
            string::iterator head = line.begin() + 15;
            string::iterator tail = line.end();
            std::copy(head, tail, L.elem[L.length].name);
            count += 1;
        }
        else if (line.substr(0, 12) == "Ӣ������") {
            string::iterator head = line.begin() + 15;
            string::iterator tail = line.end();
            std::copy(head, tail, L.elem[L.length].sname);
            count += 1;
        }
        else if (line.substr(0, 12) == "������Ч") {
            string::iterator head = line.begin() + 15;
            string::iterator tail = line.end();
            std::copy(head, tail, L.elem[L.length].health);
            count += 1;
        }
        else if (line.substr(0, 15) == "Ӫ���빦Ч") {
            string::iterator head = line.begin() + 18;
            string::iterator tail = line.end();
            std::copy(head, tail, L.elem[L.length].nutrition);
            count += 1;
        }
        else if (line.substr(0, 12) == "ר������") {
            string::iterator head = line.begin() + 15;
            string::iterator tail = line.end();
            std::copy(head, tail, L.elem[L.length].expert);
            count += 1;
        }
        else if (line.substr(0, 12) == "�������") {
            string::iterator head = line.begin() + 15;
            string::iterator tail = line.end();
            std::copy(head, tail, L.elem[L.length].link);
            count += 1;
        }
        else if (line.substr(0, 18) == "��������ʳ��" || line.substr(0, 12) == "ʳ���鷽") {
            count += 1;
            continue;
        }

        if (count == 7) {
            auto head = line.begin();
            auto tail = line.end();
            L.elem[L.length].recipe[L.elem[L.length].recipe_size] = string(head, tail);
            L.elem[L.length].recipe_size += 1;
        }
        else if (count == 8) {
            string::iterator head = line.begin();
            string::iterator tail = line.end();
            L.elem[L.length].therapy[L.elem[L.length].therapy_size] = string(head, tail);
            L.elem[L.length].therapy_size += 1;
        }
    }

    L.length += 1;
}

void copy(Food* dst, Food* src) {
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

void MSDSort(SqList& L, SqList& L2, int l, int r, int d) {
    if (r <= l) return;

    int count[256 + 2]; for (int i = 0; i != 258; i++) count[i] = 0;

    for (int i = l; i <= r; i++)
        count[L.elem[i].sname[d] + 2] += 1;

    for (int i = 0; i < 256 + 1; i++)
        count[i + 1] += count[i];

    for (int i = l; i <= r; i++)
        L2.elem[count[L.elem[i].sname[d] + 1]++] = L.elem[i];

    for (int i = l; i <= r; i++)
        L.elem[i] = L2.elem[i - l];

    for (int i = 0; i != 256; i++)
        MSDSort(L, L2, l + count[i], l + count[i + 1] - 1, d + 1);
}


int main() {
	SqList L, L2;
	InitList(L);
	ReadFile(L, "food.txt");
	InitList(L2);
	MSDSort(L, L2, 0, L.length - 1, 0);
	for (int i = 0; i < L.length; i++)
		cout << L.elem[i].sname << endl;
	FreeList(L);
	FreeList(L2);
	return 0;
}