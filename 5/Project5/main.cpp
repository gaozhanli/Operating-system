#include <iostream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

#define MAX 50          //最大产品数
//
//实习5:模拟P、V操作实现同步机构，且用P、V操作解决生产者——消费者问题
//

//进程控制块类型
struct PCB {
	string name;         //进程名
	string status;        //进程状态：运行态、就绪态、等待态、完成态
	string reason;       //等待原因
	int  breakPoint;    //断点信息，使用int类型变量来判断运行到的位置
	char s;                  //生产者要生产的产品
	int t;                     //阻塞循序
};

void init();                //初始化生产者和消费者以及互斥信号量
void printStatus();   //输出所有模拟进程状态
void process();        //进行生产和消费
bool isGoing();        //判断是否有生产者进程还在运行
void getEarliest(int type); //解除最先阻塞的生产者或消费者


//消费者数组
vector<PCB> consume;
//生产者数组
vector <PCB> produce;
//缓冲区数组，用于保存生产的产品
vector <char> stock;
int s;               //指向获取的产品
//用于消费者消费时充当stock的临时存储
vector<char> temp;
vector<PCB> temp1;         //临时存储生产者信息


//访问互斥信号量
int s1, s2;           //s1表示产品数， s2表示空闲数，二者相加为缓冲区大小
char products[MAX];          //需要生产的产品
int p = 0;                           //products数组下标

int main() {
	init();
	printStatus();
	process();

	system("pause");
	return 0;
}

//初始化生产者和消费者以及互斥信号量
void init() {
	int snum, pnum;    //消费者和生产者个数
	cout << "请依次输入生产者和消费者个数：";
	cin >> pnum >> snum;
	if (snum <= 0 || pnum <= 0) {
		cout << "输入错误！" << endl;
		system("pause");      //如果输入错误，暂停整个项目的运行
	}

	//创建消费者模拟进程
	for (int i = 1; i <= snum; i++) {
		PCB *p = new PCB;
		p->name = "s" + to_string(i);
		p->status = "就绪态";           //初始状态设为就绪态
		p->reason = "";                    //赋为空
		p->breakPoint = 0;               //初始运行位置为0
		consume.push_back(*p);       //添加到consume数组中
	}
	
	//创建生产者模拟进程
	for (int i = 1; i <= pnum; i++) {
		PCB *p = new PCB;
		p->name = "p" + to_string(i);
		p->status = "就绪态";           //初始状态设为就绪态
		p->reason = "";                    //赋为空
		p->breakPoint = 0;               //初始运行位置为0
		produce.push_back(*p);        //添加到produce数组中
	}

	int all;                   //缓冲区大小
	cout << "请输入缓冲区大小：";
	cin >> all;
	if (all <= 0) {
		cout << "输入错误!" << endl;
		system("pause");                     //如果输入错误暂停项目执行
	}
	s1 = 0, s2 = all;                           //给互斥信号量赋初值

	cout << "请输入需要生产的产品：";
	cin >> products;                         //初始化产品序列

	//产品个数;
	int j = 0;
	while (products[j] != '\0')
		j++;
}

//输出所有模拟进程状态
void printStatus() {
	cout << "进程名" << "\t" << "状态" << "\t" <<"等待原因" << "\t" <<"断点"<< endl;
	string temp1;

	//输出生产者状态
	for (int i = 0; produce.size() >= 0 && i < produce.size(); i++) {
		cout << produce[i].name << "\t" << produce[i].status << "\t" << produce[i].reason << "\t" << "\t";
		switch (produce[i].breakPoint) {
		case 0:
			temp1 = "0";
			break;
		case 1:
			temp1 = "produce";
			break;
		case 2:
			temp1 = "p(s2)";
			break;
		case 3:
			temp1 = "put";
			break;
		case 4:
			temp1 = "v(s1)";
			break;
		}
		cout << temp1 << endl;
	}
		

	//输出消费者状态
	for (int i = 0; i < consume.size(); i++) {
		cout << consume[i].name << "\t" << consume[i].status << "\t" << consume[i].reason << "\t" << "\t";
		switch (consume[i].breakPoint) {
		case 0:
			temp1 = "0";
			break;
		case 1:
			temp1 = "p(s1)";
			break;
		case 2:
			temp1 = "get";
			break;
		case 3:
			temp1 = "v(s2)";
			break;
		case 4:
			temp1 = "consume";
			break;
		}
		cout << temp1 << endl;
	}
		
	cout << endl;
}

