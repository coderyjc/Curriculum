#pragma once
#include<iostream>
#include<memory>
#include<queue>
using namespace std;

class TableNode {
public:
	TableNode(int a = 0, TableNode* n = NULL, int d = 0) {
		this->adjVex = a;
		this->nextArc = n;
		this->data = d;
	}

	int data; // data field 
	int adjVex; // �ڽӵ�
	TableNode* nextArc; // ָ��vi����һ���߻��߻��Ľڵ�
};

class HeadNode {
public:
	HeadNode(TableNode* n = NULL, int id = 0, int d = 0) {
		this->id = id;
		this->data = d;
		this->firstarc = n;
	}

	// vi's info
	int data;
	
	// point to the first node
	TableNode* firstarc;

	// Լ�� id Ϊ 0 ��ʱ���ʾ�ڵ��Ѿ�ɾ����
	int id;
};

class TableMap {
public:
	//----------CONSTRUCTOR------------

	TableMap();

	~TableMap();

	//---------FUNCTIONS-----------------

	// create a array map
	void init();

	// traverse the array map
	void DFSTraverse();
	void BFSTraverse();

	//insert a edge
	void insert();

	//delete a edge
	void deleteVtx();

	//get the shortest path
	void shortestPath();

	// main loop of the programe
	void mainLoop();

	//--------------FUNCTIONS

	void DFS(int edge, int visit[]);

	void layout();

private:
	HeadNode node[30];
	int size;
};

TableMap::TableMap() {
	size = 0;
	for(int i = 0; i < 30; i++) {
		// ����������е�id����Ϊ 1
		// ��Ϊ��ɾ����ҵ���߼��У�ɾ��һ�����ķ����ǰ� id ��Ϊ 0
		this->node[i].id = 1;
	}
}

TableMap::~TableMap() {}

void TableMap::init() {
	cout << "----------\nͼ�ĳ�ʼ��" << endl
		<< "----------" << endl;

	cout << "������ͼ�Ľ������(������30)" << endl;
	cin >> this->size;
	while (this->size > 30 || this->size < 0) {
		cout << "��������������" << endl;
		cin >> this->size;
	}
	// ���ø����ڵ��id
	for (int i = 0; i < this->size; i++) this->node[i].id = i + 1;
	// ���ñߺͱ��ϵ�Ȩֵ
	cout << "��ʼ���ߣ�����-1�������룺" << endl;
	int start = 0, end = 0, rank = 0;
	int i = 1;
	while (1) {
		int flag = 1;
		do {
			cout << "��������㡢�յ��Ȩֵ�м��ÿո����: ";
			cin >> start >> end >> rank;
			if (start < 0 || end < 0) {
				cout << "--------\n�������\n--------" << endl;
				return;
			} else if (start > this->size || end > this->size) {
				cout << "�����������������" << endl;
				flag = 1;
			} else break;
		} while (flag);
		
		// ͷ�ڵ�ĺ���ǿյ�ʱ��, ֱ��ָ��
		if (this->node[start - 1].firstarc == NULL) {
			this->node[start - 1].firstarc = new TableNode(end - 1, NULL, rank);
		} else {
		// ͷ�ڵ�ĺ�̲��ǿյ�ʱ��, ����ָ��ָ�����һλ����new��
			TableNode* temp = this->node[start - 1].firstarc;
			if (temp->adjVex == end - 1) {
				cout << "------\n���ظ�\n------" << endl;
				continue;
			}
			while (temp && temp->nextArc) {
				temp = temp->nextArc;
				if (temp->adjVex == end - 1) {
					cout << "------\n���ظ�\n------" << endl;
					break;
				}
			}
			temp->nextArc = new TableNode(end - 1, NULL, rank);
		}
	}
	cout << "------------\n��ʾ\n\nͼ��ʼ���ɹ�\n------------" << endl;
}


