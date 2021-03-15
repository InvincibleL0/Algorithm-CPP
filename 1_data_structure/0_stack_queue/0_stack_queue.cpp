#include<iostream>
using namespace std;
/*
C++��׼�����Ѱ���ջ�Ͷ���������˳��������ֻ�����ͷ�ļ�����
#include<stack>
#include<queue>
���巽����
stack<int> stack0;
queue<int> queue0;
stack���ò�����stack0.empty()��stack0.size()��stack0.push(item)��stack0.pop()��stack0.top()����ջ��Ԫ�ص�������
queue���ò�����queue0.empty()��queue0.size()��queue0.push(item)��queue0.pop()��stack0.back()���ض�β����ɾ��
*/

//����������ʵ��һ���̶�������ջ�Ͷ���
constexpr int stack_size = 2;
constexpr int queue_size = 2;
class stack
{
private:
	int arr[stack_size]{};
	int index;

public:
	stack()//���캯��
	{
		index = 0;
	}
	void push(int num)
	{
		if (index == stack_size)
			cout << "stack overflow !" << endl;
		else
		{
			arr[index++] = num;
			cout << "count of number in stack is " << index << endl;
		}
	}
	void pop()
	{
		if (index == 0)
			cout << "stack underflow !" << endl;
		else
			cout << arr[--index] << ",count of number in stack is " << index << endl;
	}
};
class queue
{
private:
	int arr[queue_size]{};
	int index1, index2;
public:
	queue()
	{
		index1 = 0;//�������
		index2 = 0;//��������
	}
	void push(int num)
	{
		if (index1 == queue_size)
			cout << "queue overflow !" << endl;
		else
		{
			arr[index1++] = num;
			cout << "count of number in queue is " << index1 << endl;
		}
	}
	void pop()
	{
		if (index1 == 0 || index2 == queue_size)
		{
			cout << "queue underflow !" << endl;
			index2 = 0;//��������գ�Ϊ��һ�γ�����׼��
		}
		else
			cout << arr[index2++] << ",count of number in queue is " << --index1 << endl;
	}
};
int main()
{
	stack stack0;		//ʵ����һ��stack����
	stack0.pop();		//stack underflow !
	stack0.push(9681);	//count of number in stack is 1
	stack0.push(421);	//count of number in stack is 2
	stack0.push(666);	//stack overflow !
	stack0.pop();		//421,count of number in stack is 1
	stack0.pop();		//9681,count of number in stack is 0
	stack0.pop();		//stack underflow !
	cout << endl;
	queue queue0;
	queue0.pop();		//queue underflow !
	queue0.push(9681);	//count of number in queue is 1
	queue0.push(421);	//count of number in queue is 2
	queue0.push(666);	//queue overflow !
	queue0.pop();		//9681,count of number in queue is 1
	queue0.pop();		//421,count of number in queue is 0
	queue0.pop();		//queue underflow !
	queue0.push(9681);	//count of number in queue is 1
	queue0.push(421);	//count of number in queue is 2
	queue0.push(666);	//queue overflow !
	queue0.pop();		//9681,count of number in queue is 1
	queue0.pop();		//421,count of number in queue is 0
	queue0.pop();		//queue underflow !

	return 0;
}