#include <iostream>
#include <string>

using namespace std;
//
//��������ʵ���״���Ӧ�ڴ�����㷨
//

//�洢�����ṹ��
struct Memery2 {
	int no;                 //������
	int size;               //������С
	int address;        //�����׵�ַ
	string status;      //����״̬,ֻ������״̬�������С����ѷ��䡱
	Memery2 * next;  //ָ����һ��������ָ��
};

void Distribute(Memery2 * head);           //�ڴ��������պ���
void init(Memery2 *head);                      //��ʼ��
void printLinker(Memery2 * head);        //�����������
int getMAX(Memery2 *head, int size);   //ѭ�������ú��ʿ��з�����
int getSum(Memery2 *head, int i);         //���i֮ǰ�ķ�����С�ܺ�
bool isEmpty(Memery2 *head, int i);      //�ж�ĳ�����Ƿ�Ϊ����
void deleteLinker(Memery2 *head);      //����ɾ������

//�����������
void Linker();
