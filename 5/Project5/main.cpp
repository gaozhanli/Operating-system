#include <iostream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

#define MAX 50          //����Ʒ��
//
//ʵϰ5:ģ��P��V����ʵ��ͬ������������P��V������������ߡ�������������
//

//���̿��ƿ�����
struct PCB {
	string name;         //������
	string status;        //����״̬������̬������̬���ȴ�̬�����̬
	string reason;       //�ȴ�ԭ��
	int  breakPoint;    //�ϵ���Ϣ��ʹ��int���ͱ������ж����е���λ��
	char s;                  //������Ҫ�����Ĳ�Ʒ
	int t;                     //����ѭ��
};

void init();                //��ʼ�������ߺ��������Լ������ź���
void printStatus();   //�������ģ�����״̬
void process();        //��������������
bool isGoing();        //�ж��Ƿ��������߽��̻�������
void getEarliest(int type); //������������������߻�������


//����������
vector<PCB> consume;
//����������
vector <PCB> produce;
//���������飬���ڱ��������Ĳ�Ʒ
vector <char> stock;
int s;               //ָ���ȡ�Ĳ�Ʒ
//��������������ʱ�䵱stock����ʱ�洢
vector<char> temp;
vector<PCB> temp1;         //��ʱ�洢��������Ϣ


//���ʻ����ź���
int s1, s2;           //s1��ʾ��Ʒ���� s2��ʾ���������������Ϊ��������С
char products[MAX];          //��Ҫ�����Ĳ�Ʒ
int p = 0;                           //products�����±�

int main() {
	init();
	printStatus();
	process();

	system("pause");
	return 0;
}

//��ʼ�������ߺ��������Լ������ź���
void init() {
	int snum, pnum;    //�����ߺ������߸���
	cout << "���������������ߺ������߸�����";
	cin >> pnum >> snum;
	if (snum <= 0 || pnum <= 0) {
		cout << "�������" << endl;
		system("pause");      //������������ͣ������Ŀ������
	}

	//����������ģ�����
	for (int i = 1; i <= snum; i++) {
		PCB *p = new PCB;
		p->name = "s" + to_string(i);
		p->status = "����̬";           //��ʼ״̬��Ϊ����̬
		p->reason = "";                    //��Ϊ��
		p->breakPoint = 0;               //��ʼ����λ��Ϊ0
		consume.push_back(*p);       //��ӵ�consume������
	}
	
	//����������ģ�����
	for (int i = 1; i <= pnum; i++) {
		PCB *p = new PCB;
		p->name = "p" + to_string(i);
		p->status = "����̬";           //��ʼ״̬��Ϊ����̬
		p->reason = "";                    //��Ϊ��
		p->breakPoint = 0;               //��ʼ����λ��Ϊ0
		produce.push_back(*p);        //��ӵ�produce������
	}

	int all;                   //��������С
	cout << "�����뻺������С��";
	cin >> all;
	if (all <= 0) {
		cout << "�������!" << endl;
		system("pause");                     //������������ͣ��Ŀִ��
	}
	s1 = 0, s2 = all;                           //�������ź�������ֵ

	cout << "��������Ҫ�����Ĳ�Ʒ��";
	cin >> products;                         //��ʼ����Ʒ����

	//��Ʒ����;
	int j = 0;
	while (products[j] != '\0')
		j++;
}

