#include <iostream>
#include <string>

using namespace std;
//
//利用链表实现首次适应内存分配算法
//

//存储分区结构体
struct Memery2 {
	int no;                 //分区号
	int size;               //分区大小
	int address;        //分区首地址
	string status;      //分区状态,只有两种状态即“空闲”“已分配”
	Memery2 * next;  //指向下一个分区的指针
};

void Distribute(Memery2 * head);           //内存分配与回收函数
void init(Memery2 *head);                      //初始化
void printLinker(Memery2 * head);        //输出分区链表
int getMAX(Memery2 *head, int size);   //循环链表获得合适空闲分区号
int getSum(Memery2 *head, int i);         //获得i之前的分区大小总和
bool isEmpty(Memery2 *head, int i);      //判断某分区是否为空闲
void deleteLinker(Memery2 *head);      //链表删除函数

//链表分析函数
void Linker();