//进行生产和消费
void process() {
	string operate;       //操作
	srand((unsigned)time(NULL));
	int time = 0;
	while (1) {
		time++;
		cout << "请输入要执行的操作(1:继续   0:退出)：";
		//cin >> operate;
		operate = "1";
		if (operate == "1") {    //执行生产或消费
			
			int n = (rand() % (produce.size() + consume.size()));      //通过随机数选择即将运行的进程

			if (products[p] == '\0' && stock.size() == 0 && !isGoing()) {   //当无产品需要生产且缓冲区中产品已被使用时退出
				cout << "生产和消费结束！" << endl;
				break;
			}

			if (n < produce.size() && (products[p] != '\0' || produce[n].breakPoint != 0)) {    //执行生产者进程,且当前无产品需要生产时不执行新的生产者进程

				if (produce[n].status != "等待态") {          
					switch (produce[n].breakPoint) {                               //根据断点信息的不同执行相应操作
					case 0:            //执行生产                                        
						produce[n].breakPoint = 1;                                 //断点信息更新
						produce[n].status = "运行态";                              //状态设为运行态
						cout << produce[n].name << "生产" << products[p] << endl;
						
						produce[n].s = products[p];
						p++;
						break;

					case 1:          //对信号量s2执行p原语
						s2--;          //空闲数自减
						if (s2 < 0) {             //阻塞
							produce[n].status = "等待态";
							produce[n].reason = "等待s2";
							produce[n].t = time;      //保存阻塞时的时间
							cout << produce[n].name << "阻塞" << endl;
						}
						else {
							produce[n].status = "运行态";
							cout << produce[n].name << "执行p(s2)" << endl;
						}
						produce[n].breakPoint = 2;
						break;

					case 2:             //将生产的产品添加到缓冲区中
						stock.push_back(produce[n].s);
						produce[n].breakPoint = 3;
						cout << produce[n].name << "生产的" << produce[n].s << "被添加到缓冲区" << endl;
						break;

					case 3:              //信号量s1自增,若消费者有阻塞的，释放一个消费者进程
						s1++;
						getEarliest(1);
						cout << produce[n].name << "执行v(s1)" << endl;
						produce[n].breakPoint = 4;
						break;

					case 4:              //生产者一个生产流程结束，跳转到断掉信号0
						produce[n].breakPoint = 0;
						produce[n].status = "就绪态";
						cout << produce[n].name << "完成一个生产流程" << endl;
						if (products[p] == '\0') {
							temp1.clear();
							for (int i = 0; i < produce.size(); i++)
								if (i != n) {
									temp1.push_back(produce[i]);
								}
							produce.clear();
							for (int i = 0; i < temp1.size(); i++)
								produce.push_back(temp1[i]);
						}
						break;
					}
					printStatus();
					continue;
				}

				if (produce[n].status == "等待态") {
					cout << produce[n].name << "阻塞" << endl;
					printStatus();
					continue;
				}
				//n2 = n;
			}

			if (n >= produce.size()) {                           //执行消费者进程
				int m = n - produce.size();
				if (consume[m].status != "等待态") {
					char t;   //临时存储产品名
					switch (consume[m].breakPoint) {  //根据断点信息的不同执行不同操作
					case 0:      //信号量s1自减
						s1--;
						if (s1 < 0) {
							consume[m].status = "等待态";
							consume[m].reason = "等待s1";
							consume[m].t = time;      //保存阻塞时间
							cout << consume[m].name << "阻塞" << endl;
						}
						else {
							consume[m].status = "运行态";
							cout << consume[m].name << "执行p(s1)" << endl;
						}
						consume[m].breakPoint = 1;   //更新断点信息
						break;

					case 1:     //随机获缓存区中的产品
						s = rand() % stock.size();
						consume[m].breakPoint = 2;
						cout << consume[m].name << "获取产品" <<stock[s] <<endl;
						break;

					case 2:    //s2空闲数信号量自增,若生产者有阻塞，释放一个生产者进程
						s2++;
						getEarliest(0);
						consume[m].breakPoint = 3;
						cout << consume[m].name << "执行v(s2)" << endl;
						break;

					case 3:   //消费产品,将stock[s]移出
						t = stock[s];
						temp.clear();
						for (int i = 0; i < stock.size(); i++)
							if (i != s) {
								temp.push_back(stock[i]);
							}
						stock.clear();
						for (int i = 0; i < temp.size(); i++)
							stock.push_back(temp[i]);
						consume[m].breakPoint = 4;      //更新断点信息
						cout << consume[m].name << "消费产品" << t << endl;
						break;

					case 4:                        //消费者一个消费流程结束，跳转到断掉信号0
						consume[m].breakPoint = 0;
						consume[m].status = "就绪态";
						cout << consume[m].name << "完成一个消费流程" << endl;
						consume[m].breakPoint = 0;
						break;
					}
					printStatus();
					continue;
				}

				else if (consume[m].status == "等待态") {            //消费者进程仍处于阻塞状态
					cout << consume[m].name << "阻塞" << endl;
					printStatus();
					continue;
				}
			}
		}

		else if (operate == "0")
			break;
	}
}

//判断是否有生产者进程还在运行
bool isGoing() { 
	for (int i = 0; i < produce.size(); i++) {
		if (produce[i].breakPoint > 0 && produce[i].breakPoint <= 2)
			return true;
	}
	return false;
}

//解除最先阻塞的生产者或消费者
void getEarliest(int type) {
	//type: 0代表生产者； 1代表消费者
	int w;                       //保存释放阻塞进程的下标
	int temp = 0;         //保存进程阻塞时的时间
	if (type == 0) {       //释放生产者最先阻塞的进程
		if (produce.size() == 0)
			return;
		
		for (int i = 0; i < produce.size(); i++) {   //任意获取一个阻塞进程的阻塞时间
			if (produce[i].reason == "等待s2") {
				w = i;
				temp = produce[i].t;
			}
		}

		for (int i = 0; i < produce.size(); i++) {   //循环获取最先阻塞进程的下标
			if (produce[i].reason == "等待s2"  && produce[i].t < temp ) {
				w = i;
				temp = produce[i].t;
				break;
			}
		}
		if (temp != 0) {
			produce[w].reason = "";                        //解除阻塞状态
			produce[w].status = "就绪态";
		}
		
	}

	if (type == 1) {             //释放消费者最先阻塞的进程
		if (consume.size() == 0)
			return;
		
		for (int i = 0; i < consume.size(); i++) {    //任意获取一个阻塞进程的阻塞时间
			if (consume[i].reason == "等待s1") {
				temp = consume[i].t;
				w = i;
				break;
			}
		}

		for (int i = 0; i < consume.size(); i++) {   //循环获取最先阻塞进程的下标
			if (consume[i].reason == "等待s1" && consume[i].t < temp) {
				w = i;
				temp = consume[i].t;
			}
		}
		if (temp != 0) {
			consume[w].reason = "";                        //解除阻塞状态
			consume[w].status = "就绪态";
		}
		
	}
}