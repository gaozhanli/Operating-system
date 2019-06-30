#include <iostream>
#include <string>
#define MAX_GROUP 100    //�������
#define MAX_BLOCK  100    //һ��������

using namespace std;
//
//���ÿռ��������ӷ�ʵ�ִ��̴洢�ռ�Ĺ���
//

//������
struct Block {
	int no;        //���
	string status; //״̬
};
//������
struct Group {
	int size;      //���п�ĸ���
	Block blocks[MAX_BLOCK]; //���п�����
	Group * next;          //ָ����һ���ָ��
};


void init();                              //��ʼ������
void printBlock();                  //����ѷ���Ŀ��
void printGroup();                //������п��п����Ϳ��
void deleteLinker(Group * head); //��������
int getMax();                         //��ȡʣ����п���
bool getStatus(int no);         //��ȡ�ض���ŵ�״̬
Block getBlock(int no);         //���ݿ���ҵ���
void operation();                  //���пռ�ķ���ͻ���


int group, block, all;                //������һ��������ܿ���
Group *A = new Group;         //���̿�����ͷ���
Group * MA = new Group;    //ר�ÿ���ָ��
Block B[MAX_GROUP*MAX_BLOCK];   //���������ѷ���Ŀ�
int num = -1;                                         //B�±