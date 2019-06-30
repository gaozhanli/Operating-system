#include "Array.h"

#define MAX 50   //最大分区数
Memery m[MAX];   //分区数组

//数组分析函数
void Array() {    
	int count = -1;                                     //总的分区数目
	int no, applySize, initSize;                   //分区号，大小
	int num = 1;                                       //初始分区数量
	cout << "请输入初始分区数目：";
	cin >> num;
	cout << "请依次输入初始分区大小：";
	for (int i = 0; i < num; i++) {
		cin >> initSize;
		if (initSize <= 0) {
			cout << "初始分区大小设置错误！" << endl;
			system("pause");
		}
		count++;
		//初始化分区
		m[count].no = count + 1;
		m[count].address = getSum(count);
		m[count].size = initSize;
		m[count].status = "空闲";
		m[count].id = m[count].no;
	}

	//输出分区表
	cout << "分区号" << "\t" << "大小" << "\t" << "起始地址" << "\t" << "状态" << endl;
	for (int i = 0; i <= count; i++) {
		cout << m[i].no << "\t" << m[i].size << "\t" << m[i].address << "\t" << "\t" << m[i].status << endl;
	}


	while (1) {
		string temp;                 //状态判断变量
		int i = 0;                      //申请的空间被分配的块号
		int num = 0;               //申请回收的块号
		cout << "请根据提示输入(分配：1    回收：2    退出：0 )： ";
		cin >> temp;
		if (temp == "1") {       //进行分配操作
			cout << "请输入申请空间的大小：";
			cin >> applySize;
			if (applySize <= 0) {
				cout << "请求空间大小有误！" << endl;
				continue;
			}
			i = getMAX(count, applySize);
			if (i == -1) {              //如果要求分配的空间大于最大的空闲分区
				cout << "无足够空闲空间！" << endl;
				continue;
			}
			else {                                                           //进行空间的分配，并打印
				for (int j = count; j >= i; j--)                   //进行块的后移
				{
					m[j + 1] = m[j];
					m[j + 1].no = m[j + 1].no + 1;           //后面的块号自增
				}
				count++;                                               //总分区数自增

				m[i].status = "已分配";
				int t = m[i].size;
				m[i].size = applySize;

				m[i + 1].size = t - applySize;
				m[i + 1].status = "空闲";
				m[i + 1].address = getSum(i);
				m[i + 1].id = m[i].id;

			}
			//输出分区表
			cout << "分区号" << "\t" << "大小" << "\t" << "起始地址" << "\t" << "状态" << endl;
			for (int i = 0; i <= count; i++) {
				cout << m[i].no << "\t" << m[i].size << "\t" << m[i].address << "\t" << "\t" << m[i].status << endl;
			}
		}

		if (temp == "2") {  // 进行回收操作
			cout << "请输入回收的分区号：";
			cin >> num;
			num--;              //为了与实际的计量相符合
			if (num <0 || num > count + 1) {
				cout << "分区号输入错误！" << endl;
				continue;
			}
			if (m[num].status == "空闲") {
				cout << "该分区为空闲状态，不需要回收！" << endl;
				continue;
			}

			//合并上下块
			if (num > 0 && (num + 1) <= count && m[num - 1].status == "空闲" && m[num].id == m[num - 1].id&& m[num + 1].status == "空闲" && m[num].id == m[num + 1].id) {
				m[num - 1].size = m[num - 1].size + m[num].size + m[num + 1].size;
				for (int j = num; j <= count; j++) {   //后面块前移
					m[j] = m[j + 2];
					m[j].no = m[j].no - 2;                   //分区号发生改变
				}
				count -= 2;                                      //合并后分区减小
			}

			//如果该块下一块为空闲则合并两分区
			else if ((num + 1) <= count && m[num + 1].status == "空闲" && m[num].id == m[num + 1].id) {   
				m[num].size = m[num].size + m[num + 1].size;
				m[num].status = "空闲";
				for (int j = num + 1; j <= count; j++) {   //后面块前移
					m[j] = m[j + 1];
					m[j].no = m[j].no - 1;                         //分区号发生改变
				}
				count--;                                                 //合并后分区减小
			}

			//上一块为空闲时向上合并，且保证为分区内的合并
			else if (num > 0 && m[num - 1].status == "空闲" && m[num].id == m[num - 1].id) {      
				m[num - 1].size = m[num - 1].size + m[num].size;
				for (int j = num; j <= count; j++) {   //后面块前移
					m[j] = m[j + 1];
					m[j].no = m[j].no - 1;                    //分区号发生改变
				}
				count--;                                            //合并后分区减小
			}

			else {
				m[num].status = "空闲";
			}

			//输出分区表
			cout << "分区号" << "\t" << "大小" << "\t" << "起始地址" << "\t" << "状态" << endl;
			for (int i = 0; i <= count; i++) {
				cout << m[i].no << "\t" << m[i].size << "\t" << m[i].address << "\t" << "\t" << m[i].status << endl;
			}
		}

		if (temp == "0")
			break;                //退出循环
	}

	system("pause");
}

//获得count地址
int getSum(int count) {
	int sum = 0;
	for (int i = 0; i <= count; i++) {
		sum += m[i].size;
	}
	return sum;
}

//获得最大空闲分区大小
int getMAX(int count, int applysize) {
	for (int i = 0; i <= count; i++) {
		if (m[i].size >= applysize && m[i].status == "空闲") {
			return i;
		}
	}
	return -1;
}