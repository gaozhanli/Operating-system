#include "Linker.h"

static int counts = 0;                           //�ܵķ�����,��ʼΪ0

//�����������
void Linker() {
	Memery2 *head = new Memery2;      //����ͷָ��
	init(head);   //��ʼ��
	printLinker(head);
	Distribute(head);          //�ڴ���������
	deleteLinker(head);     //ɾ������
	system("pause");
}

//��ʼ��
void init(Memery2 *head) {    
	counts ++;                               
	int initSize;            //�����ţ���С
	cout << "�������ʼ������С��";
	cin >> initSize;
	if (initSize <= 0) {
		cout << "��ʼ������С���ô���";
		system("pause");   //��ͣ����ִ��
	}

	head->no = 1;
	head->size = initSize;
	head->status = "����";
	head->address = 0;
	head->next = NULL;
}

//�����������
void printLinker(Memery2 * head) {    
	Memery2 * p = head;
	cout << "������" << "\t" << "��С" << "\t" << "��ʼ��ַ" << "\t" << "״̬" << endl;
	while (p != NULL) {
		cout << p->no << "\t" << p->size << "\t" << p->address << "\t" << "\t" << p->status << endl;
		p = p->next;
	}
}

//�ڴ��������պ���
void Distribute(Memery2 * head) {    
	Memery2 * p = head;
	string operation;  //����
	int applySize, i = 0;   //����ռ䣬���з�����
	while (1) {
		cout << "�������ʾ����(���䣺1    ���գ�2    �˳���0 )�� ";
		cin >> operation;

		if (operation == "1") {   //�����ڴ����
			cout << "����������ռ�Ĵ�С��";
			cin >> applySize;
		    if (applySize <= 0) {
				cout << "����ռ��С����" << endl;
				continue;
			}
			i = getMAX(head, applySize);

			if (i == -1) {
				cout << "���㹻���пռ䣡" << endl;
			    continue;
			}
			else {    
				while (p->no != i)                           //iΪ���з����ţ����пռ�ķ���
					p = p->next;
				int temp = p->size - applySize;     //����֮��ʣ��Ŀ��з�����С
				p->size = applySize;
				p->status = "�ѷ���";

				Memery2 * q = new Memery2;       //����֮��������µĿ��з���
				q->no = p->no + 1;
				q->address = getSum(head,q->no);
				q->size = temp;
				q->status = "����";
				q->next = p->next;

				p->next = q;
				q = q->next;
				while (q != NULL) {                          //���������ķ���������
					q->no = q->no + 1;
					q = q->next;
				}
				counts++;                                       //����������
				printLinker(head);                           //��ӡ
			}

		}

		else if (operation == "2") {  //���շ���Ŀռ�
			int no;
			cout << "������Ҫ���յķ����ţ�";
			cin >> no;
			if (no<0 || no > counts) {
				cout << "�������������" << endl;
				continue;
			}
			if (isEmpty(head,no)) {
				cout << "�÷���Ϊ����״̬������Ҫ���գ�" << endl;
				continue;
			}

			if (no > 0 && no < counts && isEmpty(head, no - 1) && isEmpty(head, no + 1)) {   //��Ҫ���յķ��������¾�Ϊ����ʱ��ֱ�Ӻϲ�
				p = head;
				while (p != NULL && p->no != (no - 1))
					p = p->next;
				Memery2 *temp1 = p->next;
				Memery2 *temp2 = temp1->next;

				p->next = temp2->next;
				p->size = p->size + temp1->size + temp2->size;   //�ϲ�

				while (p->next != NULL) {    //�ϲ������Ŀ��кż�2
					p = p->next;
					p->no -= 2;
				}
			}

			else if (no > 0 && isEmpty(head, no - 1)) {            //����һ��ϲ�
				p = head;
				while (p != NULL && p->no != (no - 1))
					p = p->next;
				Memery2 *temp1 = p->next;

				p->next = temp1->next;
				p->size = p->size + temp1->size;

				while (p->next != NULL) {
					p = p->next;
					p->no--;
				}
			}

			else if (no < counts && isEmpty(head, no + 1)) {    //����һ��ϲ�
				p = head;
				while (p != NULL && p->no != no)
					p = p->next;
				Memery2 *temp1 = p->next;

				p->next = temp1->next;
				p->size = p->size + temp1->size;

				while (p->next != NULL) {
					p = p->next;
					p->no--;
				}
			}

			else {
				p = head;
				while (p != NULL && p->no != no)
					p = p->next;
				p->status = "����";
			}
			printLinker(head);    //����ϲ��������
		}

		else if(operation == "0")    //�˳�
			break;
	}
}

//���i֮ǰ�ķ�����С�ܺ�
int getSum(Memery2 *head, int i) {
	//cout << head->size;
	Memery2 * p = head;
	int sum = 0;
	while (p!= NULL && p->no != i) {
		sum += p->size;
		p = p->next;
	}
	return sum;
}

//����ɾ������
void deleteLinker(Memery2 *head) {    
	Memery2 * p;
	while (head != NULL) {
		p = head->next;
		delete head;
		head = p;
	}
}

//�ж�ĳ�����Ƿ�Ϊ����
bool isEmpty(Memery2 *head, int i) {
	Memery2 * p = head;
	while (p != NULL && p->no != i)
		p = p->next;
	if (p != NULL && p->status == "����")
		return true;
	else
		return false;
}

//ѭ�������ú��ʿ��з�����
int getMAX(Memery2 *head, int size) {
	Memery2 * p = head;
	int num = 0;
	while (p != NULL) {
		num++;
		if (p->size >= size && p->status == "����")
			return num;
		p = p->next;
	}
	return -1;
}