#include<iostream>
//顺序容器
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<stack>
//关联容器
#include<set>
#include<map>
using namespace std;

int string_test()
{
	string s1;//初始化字符串，空字符串
	string s2 = s1; //拷贝初始化，深拷贝字符串
	string s3 = "Hellor World"; //直接初始化，s3存了字符串
	string s4(10, 'a'); //s4存的字符串是aaaaaaaaaa
	string s5(s4); //拷贝初始化，深拷贝字符串
	string s6(" L0"); //直接初始化
	string s7 = string(6, 'c'); //拷贝初始化，cccccc

	//string的各种操作
	string s8 = s3 + s6;//将两个字符串合并成一个
	s3 = s6;//用一个字符串来替代另一个字符串的对用元素

	//cin >> s1;//使用cin读入字符串时，遇到空白就停止读取
	getline(cin, s1);//键入s1的内容，读取一整行

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;
	cout << s7 << endl;
	cout << s8 << endl;
	cout << "s7 size = " << s7.size() << endl; //字符串长度，不包括结束符
	cout << (s2.empty() ? "This string is empty." : "This string is not empty.") << endl;;

	return 0;
}

template <typename T> void showvector(vector<T> v) 
{
	for (typename vector<T>::iterator it = v.begin(); it != v.end(); it++) 
	{
		cout << *it;
	}
	cout << endl;
}
/*
（1）vector是数组的一种类表示，它提供了自动内存管理功能，可以动态地改变vector对象的长度，并随着元素的添加和删除而增大缩小，
	它提供了对元素的随机访问，在尾部添加和删除元素的时间是固定的，但在头部或中间插入和删除元素的复杂度为线性时间。
（2）虽然vertor对象可以动态增长，但是也或有一点副作用：已知的一个限制就是不能再范围for循环中向vector对象添加元素，会使end迭代器失效。
	另外一个限制就是任何一种可能改变vector对象容量的操作，不如push_back，都会使该迭代器失效。
	另外，为容器申请内存空间的时候会为其额外的多申请一些空间。
（3）push_back把元素插入容器末尾，insert把元素插入任何指定的位置。不过push_back速度一般比insert快。如果能用push_back尽量先用push_back。
（4）只能对已存在的元素进行赋值或者修改操作，如果是要加入新元素，务必使用push_back。push_back的作用有两个：告诉编译器为新元素开辟空间、将新元素存入新空间里。
	例如vector<int> vec; vec[0] = 1;//错误！
*/
int vector_test()
{
	vector<string> v1 = { "hi ", "C++ ", "Primer ", "learning " };
	v1.resize(3); //重新调整vector容量大小
	showvector(v1);

	vector<int> v2 = { 1, 2, 3, 4, 5 }; //列表初始化,注意使用的是花括号
	cout << v2.front() << endl;       //访问第一个元素
	cout << v2.back() << endl;        //访问最后一个元素

	showvector(v2);
	v2.pop_back(); //删除最后一个元素
	showvector(v2);
	v2.push_back(6); //加入一个元素并把它放在最后
	showvector(v2);
	v2.insert(v2.begin() + 1, 9); //在第二个位置插入新元素
	showvector(v2);
	v2.erase(v2.begin() + 3); //删除第四个元素
	showvector(v2);
	v2.insert(v2.begin() + 1, 7, 8); //连续插入7个8
	showvector(v2);
	v2.clear(); //清除所有内容
	showvector(v2);

	return 0;
}
/*
deque
（1）deque模版类 double-ended queue(双端队列) ，支持随机访问，从deque对象的开始位置插入和删除元素的时间是固定的，而不像vector是线性时间。
（2）所以多数操作是发生在序列的起始和结尾处，就应该考虑deque。为实现在deque两端执行插入和删除操作的时间为固定的这一目的，deque对象的设计比vector对象更为复杂。
（3）因此，尽管两者都提供对元素的随机访问和在序列中部执行线性时间的插入和删除操作，但是vector容器执行这些操作时速度还要快些。
（4）queue模版的限制比deque更多，它不仅不允许随机访问队列元素，甚至不允许遍历队列。
	它把使用限制在定义队列的基本操作上，可以将元素添加到队尾，从队首删除元素，查看队首和队尾的值，检查元素数目和测试队列是否为空。

stack<value_type> name;
（1）提供了典型的栈接口,stack模版的限制比vector更多。
	它不仅不允许随机访问栈元素，甚至不允许遍历栈，它把使用限制在定义栈的基本操作上，即可以将压入推到栈顶，从栈顶弹出元素，查看栈顶的值，检查元素数目和测试栈是否为空。
（2）与queue相似，如果要使用栈中的值，必须首先使用top()来检索这个值，然后使用pop()将它中栈中删除。

list<value_type> name;
（1）list（双向链表），除了第一个和最后一个元素外，每个元素都与前后的元素相连接，这意味着可以双向遍历链表.
（2）list和vector之间关键区别在于，list在链表中任一位置进行插入和删除的时间都是固定的（vector模版提供了除结尾处外的线性时间的插入和删除，在结尾处，它提供了固定时间的插入和删除）。
	因此，vector强调的是通过随机访问快速访问，而list强调的是元素的快速插入和删除。
（3）list也可以反转容器，list不支持数组表示法和随机访问。因为它是用双向链表实现的，
	所以，它的一大特性就是它的迭代器永远不会变为无效（除非这段空间不存在了），即无论增加、删除操作，都不会破坏迭代器。
	list是一个双向链表，而单链表对应的容器则是foward_list。
（4）forward_list，它实现了单链表，在这种链表中，每个节点都只链接到下一个节点，而没有链接到前一个节点。
	因此forward_list只需要正向迭代器，而不需要双向迭代器。因此，不同于vector和list，forward_list是不可反转的容器。
	相比list，forward_list更简单，更紧凑，但功能也更少。
*/
template <typename T> void showlist(list<T> v) 
{
	for (typename list<T>::iterator it = v.begin(); it != v.end(); it++) 
	{
		cout << *it << " ";
	}
	cout << endl;
}
int list_test()
{
	list<int> lst1{ 9,6,8,1,0,4,2,1 };
	showlist(lst1);
	lst1.sort();//list容器不能调用algorithm.h下的sort函数进行排序，因为sort函数要求容器必须可以随机存储，而list做不到。但是list有自己的成员函数sort()可以使用。
	showlist(lst1);
	list<int> lst2(5, 10); //将元素都初始化为10
	showlist(lst2);
	list<string> lst3{ "Hello","World" };
	showlist(lst3);
	return 0;
}

