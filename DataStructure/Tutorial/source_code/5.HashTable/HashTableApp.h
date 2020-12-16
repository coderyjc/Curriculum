#pragma once
#include"ListNode.h"

class HashTableApp {
public:
	HashTableApp();

	// ��ȡ�����ļ�
	void readFile();

	// ������������
	void enterName();
	
	// ���ϣ���в���ֵ
	void insert(int posi, string data);

	// �����ϣ��
	int hashCode(string str);

	// �鿴��ϣ��
	void layout();

	// ����
	void find();

	// ������ѭ��
	void mainLoop();

private:

	string names[30];
	ListNode* hashTable = new ListNode[27];
};

