/*******************************************
* 
* Author: Yan Jingcun
* 
* DateTime: 2022-4-18 11:40
* 
* Description: �洢����̬�������估�����㷨
* 
*******************************************/

#include<cstdio>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

// �洢�ռ����ɹ�
#define ALLOCATE_SUCCESS 1
// �ڴ治��
#define OVERFLOW_ERROR -1

// ������Ӧ�㷨
#define FIRST_FIT_ALGORITHM 1
// ������Ӧ�㷨
#define BEST_FIT_ALGORITHM 2
// �ڴ����
#define MEMORY_ALLOCATE 1
// �ڴ����
#define MEMORY_RECOVERY 2

// ������ ��ַ��������
#define FREE_ADD_ASC_SORT 1
// �������ڴ�ռ��С��������
#define FREE_MEM_ASC_SORT 2
// ������ ��ַ��������
#define ALLO_ADD_ASC_SORT 3

// check �Ľ�� - �ڿ���
#define CHECK_STATUS_INBLOCK 1
// check �Ľ�� - ��Խ��
#define CHECK_STATUS_CROSS 2
// check �Ľ�� - ����Խ��(δ�ҵ���ַ)
#define CHECK_STATUS_VIOLATE -1

typedef struct Node {

	Node() {
		this->adr = 0;
		this->size = 0;
		this->next = NULL;
	}

	Node(int ad, int size, Node* n = NULL) {
		this->adr = ad;
		this->size = size;
		this->next = n;
	}

	// �����׵�ַ
	int adr;

	// ������С
	int size;

	// ָ����һ��������ָ��
	Node* next;

}Node;

// ������������ָ��
Node* head1 = NULL;

// ָ���ͷ��� node �ṹ��ָ��
Node* back1 = NULL;

// ָ��������ڴ���� node �ṹ��ָ��
Node* assign = NULL;

// �û�������ڴ��С
int allocate = 0;

// �ͷ������׵�ַ
int release_add = 0;

// �ͷ����Ĵ�С
int release_size = 0;

// ���еĲ���
char operation = 0;

// ʹ�õ��㷨
char recoverAlgorithm = 0;

// ν�� ��ַ��������
bool compareAddressAsc(Node a, Node b) {
	return a.adr < b.adr;
}
// ν�� �ڴ���������
bool compareMemoryAsc(Node a, Node b) {
	return a.size < b.size;
}

/// 
/// �������������
/// 
int sortList(int method) {

	Node* temp = NULL;
	vector<Node> v;
	if (FREE_ADD_ASC_SORT == method) {
		// ��������ַ��������
		temp = head1;
		// ʹ��vector�Դ�������
		while (temp) {
			v.push_back(Node(temp->adr, temp->size, temp->next));
		}
		sort(v.begin(), v.end(), compareAddressAsc);
		// ����֮���ٷŻ�ԭ��������
		temp = head1;
		for (int i = 0; temp; i++) {
			temp->adr = v[i].adr;
			temp->size = v[i].size;
			temp->next = v[i].next;
			temp = temp->next;
		} // �������
	}
	else if (FREE_MEM_ASC_SORT == method) {
		// �������ڴ�ռ��С��������
		temp = head1;
		// ʹ��vector�Դ�������
		while (temp) {
			v.push_back(Node(temp->adr, temp->size, temp->next));
		}
		sort(v.begin(), v.end(), compareMemoryAsc);
		// ����֮���ٷŻ�ԭ��������
		temp = head1;
		for (int i = 0; temp; i++) {
			temp->adr = v[i].adr;
			temp->size = v[i].size;
			temp->next = v[i].next;
			temp = temp->next;
		} // �������
	}
	else if (ALLO_ADD_ASC_SORT == method) {
		// ��������ַ��������
		temp = assign;
		// ʹ��vector�Դ�������
		while (temp) {
			v.push_back(Node(temp->adr, temp->size, temp->next));
		}
		sort(v.begin(), v.end(), compareAddressAsc);
		// ����֮���ٷŻ�ԭ��������
		temp = assign;
		for (int i = 0; temp; i++) {
			temp->adr = v[i].adr;
			temp->size = v[i].size;
			temp->next = v[i].next;
			temp = temp->next;
		} // �������
	}
	return 0;
}

/// check ����ͷſ����Ч��
///		Ҳ���Ǽ���ͷſ�������ǲ������Ѿ�����Ŀ���
/// 
/// *provided: 
///		release_add �ͷ�������׵�ַ
///		release_size Ҫ�ͷ�����Ĵ�С
///		assign �Ѿ�ʹ�õĿռ�, ����ռ�Ӧ����[��ַ����]����, 
///			   �Ա�Ҫ�ͷŵ������Խ�����ڵ��ʱ���ܹ�˳������
///		head1 ���ж��е�ָ��
/// 