//�������ģ�����״̬
void printStatus() {
	cout << "������" << "\t" << "״̬" << "\t" <<"�ȴ�ԭ��" << "\t" <<"�ϵ�"<< endl;
	string temp1;

	//���������״̬
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
		

	//���������״̬
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

//��������������
void process() {
	string operate;       //����
	srand((unsigned)time(NULL));
	int time = 0;
	while (1) {
		time++;
		cout << "������Ҫִ�еĲ���(1:����   0:�˳�)��";
		//cin >> operate;
		operate = "1";
		if (operate == "1") {    //ִ������������
			
			int n = (rand() % (produce.size() + consume.size()));      //ͨ�������ѡ�񼴽����еĽ���

			if (products[p] == '\0' && stock.size() == 0 && !isGoing()) {   //���޲�Ʒ��Ҫ�����һ������в�Ʒ�ѱ�ʹ��ʱ�˳�
				cout << "���������ѽ�����" << endl;
				break;
			}

			if (n < produce.size() && (products[p] != '\0' || produce[n].breakPoint != 0)) {    //ִ�������߽���,�ҵ�ǰ�޲�Ʒ��Ҫ����ʱ��ִ���µ������߽���

				if (produce[n].status != "�ȴ�̬") {          
					switch (produce[n].breakPoint) {                               //���ݶϵ���Ϣ�Ĳ�ִͬ����Ӧ����
					case 0:            //ִ������                                        
						produce[n].breakPoint = 1;                                 //�ϵ���Ϣ����
						produce[n].status = "����̬";                              //״̬��Ϊ����̬
						cout << produce[n].name << "����" << products[p] << endl;
						
						produce[n].s = products[p];
						p++;
						break;

					case 1:          //���ź���s2ִ��pԭ��
						s2--;          //�������Լ�
						if (s2 < 0) {             //����
							produce[n].status = "�ȴ�̬";
							produce[n].reason = "�ȴ�s2";
							produce[n].t = time;      //��������ʱ��ʱ��
							cout << produce[n].name << "����" << endl;
						}
						else {
							produce[n].status = "����̬";
							cout << produce[n].name << "ִ��p(s2)" << endl;
						}
						produce[n].breakPoint = 2;
						break;

					case 2:             //�������Ĳ�Ʒ��ӵ���������
						stock.push_back(produce[n].s);
						produce[n].breakPoint = 3;
						cout << produce[n].name << "������" << produce[n].s << "����ӵ�������" << endl;
						break;

					case 3:              //�ź���s1����,���������������ģ��ͷ�һ�������߽���
						s1++;
						getEarliest(1);
						cout << produce[n].name << "ִ��v(s1)" << endl;
						produce[n].breakPoint = 4;
						break;

					case 4:              //������һ���������̽�������ת���ϵ��ź�0
						produce[n].breakPoint = 0;
						produce[n].status = "����̬";
						cout << produce[n].name << "���һ����������" << endl;
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

				if (produce[n].status == "�ȴ�̬") {
					cout << produce[n].name << "����" << endl;
					printStatus();
					continue;
				}
				//n2 = n;
			}

			if (n >= produce.size()) {                           //ִ�������߽���
				int m = n - produce.size();
				if (consume[m].status != "�ȴ�̬") {
					char t;   //��ʱ�洢��Ʒ��
					switch (consume[m].breakPoint) {  //���ݶϵ���Ϣ�Ĳ�ִͬ�в�ͬ����
					case 0:      //�ź���s1�Լ�
						s1--;
						if (s1 < 0) {
							consume[m].status = "�ȴ�̬";
							consume[m].reason = "�ȴ�s1";
							consume[m].t = time;      //��������ʱ��
							cout << consume[m].name << "����" << endl;
						}
						else {
							consume[m].status = "����̬";
							cout << consume[m].name << "ִ��p(s1)" << endl;
						}
						consume[m].breakPoint = 1;   //���¶ϵ���Ϣ
						break;

					case 1:     //����񻺴����еĲ�Ʒ
						s = rand() % stock.size();
						consume[m].breakPoint = 2;
						cout << consume[m].name << "��ȡ��Ʒ" <<stock[s] <<endl;
						break;

					case 2:    //s2�������ź�������,�����������������ͷ�һ�������߽���
						s2++;
						getEarliest(0);
						consume[m].breakPoint = 3;
						cout << consume[m].name << "ִ��v(s2)" << endl;
						break;

					case 3:   //���Ѳ�Ʒ,��stock[s]�Ƴ�
						t = stock[s];
						temp.clear();
						for (int i = 0; i < stock.size(); i++)
							if (i != s) {
								temp.push_back(stock[i]);
							}
						stock.clear();
						for (int i = 0; i < temp.size(); i++)
							stock.push_back(temp[i]);
						consume[m].breakPoint = 4;      //���¶ϵ���Ϣ
						cout << consume[m].name << "���Ѳ�Ʒ" << t << endl;
						break;

					case 4:                        //������һ���������̽�������ת���ϵ��ź�0
						consume[m].breakPoint = 0;
						consume[m].status = "����̬";
						cout << consume[m].name << "���һ����������" << endl;
						consume[m].breakPoint = 0;
						break;
					}
					printStatus();
					continue;
				}

				else if (consume[m].status == "�ȴ�̬") {            //�����߽����Դ�������״̬
					cout << consume[m].name << "����" << endl;
					printStatus();
					continue;
				}
			}
		}

		else if (operate == "0")
			break;
	}
}

//�ж��Ƿ��������߽��̻�������
bool isGoing() { 
	for (int i = 0; i < produce.size(); i++) {
		if (produce[i].breakPoint > 0 && produce[i].breakPoint <= 2)
			return true;
	}
	return false;
}

//������������������߻�������
void getEarliest(int type) {
	//type: 0���������ߣ� 1����������
	int w;                       //�����ͷ��������̵��±�
	int temp = 0;         //�����������ʱ��ʱ��
	if (type == 0) {       //�ͷ����������������Ľ���
		if (produce.size() == 0)
			return;
		
		for (int i = 0; i < produce.size(); i++) {   //�����ȡһ���������̵�����ʱ��
			if (produce[i].reason == "�ȴ�s2") {
				w = i;
				temp = produce[i].t;
			}
		}

		for (int i = 0; i < produce.size(); i++) {   //ѭ����ȡ�����������̵��±�
			if (produce[i].reason == "�ȴ�s2"  && produce[i].t < temp ) {
				w = i;
				temp = produce[i].t;
				break;
			}
		}
		if (temp != 0) {
			produce[w].reason = "";                        //�������״̬
			produce[w].status = "����̬";
		}
		
	}

	if (type == 1) {             //�ͷ����������������Ľ���
		if (consume.size() == 0)
			return;
		
		for (int i = 0; i < consume.size(); i++) {    //�����ȡһ���������̵�����ʱ��
			if (consume[i].reason == "�ȴ�s1") {
				temp = consume[i].t;
				w = i;
				break;
			}
		}

		for (int i = 0; i < consume.size(); i++) {   //ѭ����ȡ�����������̵��±�
			if (consume[i].reason == "�ȴ�s1" && consume[i].t < temp) {
				w = i;
				temp = consume[i].t;
			}
		}
		if (temp != 0) {
			consume[w].reason = "";                        //�������״̬
			consume[w].status = "����̬";
		}
		
	}
}