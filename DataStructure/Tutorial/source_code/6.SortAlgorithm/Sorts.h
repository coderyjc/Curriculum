#pragma once
#include<vector>
using namespace std;
class Sorts {

public:

	Sorts() {
		this->cmpOfQuickSort = 0;
		this->movOfQuickSort = 0;
		this->cmpOfHeapSort = 0;
		this->movOfHeapSort = 0;
	}

	vector<int> bubbleSort(int* nums, int n); //ð������

	vector<int> insertSort(int*, int); // ��������

	vector<int> selectionSort(int*, int); // ѡ������

	vector<int> shellSort(int*, int); // ϣ������
	
	void quickSort(int*, int, int); // ����

	void heapSort(int*, int); // ������

	void heapAdjust(int*, int, int);

	void printNums(int *, int); // ��ӡ����

public:
	int cmpOfQuickSort;
	int movOfQuickSort;
	int cmpOfHeapSort;
	int movOfHeapSort;
};
