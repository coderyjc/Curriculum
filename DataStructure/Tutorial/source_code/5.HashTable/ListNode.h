#pragma once
#include<iostream>
using namespace std;

// ��ϣ��ڵ�
class ListNode {
public:
	ListNode() {
		this->data = "";
		this->next = NULL;
	}

	ListNode(string data, ListNode* next) {
		this->data = data;
		this->next = next;
	}

	ListNode* next;
	string data;
};