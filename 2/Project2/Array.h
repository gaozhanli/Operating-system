#include <iostream>
#include <string>
using namespace std;

//
//实习2：首次适应算法实现主存分配和回收(数组)
//

//存储分区结构体
struct Memery {
	int no;                 //分区号
	int size;               //分区大小
	int address;        //分区首地址
	string status;      //分区状态,只有两种状态即“空闲”“已分配”
	int id;                  //用来区分初始分区，防止初始分区相互合并
};


int getSum(int count);   //获得count地址
int getMAX(int count, int applysize); //获得最大空闲分区大小

//数组分析函数
void Array();
