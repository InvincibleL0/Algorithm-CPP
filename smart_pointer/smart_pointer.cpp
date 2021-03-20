/*
1、智能指针是一个类，这个类的构造函数中传入一个普通指针，析构函数中释放传入的指针。智能指针的类都是栈上的对象，所以当函数（或程序）结束时会自动被释放。
2、智能指针的作用是防止忘记调用delete释放内存和程序异常的进入catch块忘记释放内存。另外指针的释放时机也是非常有考究的，多次释放同一个指针会造成程序崩溃，这些都可以通过智能指针来解决。
3、智能指针是利用了一种叫做RAII（资源获取即初始化）的技术对普通的指针进行封装，这使得智能指针实质是一个对象，行为表现的却像一个指针。
*/
#include<iostream>
using namespace std;

/*
（1）shared_ptr多个指针指向相同的对象。shared_ptr使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。
	每使用他一次，内部的引用计数加1，每析构一次，内部的引用计数减1，减为0时，自动删除所指向的堆内存。
（2）初始化。智能指针是个模板类，可以指定类型，传入指针通过构造函数初始化。也可以使用make_shared函数初始化。
	不能将指针直接赋值给一个智能指针，一个是类，一个是指针。例如std::shared_ptr<int> p4 = new int(1);的写法是错误的
（3）拷贝和赋值。拷贝使得对象的引用计数增加1，赋值使得原对象引用计数减1，当计数为0时，自动释放内存。后来指向的对象引用计数加1，指向后来的对象。
（4）get函数获取原始指针。
（5）注意不要用一个原始指针初始化多个shared_ptr，否则会造成二次释放同一内存。
（6）注意避免循环引用，shared_ptr的一个最大的陷阱是循环引用，循环，循环引用会导致堆内存无法正确释放，导致内存泄漏。循环引用在weak_ptr中介绍。
*/
void shared()
{
	int zxn = 421;
	shared_ptr<int> ptr = make_shared<int>(zxn);
	//auto ptr = make_shared<int>(zxn);				//也可以用auto定义一个sharde_ptr<int>对象来保存make_shared的结果
	shared_ptr<int> ptr2(ptr);						//copy，ptr和ptr2都指向zxn
	cout << *ptr2 << endl;							//421
	cout << ptr.use_count() << endl;				//2	use_count()返回与ptr共享对象的智能指针数量，即有2个指针指向zxn

	int L0 = 9681;
	int *pb = &zxn;
	cout << *pb << endl;							//421
	//shared_ptr<int> ptr3 = pb;//错误，不能将指针直接赋值给一个智能指针
	shared_ptr<int> ptr3 = make_shared<int>(L0);
	ptr2 = ptr3;									//拷贝使得对象的引用计数增加1，赋值使得原对象引用计数减1，现在ptr2不指向zxn而是指向L0
	pb = ptr3.get();								//获取原指针，pb也指向L0

	cout << ptr.use_count() << endl;				//1
	cout << ptr3.use_count() << endl;				//2
	cout << *pb << endl;							//9681
}

/*
（1）unique_ptr“唯一”拥有其所指对象，同一时刻只能有一个unique_ptr指向给定对象（通过禁止拷贝语义、只有移动语义来实现）。
（2）unique_ptr指针本身的生命周期：从unique_ptr指针创建时开始，直到离开作用域。离开作用域时，若其指向对象，则将其所指对象销毁(默认使用delete操作符，用户可指定其他操作)。
（3）unique_ptr指针与其所指对象的关系：在智能指针生命周期内，可以改变智能指针所指对象，如创建智能指针时通过构造函数指定、通过reset方法重新指定、通过release方法释放所有权、
	通过移动语义转移所有权。
*/
void unique()
{
	int L0 = 9681;
	unique_ptr<int> uptr(&L0);						//绑定动态对象
	//unique_ptr<int> uptr(new int(9681));			//另一种初始化方式
	cout << *uptr << endl;							//9681
	//unique_ptr<int> uptr2 = uptr;					//不能赋值
	//unique_ptr<int> uptr2(uptr);					//不能拷贝
	unique_ptr<int> uptr2 = move(uptr);				//转换所有权
	cout << *uptr2 << endl;							//9681
	uptr2.release();								//释放所有权
	//cout << *uptr << endl;						//error
}

/*
（1）weak_ptr是为了配合shared_ptr而引入的一种智能指针，因为它不具有普通指针的行为，没有重载operator*和->,它的最大作用在于协助shared_ptr工作，像旁观者那样观测资源的使用情况。
（2）weak_ptr可以从一个shared_ptr或者另一个weak_ptr对象构造，获得资源的观测权。但weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加。
（3）使用weak_ptr的成员函数use_count()可以观测资源的引用计数，另一个成员函数expired()的功能等价于use_count()==0,但更快，表示被观测的资源(也就是shared_ptr的管理的资源)已经不复存在。
（4）weak_ptr可以使用一个非常重要的成员函数lock()从被观测的shared_ptr获得一个可用的shared_ptr对象， 从而操作资源。但当expired()==true的时候，lock()函数将返回一个存储空指针的shared_ptr。
*/
void weak()
{
	shared_ptr<int> sh_ptr = make_shared<int>(421);
	cout << sh_ptr.use_count() << endl;				//1

	weak_ptr<int> wp(sh_ptr);
	cout << sh_ptr.use_count() << endl;				//1	weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加。

	if (!wp.expired())								//失效？
	{
		shared_ptr<int> sh_ptr2 = wp.lock();		//获得另一个可用的shared_ptr对象
		cout << *sh_ptr2 << endl;					//421
		*sh_ptr = 9681;
		cout << *sh_ptr2 << endl;					//9681
		cout << wp.use_count() << endl;				//2
	}
}
int main()
{
	shared();
	unique();
	weak();
	return 0;
}