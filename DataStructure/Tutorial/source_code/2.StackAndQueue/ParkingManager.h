#pragma once
#include"Queue.h"
#include"Stack.h"
#include"Car.h"

class ParkingManager {
public:
	ParkingManager();
	~ParkingManager();

	void enterPark();
	void outPark();
	void mainLoop();

private:
	double size;
	MyDoubleStack<Car*> parking; // ��˫ջ
	MyQueue<Car*> wait; // �ȴ�����
};
