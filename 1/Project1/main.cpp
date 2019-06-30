#include <iostream>
#include <string>
#define MAX 20    //��������

using namespace std;
//
//ʵϰ1��Ŀ���ƣ�����ʱ��Ƭ��ת��ʵ�ִ���������
//

//�������ݽṹ
struct PCB {
	string name;                     //������
	int arrive;                          //���̵���ʱ��
	int need;                           //��������ʱ��
	int count = 0;                   //����������ʱ��
	bool status = true;           //����״̬��true:����   false������   (Ĭ�Ͼ���)
	bool isOK = false;            //��ʾ�����Ƿ��Ѿ���ӵ�ѭ�����У� true��������ӣ�Ĭ��Ϊfalse��
};

PCB p[MAX];                        //�����������
PCB queue[MAX];               //ѭ�����У����ڸ��ǵĿ���
int front = -1, rear = -1;     //��ͷ����βָ��

int main() {

	while (1) {
		int num, time, all = 0;                 //������, ʱ��Ƭ��С, ���н���������ʱ��
		int latest = 0;                             //���̽�����������ʱ�䣬���������̷������
		string isGoOn;                           //�Ƿ�Ҫ��������
		string detail;                              //true���������ϸ��Ϣ��false��ʾ�������ϸ��Ϣ

		cout << "��������̸�����";
		cin >> num;
		if (num > 20) {
			cout << "�������������ֵ��" << endl;
			break;
			system("pause");
		}
		if (num <= 0) {
			cout << "���������Ӧ����0��" << endl;
			system("pause");
		}
		for (int i = 0; i < num; i++) {    //�������ã������ظ�����
			p[i].status = true;
			p[i].isOK = false;
			p[i].count = 0;
		}

		cout << "������ʱ��Ƭ��С��";
		cin >> time;
		if (time <= 0) {
			cout << "ʱ��ƬӦ����0" << endl;
			system("pause");
		}
		cout << "�Ƿ������ϸ���ȹ���(y/n)��";
		cin >> detail;

		cout << "��������������������̵���ʱ��ͽ���Ҫ������ʱ�䣺";
		for (int i = 0; i < num; i++) {
			cin >> p[i].name >> p[i].arrive >> p[i].need;
			all += p[i].need;   //��ʱ��
			if (latest < p[i].arrive)
				latest = p[i].arrive;
		}

		if (detail == "y")
			cout << "������" << "\t" << "������" << "\t" << "״̬" << "\t" << "��ǰʱ��" << endl;
		else
			cout << "������" << "\t" << "���ʱ��" << endl;

		//���ݽ��̵���ʱ���������������ʱ��Ƭδ��������
		for (int i = 0; i < num; i++)
			for (int j = i + 1; j < num; j++) {
				if (p[i].arrive > p[j].arrive) {
					PCB temp = p[i];
					p[i] = p[j];
					p[j] = temp;
				}
			}

		int t = 0;
		while (t < all + latest) {   //��tС����ʱ��ʱ

			if (t <= latest) {    //��С��latestʱ��������Ҫ���������ӽ���
				for (int i = 0; i < num; i++) {
					if (p[i].isOK == false && t >= p[i].arrive) {   //��ѭ����������ӽ���
						p[i].isOK = true;         //��ֹ�ظ����
						rear = (rear + 1) % MAX;
						queue[rear] = p[i];    //������
					}
				}
			}

			if ((rear - front) != 0) {
				front = (front + 1) % MAX;   //������
				if ((queue[front].need - queue[front].count) <= time) {
					if (detail != "y")             //���������Ϣ
						cout << queue[front].name << "\t" << t + queue[front].need - queue[front].count << endl;
					queue[front].status = false;   //���н�����״̬��Ϊfalse

					t += (queue[front].need - queue[front].count);   //��ǰʱ������
					queue[front].count = queue[front].need;
					if (detail == "y")                                                   //���������Ϣ
						cout << queue[front].name << "\t" << queue[front].count << "\t" << queue[front].status << "\t" << t << endl;
					continue;
				}
				else {
					queue[front].count += time;    // ������ʱ������
					t += time;    //t��timeΪ��λ����
					if (t <= latest + time) {    //��С��latestʱ��������Ҫ���������ӽ���
						for (int i = 0; i < num; i++) {
							if (p[i].isOK == false && t >= p[i].arrive) {   //��ѭ����������ӽ���
								p[i].isOK = true;         //��ֹ�ظ����
								rear = (rear + 1) % MAX;
								queue[rear] = p[i];    //������
							}
						}
					}

					rear = (rear + 1) % MAX;
					queue[rear] = queue[front];    //����δ������½������
					if (detail == "y")
						cout << queue[front].name << "\t" << queue[front].count << "\t" << queue[front].status << "\t" << t << endl;
					continue;
				}
			}
			t++;  //������ʱ�䲻����ʱ
		}
		cout << "����ִ���½�����(y/n)��";
		cin >> isGoOn;
		if (isGoOn == "y") {
			continue;
		}

		if (isGoOn == "n")
			system("pause");
		else {
			cout << "�����룺y/s" << endl;
			system("pause");
		}
	}

	system("pause");
	return 0;
}