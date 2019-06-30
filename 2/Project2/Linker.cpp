#include "Linker.h"

static int counts = 0;                           //总的分区数,初始为0

//链表分析函数
void Linker() {
	Memery2 *head = new Memery2;      //链表头指针
	init(head);   //初始化
	printLinker(head);
	Distribute(head);          //内存分配与回收
	deleteLinker(head);     //删除链表
	system("pause");
}

//初始化
void init(Memery2 *head) {    
	counts ++;                               
	int initSize;            //分区号，大小
	cout << "请输入初始分区大小：";
	cin >> initSize;
	if (initSize <= 0) {
		cout << "初始分区大小设置错误！";
		system("pause");   //暂停程序执行
	}

	head->no = 1;
	head->size = initSize;
	head->status = "空闲";
	head->address = 0;
	head->next = NULL;
}

//输出分区链表
void printLinker(Memery2 * head) {    
	Memery2 * p = head;
	cout << "分区号" << "\t" << "大小" << "\t" << "起始地址" << "\t" << "状态" << endl;
	while (p != NULL) {
		cout << p->no << "\t" << p->size << "\t" << p->address << "\t" << "\t" << p->status << endl;
		p = p->next;
	}
}

//内存分配与回收函数
void Distribute(Memery2 * head) {    
	Memery2 * p = head;
	string operation;  //操作
	int applySize, i = 0;   //申请空间，空闲分区块
	while (1) {
		cout << "请根据提示输入(分配：1    回收：2    退出：0 )： ";
		cin >> operation;

		if (operation == "1") {   //进行内存分配
			cout << "请输入申请空间的大小：";
			cin >> applySize;
		    if (applySize <= 0) {
				cout << "请求空间大小有误！" << endl;
				continue;
			}
			i = getMAX(head, applySize);

			if (i == -1) {
				cout << "无足够空闲空间！" << endl;
			    continue;
			}
			else {    
				while (p->no != i)                           //i为空闲分区号，进行空间的分配
					p = p->next;
				int temp = p->size - applySize;     //分配之后剩余的空闲分区大小
				p->size = applySize;
				p->status = "已分配";

				Memery2 * q = new Memery2;       //划分之后产生的新的空闲分区
				q->no = p->no + 1;
				q->address = getSum(head,q->no);
				q->size = temp;
				q->status = "空闲";
				q->next = p->next;

				p->next = q;
				q = q->next;
				while (q != NULL) {                          //将链表后面的分区号自增
					q->no = q->no + 1;
					q = q->next;
				}
				counts++;                                       //分区数自增
				printLinker(head);                           //打印
			}

		}

		else if (operation == "2") {  //回收分配的空间
			int no;
			cout << "请输入要回收的分区号：";
			cin >> no;
			if (no<0 || no > counts) {
				cout << "分区号输入错误！" << endl;
				continue;
			}
			if (isEmpty(head,no)) {
				cout << "该分区为空闲状态，不需要回收！" << endl;
				continue;
			}

			if (no > 0 && no < counts && isEmpty(head, no - 1) && isEmpty(head, no + 1)) {   //当要回收的分区，上下均为空闲时，直接合并
				p = head;
				while (p != NULL && p->no != (no - 1))
					p = p->next;
				Memery2 *temp1 = p->next;
				Memery2 *temp2 = temp1->next;

				p->next = temp2->next;
				p->size = p->size + temp1->size + temp2->size;   //合并

				while (p->next != NULL) {    //合并后后面的空闲号减2
					p = p->next;
					p->no -= 2;
				}
			}

			else if (no > 0 && isEmpty(head, no - 1)) {            //与上一块合并
				p = head;
				while (p != NULL && p->no != (no - 1))
					p = p->next;
				Memery2 *temp1 = p->next;

				p->next = temp1->next;
				p->size = p->size + temp1->size;

				while (p->next != NULL) {
					p = p->next;
					p->no--;
				}
			}

			else if (no < counts && isEmpty(head, no + 1)) {    //与下一块合并
				p = head;
				while (p != NULL && p->no != no)
					p = p->next;
				Memery2 *temp1 = p->next;

				p->next = temp1->next;
				p->size = p->size + temp1->size;

				while (p->next != NULL) {
					p = p->next;
					p->no--;
				}
			}

			else {
				p = head;
				while (p != NULL && p->no != no)
					p = p->next;
				p->status = "空闲";
			}
			printLinker(head);    //输出合并后的链表
		}

		else if(operation == "0")    //退出
			break;
	}
}

//获得i之前的分区大小总和
int getSum(Memery2 *head, int i) {
	//cout << head->size;
	Memery2 * p = head;
	int sum = 0;
	while (p!= NULL && p->no != i) {
		sum += p->size;
		p = p->next;
	}
	return sum;
}

//链表删除函数
void deleteLinker(Memery2 *head) {    
	Memery2 * p;
	while (head != NULL) {
		p = head->next;
		delete head;
		head = p;
	}
}

//判断某分区是否为空闲
bool isEmpty(Memery2 *head, int i) {
	Memery2 * p = head;
	while (p != NULL && p->no != i)
		p = p->next;
	if (p != NULL && p->status == "空闲")
		return true;
	else
		return false;
}

//循环链表获得合适空闲分区号
int getMAX(Memery2 *head, int size) {
	Memery2 * p = head;
	int num = 0;
	while (p != NULL) {
		num++;
		if (p->size >= size && p->status == "空闲")
			return num;
		p = p->next;
	}
	return -1;
}