void TableMap::insert() {
	cout << "--------\n�ߵĲ���\n--------" << endl;
	int start = 0, end = 0, rank = 0;
	cin.clear();
	do {
		cout << "�������: " << endl;
		cin >> start;
		if (start <= 0 || start > this->size) {
			cout << "������������������" << endl;
		} else break;
	} while (1);

	do {
		cout << "�����յ�: " << endl;
		cin >> end;
		if (end <= 0 || end > this->size) {
			cout << "������������������" << endl;
		} else break;
	} while (1);

	cout << "����Ȩֵ" << endl;
	cin >> rank;
	
	if (this->node[start - 1].firstarc == NULL) {
		// �����㻹û��ָ���κεı�
		this->node[start - 1].firstarc = new TableNode(end - 1, NULL, rank);
	} else {
		// �������г�����
		TableNode* temp = this->node[start - 1].firstarc;
		if (temp->adjVex == end - 1) {
			cout << "--------\n���ظ���\n--------" << endl;
			return;
		}
		while (temp->nextArc) {
			temp = temp->nextArc;
			if (temp->adjVex == end - 1) {
				cout << "--------\n���ظ���\n--------" << endl;
				return;
			}
		}
		temp->nextArc = new TableNode(end - 1, NULL, rank);
	}
	cout << "--------\n��ʾ\n\n����ɹ�\n--------" << endl;
}


void TableMap::deleteVtx() {
	cout << "--------\n����ɾ��\n--------" << endl;
	cout << "������Ҫɾ���Ľڵ�" << endl;
	int todel = 0;
	cin.clear();
	cin >> todel;
	// ������
	while (todel > this->size || todel < 1 || this->node[todel - 1].id == 0) {
		cout << "��㲻���ڣ�����������" << endl;
		cin >> todel;
	}
	// ����ɾ��
	// ���ڽڵ���˵���涨idΪ0��ʱ���ʾ�ýڵ㲻����
	// Ȼ��ѳ������������еĵ㶼ɾ��
	for (int i = 0; i < this->size; i++) { // ��������ͷ�ڵ�
		TableNode* temp = this->node[i].firstarc;
		// ��Ԫ�ڵ�Ϊ 0 ����������
		if (temp && (temp->adjVex == todel - 1)) {
			this->node[i].firstarc = this->node[i].firstarc->nextArc;
		}
		// �������
		while (temp && temp->nextArc) {
			if (temp->nextArc->adjVex == todel - 1) {
				temp->nextArc = temp->nextArc->nextArc;
			}
			temp = temp->nextArc;
		}
	}
	// id��Ϊ 0
	this->node[todel - 1].id = 0;
	cout << "--------\n��ʾ\n\nɾ���ɹ�\n--------" << endl;
//	this->size--;
}

// ���Գɹ�
// ���·��
void TableMap::shortestPath() {

	// ����֮������·��
	int dist[maxn][maxn]; 
	
	// �Ȱ������Ķ���ʼ��Ϊһ���Ƚϴ������
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			dist[i][j] = CANNOT_REACH;
	
	// ��ʼ��dist·��
	for (int i = 0; i < this->size; i++) {
		TableNode* temp = this->node[i].firstarc;
		while (temp) {
			dist[i][temp->adjVex] = temp->data;
			temp = temp->nextArc;
		}
	}

	// ���,��Ϊ����
	for (int k = 0; k < this->size; k++) {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j]; // ����
				}
			}
		}
	}

	// ���������
	cout << "��������, �м��ÿո����, �ж�����̾���: ";
	int v1 = 0, v2 = 0;
	cin.clear();

	// ����������㣬�����ж�
	cin >> v1 >> v2;
	while (v1 < 1 || v1 > this->size || v2 < 1 || v2 > this->size || 
		   this->node[v1 - 1].id == 0 || this->node[v2 - 1].id == 0) {
		cout << "--------\n�㲻����\n--------" << endl;
		return;
	}

	// �����������
	if (v1 == v2) {
		cout << "������̾���Ϊ 0 " << endl;
	} else if (dist[v1 - 1][v2 - 1] == CANNOT_REACH) {
		cout << "���㲻�ɴ�" << endl;
	} else {
		cout << "������̾���Ϊ " << dist[v1 - 1][v2 - 1] << endl;
	}
}

