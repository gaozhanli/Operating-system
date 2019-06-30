#include <iostream>
#include <string>
#define MAX 20    //最大进程数

using namespace std;
//
//实习1题目名称：利用时间片轮转法实现处理器调度
//

//进程数据结构
struct PCB {
	string name;                     //进程名
	int arrive;                          //进程到达时间
	int need;                           //进程请求时间
	int count = 0;                   //进程已运行时间
	bool status = true;           //进程状态，true:就绪   false：结束   (默认就绪)
	bool isOK = false;            //显示进程是否已经添加到循环队列， true代表已添加（默认为false）
};

PCB p[MAX];                        //定义进程数组
PCB queue[MAX];               //循环队列，存在覆盖的可能
int front = -1, rear = -1;     //队头、队尾指针

int main() {

	while (1) {
		int num, time, all = 0;                 //进程数, 时间片大小, 所有进程所需总时间
		int latest = 0;                             //进程进入队列最晚的时间，用来将进程放入队列
		string isGoOn;                           //是否要继续输入
		string detail;                              //true代表输出详细信息，false表示不输出详细信息

		cout << "请输入进程个数：";
		cin >> num;
		if (num > 20) {
			cout << "进程数超过最大值！" << endl;
			break;
			system("pause");
		}
		if (num <= 0) {
			cout << "输入进程数应大于0！" << endl;
			system("pause");
		}
		for (int i = 0; i < num; i++) {    //进行重置，用于重复输入
			p[i].status = true;
			p[i].isOK = false;
			p[i].count = 0;
		}

		cout << "请输入时间片大小：";
		cin >> time;
		if (time <= 0) {
			cout << "时间片应大于0" << endl;
			system("pause");
		}
		cout << "是否输出详细调度过程(y/n)：";
		cin >> detail;

		cout << "请依次输入进程名、进程到达时间和进程要求运行时间：";
		for (int i = 0; i < num; i++) {
			cin >> p[i].name >> p[i].arrive >> p[i].need;
			all += p[i].need;   //总时间
			if (latest < p[i].arrive)
				latest = p[i].arrive;
		}

		if (detail == "y")
			cout << "进程名" << "\t" << "已运行" << "\t" << "状态" << "\t" << "当前时刻" << endl;
		else
			cout << "进程名" << "\t" << "完成时刻" << endl;

		//根据进程到达时间进行排序，有利于时间片未用完的情况
		for (int i = 0; i < num; i++)
			for (int j = i + 1; j < num; j++) {
				if (p[i].arrive > p[j].arrive) {
					PCB temp = p[i];
					p[i] = p[j];
					p[j] = temp;
				}
			}

		int t = 0;
		while (t < all + latest) {   //当t小于总时间时

			if (t <= latest) {    //当小于latest时，可能需要向队列中添加进程
				for (int i = 0; i < num; i++) {
					if (p[i].isOK == false && t >= p[i].arrive) {   //向循环队列中添加进程
						p[i].isOK = true;         //防止重复添加
						rear = (rear + 1) % MAX;
						queue[rear] = p[i];    //进队列
					}
				}
			}

			if ((rear - front) != 0) {
				front = (front + 1) % MAX;   //出队列
				if ((queue[front].need - queue[front].count) <= time) {
					if (detail != "y")             //输出简略信息
						cout << queue[front].name << "\t" << t + queue[front].need - queue[front].count << endl;
					queue[front].status = false;   //运行结束，状态设为false

					t += (queue[front].need - queue[front].count);   //当前时间自增
					queue[front].count = queue[front].need;
					if (detail == "y")                                                   //输出具体信息
						cout << queue[front].name << "\t" << queue[front].count << "\t" << queue[front].status << "\t" << t << endl;
					continue;
				}
				else {
					queue[front].count += time;    // 已运行时间自增
					t += time;    //t以time为单位自增
					if (t <= latest + time) {    //当小于latest时，可能需要向队列中添加进程
						for (int i = 0; i < num; i++) {
							if (p[i].isOK == false && t >= p[i].arrive) {   //向循环队列中添加进程
								p[i].isOK = true;         //防止重复添加
								rear = (rear + 1) % MAX;
								queue[rear] = p[i];    //进队列
							}
						}
					}

					rear = (rear + 1) % MAX;
					queue[rear] = queue[front];    //进程未完成重新进入队列
					if (detail == "y")
						cout << queue[front].name << "\t" << queue[front].count << "\t" << queue[front].status << "\t" << t << endl;
					continue;
				}
			}
			t++;  //当到达时间不连续时
		}
		cout << "你想执行新进程吗(y/n)？";
		cin >> isGoOn;
		if (isGoOn == "y") {
			continue;
		}

		if (isGoOn == "n")
			system("pause");
		else {
			cout << "请输入：y/s" << endl;
			system("pause");
		}
	}

	system("pause");
	return 0;
}