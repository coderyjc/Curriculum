#pragma once
#include"Queue.h"
#include"Stack.h"
#include"Car.h"
#include<set>

class ParkingManager {
public:
	ParkingManager();
	~ParkingManager();

	void enterPark();
	void outPark();
	void mainLoop();

	void printParking();
	void printWaiting();

private:
	double size;

	//��ǰ�����г�
	set<string> currentCar;
	
	// ��˫ջ
	MyDoubleStack<Car*> parking; 
	
	// �ȴ�����
	MyQueue<Car*> wait; 
};