// �������
// ���Գɹ�
void TableMap::DFSTraverse() {
	
	cout << "------------\n������ȱ���\n------------" << endl;

	// �Ѿ����ʹ��Ľڵ�
	int* visit = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		if (this->node[i].id != 0)
			visit[i] = 0;
		// ���Ѿ�ɾ���Ľ�㿴���Ѿ����ʹ���
		else visit[i] = 1;
	}

	// ������ȱ���
	for (int i = 0; i < this->size; i++) {
		if (!visit[i])
			this->DFS(i, visit);
	}
	
	// ��������
	if (visit != NULL) {
		delete[] visit;
		visit = NULL;
	}
	cout << endl;
}

// ���Գɹ�
void TableMap::DFS(int vtx, int visit[]) {
	cout << "���ʽ��--->" << vtx + 1 << endl;
	visit[vtx] = 1; // ���ʵ�ǰ���

	//˳�ŵ�ǰ������µݹ����
	TableNode* temp = this->node[vtx].firstarc;
	while (temp) {
		if (!visit[temp->adjVex]) {
			this->DFS(temp->adjVex, visit);
		}
		temp = temp->nextArc;
	}
}

// �������
// ���Գɹ�
void TableMap::BFSTraverse() {
	cout << "------------\n������ȱ���\n------------" << endl;

	// �Ѿ����ʹ��Ľ��
	int* visit = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		if (this->node[i].id != 0)
			visit[i] = 0;
		// ���Ѿ�ɾ���Ľ�㿴���Ѿ����ʹ���
		else visit[i] = 1;
	}

	// ������
	queue<int> q;

	for (int i = 0; i < this->size; i++) {
		if (!visit[i]) {
			visit[i] = 1;
			cout << "���ʽ��--->" << i + 1 << endl;
			q.push(i);

			while (!q.empty()) {
				TableNode* temp = this->node[q.front()].firstarc;
				q.pop();
				while (temp) {
					if (!visit[temp->adjVex]) {
						cout << "���ʽ��--->" << temp->adjVex + 1 << endl;
						visit[temp->adjVex] = 1;
						q.push(temp->adjVex);
					}
					temp = temp->nextArc;
				}
			}
		}
	}
	cout << endl;
}

// չʾ���ͼ���ڽӱ�
void TableMap::layout() {
	cout << "----------\n�鿴�ڽӱ�\n----------" << endl;

	if (this->size == 0) {
		cout << "--------\nδ��ʼ��\n--------" << endl;
		return;
	}

	for (int i = 0; i < this->size; i++) {
		if (this->node[i].id == 0) continue;
		cout << i + 1 << " : |-> ";
		TableNode* t = this->node[i].firstarc;
		while (t) {
			cout << t->adjVex + 1 << " -> ";
			t = t->nextArc;
		}
		cout << "null" << endl;
	}
	cout << endl;
}

void TableMap::mainLoop() {

	int choose = 0;

	while (true) {
		cout << "ͼ���ڽӱ�洢" << endl
			<< "-----------------" << endl
			<< "1. ��ʼ��" << endl
			<< "2. �����" << endl
			<< "3. ɾ���ڵ�" << endl
			<< "4. ���·��" << endl
			<< "5. ������ȱ���" << endl
			<< "6. ������ȱ���" << endl
			<< "7. �鿴ͼ" << endl
			<< "0. ������һ��" << endl
			<< "----------------" << endl
			<< "������ԵĹ���: " << endl
			<< "----------------" << endl;
		cin >> choose;
		switch (choose) {
			case 1: this->init(); break;
			case 2: this->insert(); break;
			case 3: this->deleteVtx(); break;
			case 4: this->shortestPath(); break;
			case 5: this->DFSTraverse(); break;
			case 6: this->BFSTraverse(); break;
			case 7: this->layout(); break;
			default: return;
		}
		system("pause");
		system("cls");
	}

}
