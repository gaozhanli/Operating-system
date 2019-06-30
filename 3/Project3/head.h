#include <iostream>
#include <string>
#define MAX_GROUP 100    //最大组数
#define MAX_BLOCK  100    //一组最大块数

using namespace std;
//
//利用空间块成组链接法实现磁盘存储空间的管理
//

//块类型
struct Block {
	int no;        //块号
	string status; //状态
};
//组类型
struct Group {
	int size;      //组中块的个数
	Block blocks[MAX_BLOCK]; //组中块数组
	Group * next;          //指向下一组的指针
};


void init();                              //初始化函数
void printBlock();                  //输出已分配的块号
void printGroup();                //输出组中空闲块数和块号
void deleteLinker(Group * head); //销毁链表
int getMax();                         //获取剩余空闲块数
bool getStatus(int no);         //获取特定块号的状态
Block getBlock(int no);         //根据块号找到块
void operation();                  //进行空间的分配和回收


int group, block, all;                //组数、一组块数、总块数
Group *A = new Group;         //磁盘块链表头结点
Group * MA = new Group;    //专用块结点指针
Block B[MAX_GROUP*MAX_BLOCK];   //用来保存已分配的块
int num = -1;                                         //B下标