#pragma once
#include<iostream>

using namespace std;

/*
	�������ͺ�   ��������    ռ�ÿռ�
	   1        С�γ�        1
	   2		�ͳ�			1.5
	   3		ʮ�ֿ���		 3
*/

class Car {
public:
	int type;
	string ID;
	int enTime;
	int waitTime;

	Car(string id, int type, int time) { 
		// ��ֱ�ӽ��복�⡿�ĳ��Ĺ��캯��
		this->ID = id;
		this->type = type;
		this->waitTime = time;
		this->enTime = time;
	}

	Car(int time, string id, int type) {
		// ���ڳ�����Ⱥ򡿵ĳ��Ĺ��캯��
		this->ID = id;
		this->type = type;
		this->waitTime = time;
		this->enTime = 0;
	}

	Car(const Car& c) {
		this->enTime = c.enTime;
		this->ID = c.ID;
	}
};
