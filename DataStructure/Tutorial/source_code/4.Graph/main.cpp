#include"ArrayMap.h"
#include"TableMap.h"


/*
Ŀǰ���뷨�����У�

�ڽӱ�洢��������ͼ

�ڽӾ���洢��������ͼ
*/
int main() {

	ArrayMap am;
	TableMap tm;

	int choose = 0;
	while (true) {
		cout << "ѡ��洢��ʽ" << endl
			<< "----------------" << endl
			<< "1.�ڽӱ�洢������" << endl
			<< "2.�ڽӾ���洢������" << endl
			<< "0.�˳�" << endl
			<< "----------------" << endl
			<< "����Ҫ���ԵĹ���: ";
		cin >> choose;
		switch (choose) {
			case 1: system("cls");  tm.mainLoop();  break;
			case 2:system("cls");  am.mainLoop();  break;
			default: return 0;
		}
	}
	return 0;
}