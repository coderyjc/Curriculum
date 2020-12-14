#include<ctime>
#include<cstdlib>
#include<iostream>
#include"Sorts.h"
using namespace std;

/*
 ��Ϊ�Ƕ����鱾���������������ÿ������֮���ٴ������ʱ�����鱾���������ģ�
 ����Ҫ��ÿһ���������֮���ٴζ�������и�ֵ
*/
vector<vector<int>> getData(int size) {
	srand(time(NULL));
	vector<vector<int>> allRst; // �洢���бȽϵ���������
	int* nums = new int[size];
	for (int i = 0; i < 5; i++) {
		// һ������5�αȽ�
		Sorts s;
		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		allRst.push_back(s.bubbleSort(nums, size));

		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		allRst.push_back(s.insertSort(nums, size));

		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		allRst.push_back(s.selectionSort(nums, size));

		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		allRst.push_back(s.shellSort(nums, size));
		// ���ڿ����漰���˵ݹ飬�������ˡ�ȫ�ֱ��������洢��ص�����
		vector<int> t;
		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		s.quickSort(nums, 0, size);
		t.push_back(s.cmpOfQuickSort);
		t.push_back(s.movOfQuickSort);
		allRst.push_back(t);
		// ������������ص�����
		t.clear();
		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		s.heapSort(nums, size);
		t.push_back(s.cmpOfHeapSort);
		t.push_back(s.movOfHeapSort);
		allRst.push_back(t);
	} //��ȡ���бȽϵ����е�5������

	vector<vector<int>> rst;
	int sumCmp[6] = { 0, 0, 0, 0, 0, 0 }; // ÿһ�ֱȽϵ��ܵıȽϴ���
	int sumMov[6] = { 0, 0, 0, 0, 0, 0 }; // ÿһ�ֱȽϵ��ܵ��ƶ�����
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			sumCmp[j] += allRst[j + i * 5][0];
			sumMov[j] += allRst[j + i * 5][1];
		}
	}

	for (int i = 0; i < 6; i++) {
		// ÿһ�ֱȽϵ�ƽ���ȽϺ��ƶ�����
		vector<int> t;
		t.push_back(sumCmp[i] / 5);
		t.push_back(sumMov[i] / 5);
		rst.push_back(t);
	}
	return rst;
}

int main() {
	srand(time(NULL));
	const string names[] = { "ð�ݣ�", "���룺", "ѡ��", "ϣ����", "���ţ�", "���ţ�"};
	for (int i = 100; i <= 6400; i *= 2) { // �ĳ�10��
		cout << "������С: " << i << endl;
		vector<vector<int>> rst = getData(i);
		for (int i = 0; i < 6; i++) {
				cout << names[i] << "�Ƚϴ��� " << rst[i][0] << " �ƶ����� " << rst[i][1];
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}
