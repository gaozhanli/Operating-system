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

//��ʼ������
void init() {
	cout << "������ô洢�ռ��ܿ�����";
	cin >> all;
	if (all <= 0 || all > MAX_GROUP * MAX_BLOCK) {
		cout << "�������" << endl;
		system("pause");
	}
	cout << "������һ����������";
	cin >> block;
	if (block <= 0 || block > MAX_BLOCK) {
		cout << "�������" << endl;
		system("pause");

	}
	group = (all + block - 1) / block;    //����

	//��ʼ��A
	A->size = 0;
	A->next = NULL;

	Group *p = A;
	int n = 1;   //���
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

		for (int j = 0; j < block; j++) {   //�����п鸳���
			if ((i*block + j + 1) <= all) {
				p->blocks[p->size].no = n++;
				p->blocks[p->size].status = "δ����";
				p->size++;                      //��������
			}
		}
	}

	//��ʼ��MA
	MA->next = A->next;    //��A�ĵ�һ������MA
	MA->size = A->next->size;
	if (A->next != NULL) {
		A->next = A->next->next;
		MA->next->next = NULL;
	}
}

//����ѷ���Ŀ��
void printBlock() {
	cout << "�ѷ���Ŀ��Ϊ��";
	if (num == -1)
		cout << "��";
	else {
		int n = num;
		while (n >= 0 ) {
			if(B[n].status == "�ѷ���")
				cout << B[n].no << "  ";
			n--;
		}
	}
	cout << endl;
}

//������п��п����Ϳ��
void printGroup() {
	//�����ר�ÿ��п��п�Ϳ��
	cout << "����" << "\t"<< "���п���" << "\t" <<"���" << "\t" << endl;
	int i = 0;
	if(MA->next != NULL)
		 i= MA->next->size -1;
	int g = 0;     //����
	while (i >= 0 && MA->next != NULL) 
		cout << g<< "\t" << MA->next->size << "\t" << "\t" << MA->next->blocks[i--].no << endl;  //MA����0��
	g++;

	//���A
	Group * p = A->next;
	while (p != NULL) {
		int j = p->size - 1;
		while (j >= 0)
			cout << g << "\t" << p->size << "\t" << "\t" << p->blocks[j--].no << endl;
		g++;
		p = p->next;
	}
}

//��������
void deleteLinker(Group * head) {
	Group * p = head->next;
	delete head;
	while (p != NULL) {
		Group * temp = p->next;
		delete p;
		p = temp;
	}
}

//��ȡ�ض���ŵ�״̬
bool getStatus(int no) {
	int n = num;
	while (n >= 0) {
		if (B[n].no == no && B[n].status == "�ѷ���")
			return true;
		n--;
	}
	return false;
}

//���ݿ���ҵ���
Block getBlock(int no) {
	Block t;
	int n = num;
	while (n >= 0) {
		if (B[n].no == no && B[n].status == "�ѷ���") {
			B[n].status = "����";
			return B[n];
		}
		n--;
	}
	return t;
}

//��ȡʣ����п���
int getMax() {
	int sum = 0;
	Group * p = A->next;
	while (p != NULL) {
		sum += p->size;
		p = p->next;
	}
	return sum + MA->next->size;
}

//���пռ�ķ���ͻ���
void operation() {
	string operate;
	int size = 0;     //����Ŀ���
	int no;             //���յĿ��
	while (1) {
		cout << "�������ʾ���룺��1:����   2:����   0:�˳���";
		cin >> operate;
		if (operate == "1") {   //����
			cout << "���������������";
			cin >> size;
			if (size <= 0 || size > all) {
				cout << "�������! " << endl;
				continue;
			}
			else if (size > getMax()) {
				cout << "ʣ��ռ䲻�㣡" << endl;
				continue;
			}
			else {  //���з���
				if (size < MA->next->size) {   //�������С�ڿ��п���ʱ
					while (size > 0) {
						MA->next->blocks[MA->next->size - 1].status = "�ѷ���";
						num++;
						B[num] = MA->next->blocks[MA->next->size - 1];
						MA->next->size--;            //ר�ÿ���п����Լ�
						size--;
					}
				}
				else {          //����������ڻ���ڿ��п���ʱ
					while (size > 0) {
						MA->next->blocks[MA->next->size - 1].status = "�ѷ���";
						num++;
						B[num] = MA->next->blocks[MA->next->size - 1];
						MA->next->size--;            //ר�ÿ���п����Լ�

						if (MA->next->size == 0) {   //���µ��鸴�Ƶ�MA
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
		else if (operate == "2") {  //����
			cout << "��������յĿ�ţ�";
			cin >> no;
			if (no <= 0 || no > all) {
				cout << "�������" << endl;
				continue;
			}
			else if (!getStatus(no)) {
				cout << "�ÿ�Ϊ����״̬������Ҫ���գ�" << endl;
				continue;
			}
			else {  //���л���
				if (MA->next == NULL) {
					Group * p = new Group;
					p->next = NULL;
					p->size = 0;
					MA->next = p;
				}
				if (MA->next->size == block) {   //��ʱMAר�ÿ�����
					Group * p = new Group;
					p->next = NULL;
					p->size = 0;

					MA->next->next = A->next;  //��MA��ӵ�A��
					A->next = MA->next;
					MA->next = p;
				}

				Block q = getBlock(no);              //�����п���ӵ�MA
				MA->next->size++;
				MA->next->blocks[MA->next->size - 1] = q;
			}
			printBlock();
			printGroup();
		}

		else if (operate == "0") {  //�˳�
			break;
		}
	}
}