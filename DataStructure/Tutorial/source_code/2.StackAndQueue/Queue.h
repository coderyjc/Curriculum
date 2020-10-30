#pragma once
#include<iostream>
using namespace std;

#define NodePosi(T) QNode<T>*

template<class T>
class QNode {
public:
	T data;
	NodePosi(T) next;

public:

	QNode() {	}

	QNode(T data, NodePosi(T) next = nullptr) {
		this->data = data;
		this->next = next;
	}
};

template<class T>
class MyQueue {
public:

	MyQueue() {
		header = new QNode<T>();
		this->_size = 0;
		cout << "Q Constructor" << endl; //---------------debug
	}

	void push(T data); //��� - β��

	void pop(); //���� - ͷɾ

	bool empty(); //����Ԫ�ڵ�

	T front(); //��Ԫ�ڵ�

	int size(); //��ȡԪ�صĸ���

	void destory(); //���ٶ���

	void clear(); //��ն���

	void travser() {
		NodePosi(T) t = header->next;
		while (t) {
			cout << t->data << " ";
			t = t->next;
		}
	}
private:
	NodePosi(T) header;
	int _size;
};

template<class T>
void MyQueue<T>::push(T data) {
	NodePosi(T) t = this->header;
	while (t->next) t = t->next;
	NodePosi(T) p = new QNode<T>(data, nullptr);
	if (!p) exit(0);
	t->next = p;
	this->_size++;
}

template<class T>
void MyQueue<T>::pop() {
	if (empty()) {
		cout << "Empty List" << endl;
		exit(0);
	} else {
		NodePosi(T) t = header->next;
		header->next = header->next->next;
		delete t;
		this->_size;
	}
}

template<class T>
bool MyQueue<T>::empty() {
	return header->next == NULL;
}

template<class T>
T MyQueue<T>::front() {
	if (empty()) {
		cout << "Empty List" << endl;
		exit(0);
	}
	return header->next->data;
}

template<class T>
int MyQueue<T>::size() {
	return this->_size;
}

template<class T>
void MyQueue<T>::destory() {
	this->clear();
	delete header;
}

template<class T>
void MyQueue<T>::clear() {
	while (!empty()) this->pop();
}