/*
set<value_type> name;

（1）其值类型与键相同，键是唯一的。这意味着集合中不会有多个相同的键。set跟vector差不多，它跟vector的唯一区别就是，set里面的元素是有序的且唯一的。
（2）只要往set里添加元素，它就会自动排序，而且，如果添加的元素set里面本来就存在，那么这次添加操作就不执行。



map<key_type,value_type> name;

（1）map运用了哈希表地址映射的思想，也就是key-value的思想，来实现的，底层和set一样都是用红黑树实现。内部元素按照key哈希排序。
	首先给出map最好用也最最常用的用法例子，就是用字符串作为key去查询操作对应的value。
（2）注意：在查找一个不存在的key的时候，map会自动生成这个key，这里涉及到如何安全和挑选符合自己业务逻辑的关联容器格外重要。


set和map都要求关键字不重复、有序保存元素；
multiset和multimap允许关键字重复、有序保存元素；
unorderred_set和unorderred_map要求关键字不重复、无序保存元素；
unorderred_multiset和unorderred_multimap允许关键字重复、无序保存元素。
*/
template <typename T> void showset(set<T> v)
{
	for (typename set<T>::iterator it = v.begin(); it != v.end(); it++) 
	{
		cout << *it << " ";
	}
	cout << endl;
}
int set_test()
{
	set<int> s1{ 9,6,8,1,0,4,2,1 }; //自动排序，从小到大,剔除相同项
	showset(s1);
	set<string> s2{ "Hello ", "C++ ", "Primer ", "5th " }; //字典序排序
	showset(s2);
	s1.insert(9); //有这个值了，do nothing
	showset(s1);
	s2.insert("aaa "); //没有这个字符串，添加并且排序
	showset(s2);

	return 0;
}

void showmap(map<string, int> v)
{
	for (map<string, int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << it->first << "  " << it->second << endl;  //注意用法，不是用*it来访问了。first表示的是key，second存的是value
	}
	cout << endl;
}
int map_test()
{
	map<string, int> m1;
	m1["year"] = 1997;
	m1["month"] = 8;
	m1["day"] = 21;

	string s("month");
	m1[s] = 4;

	cout << m1["year"] << endl;
	cout << m1["month"] << endl;
	cout << m1["day"] << endl; 
	cout << m1["minute"] << endl; //不存在这个key，就显示0，并在map中创建没有的key

	m1.erase("minute");//通过关键字来删除

	if (m1.count("year"))//如果想看看某个存不存在某个key，可以用count来判断
		cout << "year is in m1." << endl;
	if (m1.find("month") == m1.end())//find调用返回一个迭代器，如果给定关键字在map中，迭代器指向该关键字，否则find返回尾后迭代器end()。
		cout << "month is not in m1." << endl;
	else
		cout << "month is in m1." << endl;

	showmap(m1);
	m1.insert(pair<string, int>("L0", 9681)); //也可以通过insert函数来实现增加元素。一个pair保存两个数据成员，是一个生成特定类型的模板。
	showmap(m1);
	m1.clear(); //清空全部

	return 0;
}
int main()
{
	string_test();
	vector_test();
	list_test();
	set_test();
	map_test();
	return 0;
}