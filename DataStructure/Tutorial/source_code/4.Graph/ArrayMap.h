#pragma once
#include<memory>
#include<iostream>
#include<queue>
using namespace std;

const int maxn = 30;
const int CANNOT_REACH = 99999;

class MapNode {
public:
	// ------CONSTRUCTOR------
	MapNode() {
		m_id = 0;
	}

	MapNode(int id) {
		this->m_id = id;
	}
private:
	int m_id;
};

class ArrayMap {

public:

	//-----------CONSTRUCTORS--------------

	ArrayMap() {
		size = 0;
		for (int i = 0; i < 30; i++) for (int j = 0; j < 30; j++) this->data[i][j] = 0;
	}

	//----------DESTRUCTORS-------------
	
	~ArrayMap() {}

	//---------FUNCTIONS-----------------

	// create a array map
	void init();

	//insert a edge
	void insert();

	//delete a edge
	void deleteVtx();

	//get the shortest path
	void shortestPath();

	// main loop of the programe
	void mainLoop();

	void DFSTraverse();
	void DFS(int vtx, int visited[]);

	void BFSTraverse();

	// see the view
	void layout();

private:

	//the number of nodes;
	int size;

	//�ڽӾ������д洢�ߵ�Ȩֵ
	int data[30][30];

	//ͼ���
	MapNode node[30];
};

/*
���Գɹ�
*/
void ArrayMap::init() {
	cout << "------\n��ʼ��\n------" << endl;
	cout << "������ͼ�Ľ������(������30)" << endl;
	cin >> this->size;
	while (this->size > 30 || this->size < 0) {
		cout << "��������������" << endl;
		cin >> this->size;
	}

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
				cout << "�������" << endl;
				return;
			} else if (start > this->size || end > this->size) {
				cout << "�����������������" << endl;
				flag = 1;
			} else break;
		} while (flag);
		this->data[start - 1][end - 1] = rank;
		this->data[end - 1][start - 1] = rank;
	}
	cout << "------------\n��ʾ\n\nͼ��ʼ���ɹ�\n------------" << endl;
}


/*
���Գɹ�
*/
void ArrayMap::insert() {
	cout << "--------\n�ߵ����\n--------" << endl;
	cout << "������ӵıߵ���㣬�յ��Ȩֵ: ";
	int start, end, rank;
	cin.clear();
	cin >> start >> end >> rank;
	if (start < 1 || end < 1 || start > this->size || end > this->size) {
		cout << "�����±�Խ��" << endl;
		exit(0);
	} else {
		this->data[start - 1][end - 1] = rank;
		this->data[end - 1][start - 1] = rank;
	}
	cout << "--------\n��ӳɹ�\n--------" << endl;
}

/*
��ͨ���ýڵ�ıߺ͸ýڵ�ͨ���ıߵ�Ȩ��Ϊ0����������Ƿ���У�
Ŀǰ��Ϊ�ǿ��еģ�������DFS��BFS��ʱ����ܻ�����һЩ�鷳
*/
void ArrayMap::deleteVtx() {
	cout << "������Ҫɾ���ĵ�:";
	int vertex = 0;
	cin >> vertex;
	if (vertex < 0 || vertex > this->size) {
		cout << "�����������" << endl;
		exit(0);
	} else {
		for (int i = 0; i < this->size; i++) {
			this->data[vertex - 1][i] = 0;
			this->data[i][vertex - 1] = 0;
		}
	}
	this->data[vertex - 1][0] = -1;
	cout << "--------\nɾ���ɹ�\n--------" << endl;
}

/*
���������㷨�����·��
*/
void ArrayMap::shortestPath() {
	int dist[maxn][maxn] = {}; // ��̾���

	// ��ʼ����̾������
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			if ((this->data[i][j] == 0 && i != j) || this->data[i][0] == -1) dist[i][j] = CANNOT_REACH;
			// data[i][0] == -1 ��ʱ�򣬿�������㲻����
			else dist[i][j] = this->data[i][j];
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
	cout << "��������, �ж�����̾���, �м��ÿո����: ";
	int v1 = 0, v2 = 0;
	cin.clear();

	// ������
	cin >> v1 >> v2;
	while (v1 < 1 || v1 > 30 || v2 < 1 || v2 > 30) {
		cout << "ֵ������Ҫ��" << endl;
		cin >> v1 >> v2;
	}

	// �����������
	if (v1 == v2) {
		cout << "������̾���Ϊ 0 " << endl;
	} else if (dist[v1 - 1][v2 - 1] == 0 || dist[v1 - 1][v2 - 1] == CANNOT_REACH) {
		cout << "���㲻�ɴ�" << endl;
	} else {
		cout << "������̾���Ϊ " << dist[v1 - 1][v2 - 1] << endl;
	}
}

void ArrayMap::DFSTraverse() {
	cout << "------------\n������ȱ���\n------------" << endl;

	// �Ѿ��������ĵ�
	int* visit = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		if (this->data[i][0] == -1) visit[i] = 1;
		else visit[i] = 0;
	}

	for (int i = 0; i < this->size; i++) {
		if (!visit[i])
			this->DFS(i, visit);
	}
	cout << endl;
}

void ArrayMap::DFS(int vtx, int visited[]) {
	cout << "���ʽڵ�--->" << vtx + 1 << endl;
	visited[vtx] = 1;
	for (int i = 0; i < this->size; i++) {
		if (this->data[vtx][i] != 0 && !visited[i])
			this->DFS(i, visited);
	}
}

void ArrayMap::BFSTraverse() {
	cout << "------------\n������ȱ���\n------------" << endl;

	// �Ѿ��������ĵ�
	int* visit = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		if (this->data[i][0] == -1) visit[i] = 1;
		else visit[i] = 0;
	}

	// ������
	queue<int> q;

	for (int i = 0; i < this->size; i++) {
		if (!visit[i]) {
			visit[i] = 1;
			cout << "���ʽ��--->" << i + 1 << endl;
			q.push(i);

			while (!q.empty()) {
				i = q.front();
				q.pop();
				for (int j = 0; j < this->size; j++) {
					if (this->data[i][j] != 0 && !visit[j]) {
						visit[j] = 1;
						cout << "���ʽ��--->" << j + 1 << endl;		
						q.push(j);
					}
				}
			}
		}
	}
	cout << endl;
}

void ArrayMap::layout() {
	if (this->size == 0) {
		cout << "----------\nͼδ��ʼ��\n----------" << endl;
		return;
	}
	cout << "--------\n�ڽӾ���\n--------" << endl;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			if (this->data[i][j] != 0) cout << this->data[i][j] << "\t";
			else cout << "��\t";
		}
		cout << endl;
	}
}

void ArrayMap::mainLoop() {

	int choose = 0;

	while (true) {
		cout << "ͼ���ڽӾ���洢" << endl
			<< "-----------------" << endl
			<< "1. ��ʼ��" << endl // yes
			<< "2. �����" << endl
			<< "3. ɾ���ڵ�" << endl
			<< "4. ���·��" << endl
			<< "5. ������ȱ���" << endl
			<< "6. ������ȱ���" << endl
			<< "7. �鿴ͼ" << endl
			<< "0. ������һ��" << endl
			<< "----------------" << endl
			<< "������ԵĹ���: " << endl;
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