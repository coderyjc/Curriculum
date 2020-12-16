#include "ParkingManager.h"

#define PARK_PER_TIME 5.0 //ͣ��ͣ�����ĵ�λʱ���ڵļ۸�
#define WAIT_PER_TIME 2.0 //ͣ�ڱ���ϵĵ�λʱ���ڵļ۸�

const string CARS[] = { "", "�γ�", "�ͳ�", "����" };

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

	// ���복��
	do {
		cout << "�����복��" << endl;
		cin >> id;
		if (this->currentCar.find(id) != currentCar.end()) {
			// �����Ѿ�����
			cout << "--------------------\n����\n\n�����Ѵ��ڣ�����������\n--------------------\n" << endl;
		} else break;
	} while (1);

	this->currentCar.insert(id);
	// ���복������
	do {
		cout << "��ѡ��������" << endl
			<< "---------------" << endl
			<< "1.�γ�" << endl
			<< "2.�ͳ�" << endl
			<< "3.����" << endl
			<< "������: ";
		cin >> type;
		if (type < 1 || type > 3) {
			cout << "----------------\n���棺\n\n��������ȷ������\n----------------" << endl;
		} else break;
	} while (1);

	// ���뵱ǰʱ��
	do {
		cout << "�����뵱ǰʱ�� : ";
		cin >> time;
		if (time < 0) {
			cout << "----------------\n���棺\n\n��������ȷ��ʱ��\n----------------" << endl;
		} else break;
	} while (1);


	if (this->size - OCCUPY[type] < 0) { //	��鳵����û����
		cout << "----------------------------\n���ѣ�\n\n����ͣ������������Ⱥ����Ⱥ�...\n----------------------------" << endl;
		this->wait.push(new Car(time, id, type));
		system("pause");
		system("cls");
		return;
	}
	this->parking.push_0(new Car(id, type, time));
	cout << "-----------------------\n����\n\n���� " << id << " ���� " << this->parking.size() << " �ų�λ, ʱ��Ϊ" << time << endl 
		<< "-----------------------" << endl;
	this->size -= OCCUPY[type];

	system("pause");
	system("cls");
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
	
	cout << "�������ͣ�����ĳ���: ";
	cin >> id;
	cout << "�����뵱ǰʱ�䣺";
	cin >> time;
	
	int flag = 0;
	while (!this->parking.empty_0()) {
		if (this->parking.top_0()->ID != id) { 
			//����������Ҫ��ȥ�ĳ�
			this->parking.push_1(this->parking.top_0());
			this->parking.pop_0();
		} else {
			// ��������Ҫ��ȥ�ĳ�
			double toPay = OCCUPY[this->parking.top_0()->type] * (PARK_PER_TIME * (time - this->parking.top_0()->enTime) +
				WAIT_PER_TIME * (this->parking.top_0()->enTime - this->parking.top_0()->waitTime));
			if (toPay < 0) {
				cout << "--------------------\n����:\n\n������󣡳�վʧ�ܣ�\n--------------------" << endl;
				system("pause");
				system("cls");
				return;
			}
			cout << "--------------------\n����: \n\n�� " << this->parking.top_0()->ID
				<< " ���⣬ʱ��Ϊ " <<
				(time - this->parking.top_0()->enTime) +
				(this->parking.top_0()->enTime - this->parking.top_0()->waitTime)
				<< " Ӧ�����Ϊ "
				<< toPay
				<< endl
				<< "--------------------\n" << endl;
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
				cout << "--------------\n��ʾ��\n\n�ڵȴ������еĳ� " << this->wait.front()->ID << " ���복�⣬ʱ��Ϊ " << time 
					<< "\n--------------"<< endl;
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
					<< " Ӧ�����Ϊ " << OCCUPY[this->wait.front()->type] * WAIT_PER_TIME * (time - this->wait.front()->waitTime) << endl;
				Car* todel = this->wait.front();
				this->currentCar.erase(todel->ID); // �����еĳ���������ɾ��������
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
	if (!flag) cout << "--------------------\n��ʾ: \n\n�Ҳ���������\n--------------------" << endl;
	system("pause");
	system("cls");
}

void ParkingManager::mainLoop() {
	int choose = 0;
	while (true) {
		cout << "----------------\nͣ�����������\n----------------" << endl
			<< "1.����ͣ����" << endl
			<< "2.����ͣ����" << endl
			<< "3.�鿴ͣ��������" << endl
			<< "4.�鿴�ȴ�������" << endl
			<< "0.�˳�����\n----------------" << endl
			<< "������ѡ��: ";
		cin >> choose;
		switch (choose) {
			case 1: enterPark(); break;
			case 2: outPark(); break;
			case 3: printParking(); break;
			case 4: printWaiting(); break;
			case 0: default: return;
		}
	}
}

void ParkingManager::printParking() {
	// �ø���ջ��������
	if (this->parking.empty_0()) {
		cout << "--------------------\n��ʾ��\n\n��ǰͣ������û�г���\n----------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "\n----------------\nͣ�����еĳ���\n----------------\n" << endl;

	// ��ͷ
	cout << "���" << "\t����" << "\t��������" << "\t���복��ʱ��" << "\t��ռ�ռ�" << endl;
	cout << "----------------------------------------------------------" << endl;
	// ���Ѿ��������ĳ��ŵ�����ջ��
	// ��������֮���ٴӸ���ջ���ó���
	// �ڸ���ջ�н��в�����ʱ��Ͳ��ý��� size ��صĲ�����
	// �ȴ� 0 ջ�зŽ�����ջ�У�ͬʱ������
	int i = 1;
	while (!this->parking.empty_0()) {
		Car* temp = this->parking.top_0();
		// ����
		cout << i++ << "\t" << temp->ID << "\t" << CARS[temp->type] << "\t\t" << temp->enTime << "\t\t" << OCCUPY[temp->type] <<  endl;
		// �Ž�����ջ
		this->parking.push_1(temp);
		// ����ջ
		this->parking.pop_0();
	}
	// �ٴ� 1 ջ�зŽ� 0 ջ��
	while (!this->parking.empty_1()) {
		this->parking.push_0(this->parking.top_1());
		this->parking.pop_1();
	}
	system("pause");
	system("cls");
}

void ParkingManager::printWaiting() {
	if (this->wait.size() == 0) {
		cout << "----------------------\n��ʾ��\n\n��ǰ�ȴ�������û�г���\n----------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	// ��һ�� size ��С�ĳ��Ӻ����
	// ��ȡ���ڵȴ����еĴ�С
	int waitNumber = this->wait.size();
	cout << "\n----------------\n�ȴ������еĳ���\n----------------\n" << endl;
	// ��ͷ
	cout << "���" << "\t����" << "\t��������" << "\t�������ʱ��" << "\t��ռ�ռ�" << endl;
	cout << "----------------------------------------------------------" << endl;

	// i �Ǵ�ӡ���
	int i = 1;
	while (waitNumber--) {
		// �ѵ�ǰ�����ĳ��ȱ������ٳ�ջ������ջ
		Car* temp = this->wait.front();
		cout << i++ << "\t" << temp->ID << "\t" << CARS[temp->type] << "\t\t" << temp->waitTime << "\t\t" << OCCUPY[temp->type] << endl;
		this->wait.push(this->wait.front());
		this->wait.pop();
	}
	system("pause");
	system("cls");
}
