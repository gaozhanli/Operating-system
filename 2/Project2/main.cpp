#include "Array.h"
#include "Linker.h"

//
//本实验分别通过数组和链表实现主存的分配和回收
//
int main() {
	string choice;
	cout << "选择（数组/链表）进行分配操作：";
	cin >> choice;
	if (choice == "数组")
		Array();
	if (choice == "链表")
		Linker();

	return 0;
}