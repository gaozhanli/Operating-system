#include "head.h"

int main() {
	init();
	printBlock();
	printGroup();
	operation();
	deleteLinker(A);
	deleteLinker(MA);
	system("pause");
	return 0;
}

//初始化函数
void init() {
	cout << "请输入该存储空间总块数：";
	cin >> all;
	if (all <= 0 || all > MAX_GROUP * MAX_BLOCK) {
		cout << "输入错误！" << endl;
		system("pause");
	}
	cout << "请输入一组最大块数：";
	cin >> block;
	if (block <= 0 || block > MAX_BLOCK) {
		cout << "输入错误！" << endl;
		system("pause");

	}
	group = (all + block - 1) / block;    //组数

	//初始化A
	A->size = 0;
	A->next = NULL;

	Group *p = A;
	int n = 1;   //块号
	for (int i = 0; i < group; i++) {
		Group *temp = new Group;
		temp->next = NULL;
		temp->size = 0;

		if (A->next == NULL) {
			A->next = temp;
			p = temp;
		}
		else {
			p->next = temp;
			p = temp;
		}

		for (int j = 0; j < block; j++) {   //给组中块赋块号
			if ((i*block + j + 1) <= all) {
				p->blocks[p->size].no = n++;
				p->blocks[p->size].status = "未分配";
				p->size++;                      //数量自增
			}
		}
	}

	//初始化MA
	MA->next = A->next;    //将A的第一组分配给MA
	MA->size = A->next->size;
	if (A->next != NULL) {
		A->next = A->next->next;
		MA->next->next = NULL;
	}
}

//输出已分配的块号
void printBlock() {
	cout << "已分配的块号为：";
	if (num == -1)
		cout << "无";
	else {
		int n = num;
		while (n >= 0 ) {
			if(B[n].status == "已分配")
				cout << B[n].no << "  ";
			n--;
		}
	}
	cout << endl;
}

//输出组中空闲块数和块号
void printGroup() {
	//先输出专用块中空闲块和块号
	cout << "组数" << "\t"<< "组中块数" << "\t" <<"块号" << "\t" << endl;
	int i = 0;
	if(MA->next != NULL)
		 i= MA->next->size -1;
	int g = 0;     //组数
	while (i >= 0 && MA->next != NULL) 
		cout << g<< "\t" << MA->next->size << "\t" << "\t" << MA->next->blocks[i--].no << endl;  //MA代表0组
	g++;

	//输出A
	Group * p = A->next;
	while (p != NULL) {
		int j = p->size - 1;
		while (j >= 0)
			cout << g << "\t" << p->size << "\t" << "\t" << p->blocks[j--].no << endl;
		g++;
		p = p->next;
	}
}

//销毁链表
void deleteLinker(Group * head) {
	Group * p = head->next;
	delete head;
	while (p != NULL) {
		Group * temp = p->next;
		delete p;
		p = temp;
	}
}

//获取特定块号的状态
bool getStatus(int no) {
	int n = num;
	while (n >= 0) {
		if (B[n].no == no && B[n].status == "已分配")
			return true;
		n--;
	}
	return false;
}

//根据块号找到块
Block getBlock(int no) {
	Block t;
	int n = num;
	while (n >= 0) {
		if (B[n].no == no && B[n].status == "已分配") {
			B[n].status = "空闲";
			return B[n];
		}
		n--;
	}
	return t;
}

//获取剩余空闲块数
int getMax() {
	int sum = 0;
	Group * p = A->next;
	while (p != NULL) {
		sum += p->size;
		p = p->next;
	}
	return sum + MA->next->size;
}

//进行空间的分配和回收
void operation() {
	string operate;
	int size = 0;     //请求的块数
	int no;             //回收的块号
	while (1) {
		cout << "请根据提示输入：（1:分配   2:回收   0:退出）";
		cin >> operate;
		if (operate == "1") {   //分配
			cout << "请输入请求块数：";
			cin >> size;
			if (size <= 0 || size > all) {
				cout << "输入错误! " << endl;
				continue;
			}
			else if (size > getMax()) {
				cout << "剩余空间不足！" << endl;
				continue;
			}
			else {  //进行分配
				if (size < MA->next->size) {   //请求块数小于空闲块数时
					while (size > 0) {
						MA->next->blocks[MA->next->size - 1].status = "已分配";
						num++;
						B[num] = MA->next->blocks[MA->next->size - 1];
						MA->next->size--;            //专用块空闲块数自减
						size--;
					}
				}
				else {          //请求块数大于或等于空闲块数时
					while (size > 0) {
						MA->next->blocks[MA->next->size - 1].status = "已分配";
						num++;
						B[num] = MA->next->blocks[MA->next->size - 1];
						MA->next->size--;            //专用块空闲块数自减

						if (MA->next->size == 0) {   //将新的组复制到MA
							delete MA->next;
							MA->next = A->next;
							if (A->next != NULL) {
								A->next = A->next->next;
								MA->next->next = NULL;
							}
								
						}
						size--;
					}
				}
			}
			printBlock();
			printGroup();
		}
		else if (operate == "2") {  //回收
			cout << "请输入回收的块号：";
			cin >> no;
			if (no <= 0 || no > all) {
				cout << "输入错误！" << endl;
				continue;
			}
			else if (!getStatus(no)) {
				cout << "该块为空闲状态，不需要回收！" << endl;
				continue;
			}
			else {  //进行回收
				if (MA->next == NULL) {
					Group * p = new Group;
					p->next = NULL;
					p->size = 0;
					MA->next = p;
				}
				if (MA->next->size == block) {   //此时MA专用块已满
					Group * p = new Group;
					p->next = NULL;
					p->size = 0;

					MA->next->next = A->next;  //将MA添加到A中
					A->next = MA->next;
					MA->next = p;
				}

				Block q = getBlock(no);              //将空闲块添加到MA
				MA->next->size++;
				MA->next->blocks[MA->next->size - 1] = q;
			}
			printBlock();
			printGroup();
		}

		else if (operate == "0") {  //退出
			break;
		}
	}
}