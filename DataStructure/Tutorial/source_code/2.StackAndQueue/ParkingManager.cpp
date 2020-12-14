#include "ParkingManager.h"

#define PARK_PER_TIME 5.0 //ͣ��ͣ�����ĵ�λʱ���ڵļ۸�
#define WAIT_PER_TIME 2.0 //ͣ�ڱ���ϵĵ�λʱ���ڵļ۸�

const string CARS[] = { "", "С�γ�", "�ͳ�", "ʮ�ֿ���" };

const double OCCUPY[4] = { 0, 1, 1.5, 3 }; //��ͬ�ĳ�ռ�ݵĳ�λ������Ҳ����ȡ����ϵ��

/*
	�������͵�����:
	- �жϳ�����ռ�����
	- ����ռ�����������ͣ����Ӧ�ø��Ľ��ڳ�����ڵȺ�����
*/

ParkingManager::ParkingManager() {
	this->size = MAX_STACK_SIZE;
}

ParkingManager::~ParkingManager() {
	Car* temp = NULL;

	while (!this->parking.empty_0()) { // ������ջͷ
		delete this->parking.top_0();
		this->parking.pop_0();
	}

	while (!this->parking.empty_1()) { //������ջβ
		delete this->parking.top_1();
		this->parking.pop_1();
	}

	while (!this->wait.empty()) {
		delete this->wait.front();
		this->wait.pop();
	}
}

// ǰ�᣺�Ⱥ�����������

void ParkingManager::enterPark() {
	string id;
	int time;
	int type;

	int enterSuc = 0;
	do {
		cin >> id >> type >> time;
		if (type < 1 || type > 3 || time < 0) {
			cout << "����������������������" << endl;
			enterSuc = 1;
		} else break;
	} while (enterSuc);

	if (this->size - OCCUPY[type] < 0) { //	��鳵����û����
		cout << "����ͣ������������Ⱥ����Ⱥ�..." << endl;
		this->wait.push(new Car(time, id, type));
		return;
	}
	this->parking.push_0(new Car(id, type, time));
	cout << "���� " << id << " ���� " << this->parking.size() << " �ų�λ, ʱ��Ϊ" << time << endl;
	this->size -= OCCUPY[type];
}

/*
	�����������:
	1. һֱ��ͣ����
	2. ԭ���ڱ���Ⱥ򣬺���������ͣ����
	3. һֱ�ڱ���Ⱥ�
*/

void ParkingManager::outPark() {
	string id;
	int time;
	int type;
	cin >> id >> type >> time;
	int flag = 0;
	while (!this->parking.empty_0()) {
		if (this->parking.top_0()->ID != id) { 
			//����������Ҫ��ȥ�ĳ�
			this->parking.push_1(this->parking.top_0());
			this->parking.pop_0();
		} else {
			// ��������Ҫ��ȥ�ĳ�
			cout << "�� " << this->parking.top_0()->ID
				<< " ���⣬ʱ��Ϊ " <<
				(time - this->parking.top_0()->enTime) +
				(this->parking.top_0()->enTime - this->parking.top_0()->waitTime)
				<< " Ӧ�����Ϊ "
				<< OCCUPY[type] * (PARK_PER_TIME * (time - this->parking.top_0()->enTime) + 
					WAIT_PER_TIME * (this->parking.top_0()->enTime - this->parking.top_0()->waitTime))
				<< endl;
			Car* todel = this->parking.top_0();
			this->parking.pop_0();
			
			//��վ���������ϸոճ�ȥ��������������
			this->size += OCCUPY[todel->type]; 
			
			//delete �ճ�ջ�ĳ�
			delete todel;
			flag = 1;
			break;
		}
	}
	if (flag) { 
		// �ڳ������ҵ������������������Ѿ���ȥ�˵������
		while (!this->parking.empty_1()) {
			// ���ո���·ȥ�ĳ�Ū��ȥ
			this->parking.push_0(this->parking.top_1());
			this->parking.pop_1();
		}
		// ���������ȴ��ĵ�һ��������Ҫ��
		// Ҳ���ǳ����п�������������
		// �Ͱ�������ȴ���1�����Ž�����
		if (!this->wait.empty()) { // �������ȴ����в���
			//  ��������л��пռ�
			if (this->size - OCCUPY[this->wait.front()->type] >= 0) {
				this->size -= OCCUPY[this->wait.front()->type];
				cout << "�ڵȴ������еĳ� " << this->wait.front()->ID << " ���복�⣬ʱ��Ϊ " << time << endl;
				this->wait.front()->enTime = time; 
				
				//���õȴ�������ǰ��ĳ������ʱ��
				this->parking.push_0(this->wait.front());
				this->wait.pop();
			}
		}
	} else { 
		// �ڳ�����û���ҵ����������ӵȺ���Ѱ��������
		flag = 0;
		// int findit = 0;
		for (int i = 0; i < this->wait.size(); i++) {
			if (this->wait.front()->ID == id) {
				// �ҵ�������������ʱ��frontλ�þ�������Ҫ�ҵĳ���
				cout << "���� " << this->wait.front()->ID
					<< " ���⣬ʱ��Ϊ " << time - this->wait.front()->waitTime
					<< " Ӧ�����Ϊ " << OCCUPY[type] * WAIT_PER_TIME * (time - this->wait.front()->waitTime) << endl;
				Car* todel = this->wait.front();
				this->wait.pop();
				
				//��ͣ�����ĳ���delete��
				delete todel; 
				flag = 1;
				break;
			} else { 
				// ��ǰ����������Ҫ�ҵĶ��� �����������뵽����β���������Ժ��ҵ���Ҳ��Ҫ�嵽���е�β���ģ�
				this->wait.push(this->wait.front());
				this->wait.pop();
			}
		}
	}
	if (!flag) cout << "����͵Ⱥ�����û��������" << endl;
}

void ParkingManager::mainLoop() {
	char choose = 0;
	while (true) {
		cout << "A.����" << endl
			<< "D.����" << endl
			<< "E.�˳�" << endl
			<< "������ѡ�A��D��E�������š��������͡�С�γ���1�����ͳ���2����ʮ�ֿ�����3�����͵�ǰʱ��" << endl;
		cin >> choose;
		switch (choose) {
			case 'A': case 'a': enterPark(); break;
			case 'D': case 'd': outPark(); break;
			case 'E': case 'e': default: return;
		}
	}
}
