#include "Array.h"

#define MAX 50   //��������
Memery m[MAX];   //��������

//�����������
void Array() {    
	int count = -1;                                     //�ܵķ�����Ŀ
	int no, applySize, initSize;                   //�����ţ���С
	int num = 1;                                       //��ʼ��������
	cout << "�������ʼ������Ŀ��";
	cin >> num;
	cout << "�����������ʼ������С��";
	for (int i = 0; i < num; i++) {
		cin >> initSize;
		if (initSize <= 0) {
			cout << "��ʼ������С���ô���" << endl;
			system("pause");
		}
		count++;
		//��ʼ������
		m[count].no = count + 1;
		m[count].address = getSum(count);
		m[count].size = initSize;
		m[count].status = "����";
		m[count].id = m[count].no;
	}

	//���������
	cout << "������" << "\t" << "��С" << "\t" << "��ʼ��ַ" << "\t" << "״̬" << endl;
	for (int i = 0; i <= count; i++) {
		cout << m[i].no << "\t" << m[i].size << "\t" << m[i].address << "\t" << "\t" << m[i].status << endl;
	}


	while (1) {
		string temp;                 //״̬�жϱ���
		int i = 0;                      //����Ŀռ䱻����Ŀ��
		int num = 0;               //������յĿ��
		cout << "�������ʾ����(���䣺1    ���գ�2    �˳���0 )�� ";
		cin >> temp;
		if (temp == "1") {       //���з������
			cout << "����������ռ�Ĵ�С��";
			cin >> applySize;
			if (applySize <= 0) {
				cout << "����ռ��С����" << endl;
				continue;
			}
			i = getMAX(count, applySize);
			if (i == -1) {              //���Ҫ�����Ŀռ�������Ŀ��з���
				cout << "���㹻���пռ䣡" << endl;
				continue;
			}
			else {                                                           //���пռ�ķ��䣬����ӡ
				for (int j = count; j >= i; j--)                   //���п�ĺ���
				{
					m[j + 1] = m[j];
					m[j + 1].no = m[j + 1].no + 1;           //����Ŀ������
				}
				count++;                                               //�ܷ���������

				m[i].status = "�ѷ���";
				int t = m[i].size;
				m[i].size = applySize;

				m[i + 1].size = t - applySize;
				m[i + 1].status = "����";
				m[i + 1].address = getSum(i);
				m[i + 1].id = m[i].id;

			}
			//���������
			cout << "������" << "\t" << "��С" << "\t" << "��ʼ��ַ" << "\t" << "״̬" << endl;
			for (int i = 0; i <= count; i++) {
				cout << m[i].no << "\t" << m[i].size << "\t" << m[i].address << "\t" << "\t" << m[i].status << endl;
			}
		}

		if (temp == "2") {  // ���л��ղ���
			cout << "��������յķ����ţ�";
			cin >> num;
			num--;              //Ϊ����ʵ�ʵļ��������
			if (num <0 || num > count + 1) {
				cout << "�������������" << endl;
				continue;
			}
			if (m[num].status == "����") {
				cout << "�÷���Ϊ����״̬������Ҫ���գ�" << endl;
				continue;
			}

			//�ϲ����¿�
			if (num > 0 && (num + 1) <= count && m[num - 1].status == "����" && m[num].id == m[num - 1].id&& m[num + 1].status == "����" && m[num].id == m[num + 1].id) {
				m[num - 1].size = m[num - 1].size + m[num].size + m[num + 1].size;
				for (int j = num; j <= count; j++) {   //�����ǰ��
					m[j] = m[j + 2];
					m[j].no = m[j].no - 2;                   //�����ŷ����ı�
				}
				count -= 2;                                      //�ϲ��������С
			}

			//����ÿ���һ��Ϊ������ϲ�������
			else if ((num + 1) <= count && m[num + 1].status == "����" && m[num].id == m[num + 1].id) {   
				m[num].size = m[num].size + m[num + 1].size;
				m[num].status = "����";
				for (int j = num + 1; j <= count; j++) {   //�����ǰ��
					m[j] = m[j + 1];
					m[j].no = m[j].no - 1;                         //�����ŷ����ı�
				}
				count--;                                                 //�ϲ��������С
			}

			//��һ��Ϊ����ʱ���Ϻϲ����ұ�֤Ϊ�����ڵĺϲ�
			else if (num > 0 && m[num - 1].status == "����" && m[num].id == m[num - 1].id) {      
				m[num - 1].size = m[num - 1].size + m[num].size;
				for (int j = num; j <= count; j++) {   //�����ǰ��
					m[j] = m[j + 1];
					m[j].no = m[j].no - 1;                    //�����ŷ����ı�
				}
				count--;                                            //�ϲ��������С
			}

			else {
				m[num].status = "����";
			}

			//���������
			cout << "������" << "\t" << "��С" << "\t" << "��ʼ��ַ" << "\t" << "״̬" << endl;
			for (int i = 0; i <= count; i++) {
				cout << m[i].no << "\t" << m[i].size << "\t" << m[i].address << "\t" << "\t" << m[i].status << endl;
			}
		}

		if (temp == "0")
			break;                //�˳�ѭ��
	}

	system("pause");
}

//���count��ַ
int getSum(int count) {
	int sum = 0;
	for (int i = 0; i <= count; i++) {
		sum += m[i].size;
	}
	return sum;
}

//��������з�����С
int getMAX(int count, int applysize) {
	for (int i = 0; i <= count; i++) {
		if (m[i].size >= applysize && m[i].status == "����") {
			return i;
		}
	}
	return -1;
}