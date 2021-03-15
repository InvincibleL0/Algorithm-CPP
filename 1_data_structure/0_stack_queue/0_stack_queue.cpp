#include<iostream>
using namespace std;
/*
C++标准库中已包含栈和队列这两种顺序容器，只需包含头文件即可
#include<stack>
#include<queue>
定义方法：
stack<int> stack0;
queue<int> queue0;
stack常用操作：stack0.empty()、stack0.size()、stack0.push(item)、stack0.pop()、stack0.top()返回栈顶元素但不弹出
queue常用操作：queue0.empty()、queue0.size()、queue0.push(item)、queue0.pop()、stack0.back()返回队尾但不删除
*/

//下面用数组实现一个固定容量的栈和队列
constexpr int stack_size = 2;
constexpr int queue_size = 2;
class stack
{
private:
	int arr[stack_size]{};
	int index;

public:
	stack()//构造函数
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
		index1 = 0;//入队索引
		index2 = 0;//出队索引
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
			index2 = 0;//队列已清空，为下一次出队做准备
		}
		else
			cout << arr[index2++] << ",count of number in queue is " << --index1 << endl;
	}
};
int main()
{
	stack stack0;		//实例化一个stack对象
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