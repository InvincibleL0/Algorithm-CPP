#include<iostream>
#include<thread>
using namespace std;
/*
C++11中加入了<thread>头文件，此头文件主要声明了std::thread线程类。C++11的标准类std::thread对线程进行了封装，
定义了C++11标准中的一些表示线程的类、用于互斥访问的类与方法等。应用C++11中的std::thread便于多线程程序的移值。

std::thread类构造函数：
（1）默认构造函数，创建一个空的 std::thread 执行对象。
	thread() noexcept
（2）初始化构造函数，创建一个 std::thread 对象，该 std::thread 对象可被 joinable，新产生的线程会调用 fn 函数，该函数的参数由 args 给出。
	template <class Fn, class... Args> explicit thread(Fn&& fn, Args&&... args);
（3）拷贝构造函数(被禁用)，意味着 std::thread 对象不可拷贝构造。
	thread(const thread&) = delete;
（4）move构造函数，调用成功之后 _Other 不代表任何 std::thread 执行对象。
	thread(thread&& _Other) noexcept

std::thread类成员函数：
（1）id get_id()：获取线程ID，返回一个类型为 std::thread::id 的对象。
（2）void join()：调用该函数会阻塞当前线程。阻塞调用者(caller)所在的线程直至被 join 的 std::thread 对象标识的线程执行结束。主线程调用子线程，子线程阻塞主线程直至子线程执行完毕。
（3）void detach()：将当前线程对象所代表的执行实例与该线程对象分离，使得线程的执行可以单独进行。一旦线程执行完毕，它所分配的资源将会被释放。子线程不阻塞主线程。
（4）void joinable()：检查线程是否可被 join。检查当前的线程对象是否表示了一个活动的执行线程，由默认构造函数创建的线程是不能被 join 的。
	另外，如果某个线程 已经执行完任务，但是没有被 join 的话，该线程依然会被认为是一个活动的执行线程，因此也是可以被 join 的。
（5）void swap(thread&)：交换两个线程对象所代表的底层句柄。
（6）thread& operator=(thread&& _Other) noexcept		Move 赋值操作(1)，如果当前对象不可 joinable，需要传递一个右值引用(rhs)给 move 赋值操作；如果当前对象可被 joinable，则会调用 terminate() 报错。
	thread& operator=(const thread&) = delete;拷贝赋值操作(2)，被禁用，因此 std::thread 对象不可拷贝赋值。
（7）static unsigned int hardware_concurrency()：静态成员函数，返回当前计算机最大的硬件并发线程数目，以 R7 4800H 为例，八核十六线程 CPU 的 hardware_concurrency() 返回值为16。
（8）void* native_handle：该函数返回与 std::thread 具体实现相关的线程句柄。native_handle_type 是连接 thread 类和操作系统 SDK API 之间的桥梁，如在 Linux g++(libstdc++) 里，
	native_handle_type 其实就是 pthread 里面的 pthread_t 类型，当 thread 类的功能不能满足我们的要求的时候(比如改变某个线程的优先级)，可以通过 thread 类实例的 native_handle() 返回值
	作为参数来调用相关的 pthread 函数达到目录。
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
	cout << "Exiting concurrent thread.\n";//threadCaller()是join的而independentThread()是detech的，所以threadCaller()运行完之后主线程结束，这一句不会显示出来。
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
std::mutex和std::lock_guard的使用
在多线程环境中，有多个线程竞争同一个公共资源，就很容易引发线程安全的问题。因此就需要引入锁的机制，来保证任意时候只有一个线程在访问公共资源。
（1）头文件是#include<mutex>，mutex是用来保证线程同步的，防止不同的线程同时操作同一个共享数据。
（2）但使用lock_guard则相对安全，它是基于作用域的，能够自解锁，当该对象创建时，它会像m.lock()一样获得互斥锁，
	当生命周期结束时，它会自动析构(unlock)，不会因为某个线程异常退出而影响其他线程。
（3）如果在递归函数中多次对同一个互斥量加锁，而std::mutex是个非递归锁，这个程序会立刻死锁。这时候使用mutex库中的recursive_mutex就可以避免程序死锁。
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