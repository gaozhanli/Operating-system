#include "Array.h"
#include "Linker.h"

//
//��ʵ��ֱ�ͨ�����������ʵ������ķ���ͻ���
//
int main() {
	string choice;
	cout << "ѡ������/�������з��������";
	cin >> choice;
	if (choice == "����")
		Array();
	if (choice == "����")
		Linker();

	return 0;
}