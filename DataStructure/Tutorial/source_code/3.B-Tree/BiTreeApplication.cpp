#include "BiTreeApplication.h"
#include<iostream>
#include<string>
using namespace std;

BiTreeApplication::BiTreeApplication() {
	this->huffTree = new HuffNode[100](); // ��ʼ����Ϊ100��
	this->nodeCount = 0;
	this->maxLength = 0;
	this->hasConstruct = 0;
}

BiTreeApplication::~BiTreeApplication() {
	if (this->huffTree) {
		delete this->huffTree;
	}
}

void BiTreeApplication::init() {
	cout << "----------------\n���ڳ�ʼ��������\n----------------" << endl;
	// enter chars and its weight;
	cout << "�����ַ�����Ȩֵ���м��Կո������EOF �������" << endl;

	char tempChar;
	int tempWeight;
	for (this->nodeCount = 1; cin >> tempChar >> tempWeight; nodeCount++) {
		this->huffTree[nodeCount].data = tempChar;
		this->huffTree[nodeCount].weight = tempWeight;
	}
	this->nodeCount--; //��ȥ��ѭ����ʱ���������Ǹ�
	this->maxLength = this->nodeCount * 2 - 1;

	cout << "----------------\n��ʾ\n\n������ĸ����ɹ�\n----------------" << endl;
	system("pause");
	system("cls");
	cin.clear();
}

void BiTreeApplication::constructHuffTree() {
	if (this->maxLength <= 0) {
		cout << "---------------------------\n��ʾ��\n\n��ĸ����δ���룬��ִ��ѡ��1\n---------------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "���ڹ���������..." << endl;
	for (int i = ++this->nodeCount; i <= this->maxLength; i++) {
		// ��s1��s2��ֵΪ���intֵ�������
		int s1 = 0, s2 = 0;
		this->selectNode(s1, i - 1, s2);
		this->huffTree[s1].parent = i;
		this->huffTree[s2].parent = i;
		this->huffTree[i].lch = s1;
		this->huffTree[i].rch = s2;
		this->huffTree[i].weight = this->huffTree[s1].weight + this->huffTree[s2].weight;
	}
	cout << "--------------\n��ʾ��\n\n�������������\n--------------" << endl;
	system("pause");
	system("cls");
	this->hasConstruct = 1;
}

void BiTreeApplication::encoding() {
	if (!this->hasConstruct) {
		cout << "---------------------------\n��ʾ��\n\n��������δ����, ��ִ��ѡ��2\n---------------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "�����ַ�(�����ո�): ";
	string str;
	cin.clear();
	cin >> str;
	cout << "\n����������Ϊ :" << endl;
	for (int i = 0; i < str.length(); i++) {
		// ��������Ѱ�����ݽڵ�
		string tempCode = "";
		int flag = 0; // ��û���ҵ������ĸ���ڵĽڵ�
		for (int j = 1; j < this->nodeCount; j++) {
			if (this->huffTree[j].data == str[i]) {
				// show 
				flag = 1;
				int tempNumber = j;
				int parent = this->huffTree[j].parent;
				while (parent != 0) {
					// left child is the node 
					if (this->huffTree[parent].lch == tempNumber) tempCode += "0";
					if (this->huffTree[parent].rch == tempNumber) tempCode += "1";
					tempNumber = parent;
					parent = this->huffTree[parent].parent;
				}
				//cout << tempCode;
				break;
			}
		}
		// ������û�ҵ�����ڵ�
		if (!flag) {
			cout << "\n\n���棺\n\nδ�ҵ��ڵ�" << str[i] << " ���򼴽�������һ��\n" << endl;
			system("pause");
			system("cls");
			return;
		}
		// ��ת10����Ȼ�����
		reverse(tempCode.begin(), tempCode.end());
		cout << tempCode;
	}
	cout << endl;
	system("pause");
	system("cls");
}

void BiTreeApplication::decoding() {
	if (!this->hasConstruct) {
		cout << "---------------------------\n��ʾ��\n\n��������δ����, ��ִ��ѡ��2\n---------------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "\n����Huffman code��";
	string source;
	cin >> source;
	cout << "\n������Ϊ ��";

	int ptr = this->maxLength;
	for (int i = 0; i <= source.length(); i++) {
		if (this->huffTree[ptr].lch != 0 && this->huffTree[ptr].rch != 0) {
			if (source[i] == '0') {
				ptr = this->huffTree[ptr].lch;
			} else if (source[i] == '1') {
				ptr = this->huffTree[ptr].rch;
			} else {
				cout << source[i];
			}
		} else {
			cout << this->huffTree[ptr].data;
			ptr = this->maxLength;
			i--; // ����
		}
	}
	cout << endl;
	system("pause");
	system("cls");
}

void BiTreeApplication::mainBody() {
	int choose = 0;
	do {
		cout << "-----------------\n������Ӧ�ò���\n-----------------\n1. ��ʼ��������" << endl
			<< "2. ���ƹ�����" << endl
			<< "3. Ϊ�ַ�����" << endl
			<< "4. ���������" << endl
			<< "0. �˳�ϵͳ\n-----------------" << endl
			<< "����ѡ�� : " ;
		cin >> choose;
		switch (choose) {
			case 1: this->init(); break;
			case 2:	this->constructHuffTree(); break;
			case 3: this->encoding(); break;
			case 4:	this->decoding(); break;
			default: return;
		}
	} while (choose);
}

/*
* s1��s2 are initialized with 0
* s1 and s2 should be a index, not a value.
* s1 is the smallest one , and s2 is the second smallest one
*/
void BiTreeApplication::selectNode(int& s1,int limit, int& s2) {
	
	int number1 = INT_MAX;
	int number2 = INT_MAX;
	for (int i = 1; i <= limit; i++) {
		// we can ensure that parent is not 0
		// find the two smallest node directly
		if (this->huffTree[i].parent != 0) continue;
		int temp = this->huffTree[i].weight;
		if (temp < number2) {
			if (temp > number1) {
				// copy to 2 directly
				number2 = temp;
				s2 = i;
			} else {
				// copy to 1, and 1 copy to 2
				number2 = number1;
				number1 = temp;
				s2 = s1;
				s1 = i;
			}
		}
	}
}
