#include <iostream>
#include <string>
using namespace std;

//
//ʵϰ2���״���Ӧ�㷨ʵ���������ͻ���(����)
//

//�洢�����ṹ��
struct Memery {
	int no;                 //������
	int size;               //������С
	int address;        //�����׵�ַ
	string status;      //����״̬,ֻ������״̬�������С����ѷ��䡱
	int id;                  //�������ֳ�ʼ��������ֹ��ʼ�����໥�ϲ�
};


int getSum(int count);   //���count��ַ
int getMAX(int count, int applysize); //��������з�����С

//�����������
void Array();
