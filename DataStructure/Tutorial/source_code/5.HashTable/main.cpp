#include<iostream>
#include<fstream>
#include<string>
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

string names[30];
ListNode* hashTable = new ListNode[27];

// �ļ���ȡû������
void readFile() {
	string path;
	cout << "�������ļ���·�� : ";
	cin >> path;
	ifstream ifs(path, ios::in);
	if (!ifs) {
		cout << "�ļ�·���������..." << endl;
		exit(0);
	}
	for (int i = 0; i < 30; i++) {
		getline(ifs, names[i]);
	}
	ifs.close();
}

// ��������
void enterName() {
	int i = 1;
	while (i <= 30) {
		cout << "������� " << i << " ���˵�����(" << i << "/30)" << endl;
		getline(cin, names[i - 1]);
		i++;
	}
}

// ���ϣ���в�������
void insert(ListNode* hashtable, int posi, string data) {
	// hashtable �ǹ�ϣ�� posi��Ҫ�����λ�ã�data��Ҫ��������� 
	cout << data << " - INSERT" << endl;
	if (hashtable[posi].next == NULL) {
		hashtable[posi].next = new ListNode(data, NULL);
	} else {
		ListNode* temp = hashtable[posi].next;
		while (temp->next) temp = temp->next;
		temp->next = new  ListNode(data, NULL);
	}
}

// �����ϣ��
int hashCode(string str) {
	return str[0] % 27;
}

//�ڹ�ϣ���в���ָ���ַ������ɹ�����1�����򷵻�0
int findInHashTable(string nameToFind) {
	ListNode* temp = nullptr;
	if (!(temp = hashTable[hashCode(nameToFind)].next)) return 0;
	while (temp) {
		if (temp->data == nameToFind) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

int main() {
	int choose = 0;
	cout << "��ѡ�񹹽�������ϣ��ķ�ʽ��" << endl
		<< "1. ֱ������" << endl
		<< "2. ���ļ���ȡ" << endl
		<< "������ѡ��" << endl;
	cin >> choose;
	switch (choose) {
	case 1: getchar();  enterName(); break;
	case 2: readFile(); break;
	default:
		break;
	}
	
	// ����
	for (int i = 0; i < 30; i++) {
		cout << i + 1 << " ";
		insert(hashTable, hashCode(names[i]), names[i]);
	}
	
	cout << "���ݲ���ɹ�\n��ϣ�����ɹ�" << endl;

	int find = 0;
	do {
		cout << "��������(1/0) ��" << endl;
		cin >> find;
		if (find == 1) {
			cout << "������ҵ�����ƴ��" << endl;
			string nameToFind;
			cin >> nameToFind;
			// ��ʼ�ڹ�ϣ���в���
			if (findInHashTable(nameToFind))
				cout << "���ҳɹ�" << endl;
			else cout << "����ʧ��" << endl;
		} else break;
	} while (1);

	return 0;
}