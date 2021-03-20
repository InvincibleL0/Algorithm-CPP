#include<iostream>
#include<thread>
using namespace std;
/*
C++11�м�����<thread>ͷ�ļ�����ͷ�ļ���Ҫ������std::thread�߳��ࡣC++11�ı�׼��std::thread���߳̽����˷�װ��
������C++11��׼�е�һЩ��ʾ�̵߳��ࡢ���ڻ�����ʵ����뷽���ȡ�Ӧ��C++11�е�std::thread���ڶ��̳߳������ֵ��

std::thread�๹�캯����
��1��Ĭ�Ϲ��캯��������һ���յ� std::thread ִ�ж���
	thread() noexcept
��2����ʼ�����캯��������һ�� std::thread ���󣬸� std::thread ����ɱ� joinable���²������̻߳���� fn �������ú����Ĳ����� args ������
	template <class Fn, class... Args> explicit thread(Fn&& fn, Args&&... args);
��3���������캯��(������)����ζ�� std::thread ���󲻿ɿ������졣
	thread(const thread&) = delete;
��4��move���캯�������óɹ�֮�� _Other �������κ� std::thread ִ�ж���
	thread(thread&& _Other) noexcept

std::thread���Ա������
��1��id get_id()����ȡ�߳�ID������һ������Ϊ std::thread::id �Ķ���
��2��void join()�����øú�����������ǰ�̡߳�����������(caller)���ڵ��߳�ֱ���� join �� std::thread �����ʶ���߳�ִ�н��������̵߳������̣߳����߳��������߳�ֱ�����߳�ִ����ϡ�
��3��void detach()������ǰ�̶߳����������ִ��ʵ������̶߳�����룬ʹ���̵߳�ִ�п��Ե������С�һ���߳�ִ����ϣ������������Դ���ᱻ�ͷš����̲߳��������̡߳�
��4��void joinable()������߳��Ƿ�ɱ� join����鵱ǰ���̶߳����Ƿ��ʾ��һ�����ִ���̣߳���Ĭ�Ϲ��캯���������߳��ǲ��ܱ� join �ġ�
	���⣬���ĳ���߳� �Ѿ�ִ�������񣬵���û�б� join �Ļ������߳���Ȼ�ᱻ��Ϊ��һ�����ִ���̣߳����Ҳ�ǿ��Ա� join �ġ�
��5��void swap(thread&)�����������̶߳���������ĵײ�����
��6��thread& operator=(thread&& _Other) noexcept		Move ��ֵ����(1)�������ǰ���󲻿� joinable����Ҫ����һ����ֵ����(rhs)�� move ��ֵ�����������ǰ����ɱ� joinable�������� terminate() ����
	thread& operator=(const thread&) = delete;������ֵ����(2)�������ã���� std::thread ���󲻿ɿ�����ֵ��
��7��static unsigned int hardware_concurrency()����̬��Ա���������ص�ǰ���������Ӳ�������߳���Ŀ���� R7 4800H Ϊ�����˺�ʮ���߳� CPU �� hardware_concurrency() ����ֵΪ16��
��8��void* native_handle���ú��������� std::thread ����ʵ����ص��߳̾����native_handle_type ������ thread ��Ͳ���ϵͳ SDK API ֮������������� Linux g++(libstdc++) �
	native_handle_type ��ʵ���� pthread ����� pthread_t ���ͣ��� thread ��Ĺ��ܲ����������ǵ�Ҫ���ʱ��(����ı�ĳ���̵߳����ȼ�)������ͨ�� thread ��ʵ���� native_handle() ����ֵ
	��Ϊ������������ص� pthread �����ﵽĿ¼��
*/

void func1(int n)
{
	for (int i = 0; i < 5; ++i)
	{
		cout << "func1:" << ++n << endl;
	}
}
void func2(int n)
{
	for (int i = 0; i < 5; ++i)
	{
		cout << "func2:" << ++n << endl;
	}
}

void independentThread()
{
	cout << "Starting concurrent thread.\n";
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Exiting concurrent thread.\n";//threadCaller()��join�Ķ�independentThread()��detech�ģ�����threadCaller()������֮�����߳̽�������һ�䲻����ʾ������
}

void threadCaller()
{
	cout << "Starting thread caller.\n";
	thread t(independentThread);
	t.detach();
	this_thread::sleep_for(chrono::seconds(1));
	cout << "Exiting thread caller.\n";
}

/*
std::mutex��std::lock_guard��ʹ��
�ڶ��̻߳����У��ж���߳̾���ͬһ��������Դ���ͺ����������̰߳�ȫ�����⡣��˾���Ҫ�������Ļ��ƣ�����֤����ʱ��ֻ��һ���߳��ڷ��ʹ�����Դ��
��1��ͷ�ļ���#include<mutex>��mutex��������֤�߳�ͬ���ģ���ֹ��ͬ���߳�ͬʱ����ͬһ���������ݡ�
��2����ʹ��lock_guard����԰�ȫ�����ǻ���������ģ��ܹ��Խ��������ö��󴴽�ʱ��������m.lock()һ����û�������
	���������ڽ���ʱ�������Զ�����(unlock)��������Ϊĳ���߳��쳣�˳���Ӱ�������̡߳�
��3������ڵݹ麯���ж�ζ�ͬһ����������������std::mutex�Ǹ��ǵݹ�������������������������ʱ��ʹ��mutex���е�recursive_mutex�Ϳ��Ա������������
*/
#include<mutex>
int cnt = 20;
mutex m;

void mutexThread1()
{
	while (cnt > 0)
	{
		lock_guard<mutex> lockGuard(m);
		//m.lock();
		if (cnt > 0)
		{
			--cnt;
			cout << cnt << endl;
		}
		//m.unlock();
	}
	cnt = 20;
}
void mutexThread2()
{
	while (cnt > 0)
	{
		lock_guard<mutex> lockGuard(m);
		//m.lock();
		if (cnt > 0)
		{
			--cnt;
			cout << cnt << endl;
		}
		//m.unlock();
	}
}

int main()
{
	unsigned int n = thread::hardware_concurrency();
	cout << n << " concurrent threads are supported.\n";

	thread t1(func1, n);
	thread t2(func2, n);
	thread t3(move(t2));
	thread t4(threadCaller);

	cout << "t1's ID is:" << t1.get_id() << endl;
	cout << "t2's ID is:" << t2.get_id() << endl;
	cout << "t3's ID is:" << t3.get_id() << endl;
	cout << "t4's ID is:" << t4.get_id() << endl;

	t1.join();
	t3.join();
	t4.join();

	thread t5(mutexThread1);
	thread t6(mutexThread2);
	t5.join();
	t6.join();

	return 0;
}