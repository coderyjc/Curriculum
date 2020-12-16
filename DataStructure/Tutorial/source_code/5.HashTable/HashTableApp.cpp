#include "HashTableApp.h"
#include<fstream>
#include<string>

HashTableApp::HashTableApp() {
}

// ���ļ��ж�ȡ����	
void HashTableApp::readFile() {
	string path;
	cout << "�������ļ���·�� : ";
	cin >> path;
	ifstream ifs(path, ios::in);
	if (!ifs) {
		cout << "----------------\n���棺\n\n�ļ�·���������...\n----------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < 30; i++) {
		getline(ifs, names[i]);
	}
	ifs.close();

	for (int i = 0; i < 30; i++) {
		cout << i + 1 << " ";
		insert(hashCode(names[i]), names[i]);
	}

	cout << "----------------\n��ʾ��\n\n��ϣ�����ɹ�\n----------------" << endl;
	system("pause");
	system("cls");
}

// �ֶ���������
void HashTableApp::enterName() {
	// ��������
	int i = 1;
	while (i <= 30) {
		cout << "������� " << i << " ���˵�����(" << i << "/30)" << endl;
		getline(cin, names[i - 1]);
		i++;
	}

	for (int i = 0; i < 30; i++) {
		cout << i + 1 << " ";
		insert(hashCode(names[i]), names[i]);
	}

	cout << "--------------\n��ʾ��\n\n��ϣ�����ɹ�\n--------------" << endl;
}

// ���ϣ���в�������
void HashTableApp::insert(int posi, string data) {
	// hashtable �ǹ�ϣ�� posi��Ҫ�����λ�ã�data��Ҫ��������� 
	cout << data << " - INSERT" << endl;
	if (this->hashTable[posi].next == NULL) {
		this->hashTable[posi].next = new ListNode(data, NULL);
	} else {
		ListNode* temp = this->hashTable[posi].next;
		while (temp->next) temp = temp->next;
		temp->next = new  ListNode(data, NULL);
	}
}

void HashTableApp::layout() {
	cout << "----------\n��ϣ��ṹ\n----------" << endl;
	ListNode* temp = NULL;
	for (int i = 0; i < 27; i++) {
		if(i < 10) cout << " ";
		cout << i << " : ";
		temp = this->hashTable[i].next;
		if (temp) {
			// temp ��Ϊ�գ�Ҳ����˵����ڵ�����ֵ
			// ����������ĺ��
			while (temp) {
				cout << temp->data << " -> ";
				temp = temp->next;
			}
		} 
		// temp Ϊ�ջ�����ֵ������±����������
		cout << "null " << endl;
	}
	system("pause");
	system("cls");
}

void HashTableApp::find() {
	cout << "������ҵ�����ƴ��" << endl;
	string nameToFind;
	cin >> nameToFind;
	// ��ʼ�ڹ�ϣ���в���
	int success = 0;
	ListNode* temp = hashTable[hashCode(nameToFind)].next;
	while (temp) {
		if (temp->data == nameToFind) {
			success = 1;
		}
		temp = temp->next;
	}

	if (success)
		cout << "--------\n���ҳɹ�\n--------" << endl;
	else cout << "--------\n����ʧ��\n--------" << endl;
	system("pause");
	system("cls");
}

void HashTableApp::mainLoop() {
	int choose = 0;
	do {
		cout << "-------------------" << endl
			<< "����hashtable�Ĳ���" << endl
			<< "-------------------" << endl
			<< "1.�����ļ���ȡ�ؼ���" << endl
			<< "2.�ֶ�����ؼ���" << endl
			<< "3.�鿴��ϣ��" << endl
			<< "4.���ҹؼ���" << endl
			<< "0.�˳�" << endl
			<< "-------------------" << endl
			<< "�����룺";
		cin >> choose;
		switch (choose) {
		case 1: this->readFile(); break;
		case 2: getchar(); this->enterName(); break;
		case 3: this->layout(); break;
		case 4: this->find(); break;
		default: return;
		}
	} while (1);
}

int HashTableApp::hashCode(string str) {
	return str[0] % 27;
}