int check() {

	// assign Ӧ���Ե�ַ����ķ�ʽ����, 
	// �Ա�Ҫ�ͷŵ������Խ�����ڵ��ʱ���ܹ�˳������
	sortList(ALLO_ADD_ASC_SORT);

	// ���
	Node* temp = assign;
	while (temp) {
		if (release_add >= temp->adr && release_add < temp->adr + temp->size) {
			// �ͷ�����ַ�ڵ�ǰ����
			if (release_add + release_size <= temp->size) {
				// û�п�Խ��(�ڵ�)
				return CHECK_STATUS_INBLOCK;
			}
			else {
				// ��Խ��(�ڵ�)
				return CHECK_STATUS_CROSS;
			}
		}
		temp = temp->next;
	}

	// ����ڴ�֮ǰ��û�з���, ����Ŀ���ַδ������, ��ʱ��ֱ�ӷ��ط��ʳ�ͻ
	return CHECK_STATUS_VIOLATE;
}

/// 
/// First Fit Algorithm
/// 
/// *���ӷ�ʽ
///		���з����� [��ַ] �����Ĵ�������
/// *���ҷ�ʽ:
///		�����ڴ�ʱ, �����׿�ʼ˳�����
/// *����:
///		�ҵ���С�ܹ������ [��һ��] ���з���
/// *provided:
///		allocate_size ��Ҫ����Ĵ�С
int assignment1() {

	// ָ����з������׵�ַ
	Node* temp = head1;

	// �Ѿ�����洢�ռ�ı�־
	int flag = 0;

	// ��һ�����пռ������
	if (temp->size >= allocate) {
		// �¿ռ����ӽڵ�
		if (!assign) {
			// assign Ϊ��
			assign = new Node(0, allocate , NULL);
		}
		else {
			Node* temp = assign;
			// �ƶ���������
			while (temp->next) temp = temp->next;
			// Ϊ���̷���ռ�
			temp->next = new Node(head1->adr, allocate, NULL);
		}
		// ���µ�һ�����пռ�
		head1->adr = head1->adr + allocate;
		head1->size = head1->size - allocate;
		// ��־�Ѿ������˿ռ�
		return ALLOCATE_SUCCESS;
	}

	// �ǵ�һ���ռ�����, ��Ҫ����ǰһ��ָ��
	// 
	while ((!flag) && temp->next) {

		/// ��ǰ�ڵ�Ĵ洢����С������Ҫ�Ĵ洢���Ĵ�С
		/// �ѵ�ǰ�ڵ�Ĵ洢����ֳ�������
		/// һ������ [temp.addr, temp.addr + allocate_size)
		/// �� [temp.addr, temp.addr + allocate_size - 1], �����洢 allocate ����
		/// ��һ������ [temp.addr + allocate_size, temp.addr + temp.size]
		if (temp->size >= allocate) {

			// �����½ڵ�
			Node* newBlock = new Node();



		}  
		temp = temp->next;
	}

	return 0;
}

/// Best Fit Algorithm
/// 
/// *���ӷ�ʽ
///		���з����� [����] �����Ĵ�������
/// *���ҷ�ʽ:
///		�����ڴ�ʱ, �����׿�ʼ˳�����
/// *����:
///		�ҵ���С�ܹ������ [��С��] ���з���
int assignment2() {



	return 0;
}

/// First Fit Algorithm �����㷨
/// 
/// *provided:
///		assign ָ���Ѿ�������ڴ�node��ָ��
///		head1 ���������е���ָ��
///		
/// 
int acceptment() {



	return 0;
}



// ��ӡ����������
int print() {

	// ���������еĴ�С
	Node* temp = head1;

	printf("����������\n\n\n���\t��ַ\t��ַ\t��С\n");

	int i = 0;
	while (temp) {
		printf("%-5d\t%-5d\t%-5d\t%-5d\n", 
			i++, temp->adr, temp->adr + temp->size - 1, temp->size);
		temp = temp->next;
	}

	// debug 

	printf("������ ����\n\n\n���\t��ַ\t��ַ\t��С\n");

	temp = assign;
	i = 0;
	while (temp) {
		printf("%-5d\t%-5d\t%-5d\t%-5d\n",
			i++, temp->adr, temp->adr + temp->size - 1, temp->size);
		temp = temp->next;
	}

	return 0;
}

int main() {

	// ��ʼ��
	head1 = new Node(0, 32767);

	allocate = 500;
	assignment1();
	assignment1();
	assignment1();
	print();

	//cout << "�����㷨: \n1. First Fit\n2. Best Fit\n";
	//cin >> recoverAlgorithm;

	//cout << "���� or ����: 1. ����\n2. ����\n";
	//cin >> operation;

	//while (1) {



	//}
	
	return 0;
}