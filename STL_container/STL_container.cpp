#include<iostream>
//˳������
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<stack>
//��������
#include<set>
#include<map>
using namespace std;

int string_test()
{
	string s1;//��ʼ���ַ��������ַ���
	string s2 = s1; //������ʼ��������ַ���
	string s3 = "Hellor World"; //ֱ�ӳ�ʼ����s3�����ַ���
	string s4(10, 'a'); //s4����ַ�����aaaaaaaaaa
	string s5(s4); //������ʼ��������ַ���
	string s6(" L0"); //ֱ�ӳ�ʼ��
	string s7 = string(6, 'c'); //������ʼ����cccccc

	//string�ĸ��ֲ���
	string s8 = s3 + s6;//�������ַ����ϲ���һ��
	s3 = s6;//��һ���ַ����������һ���ַ����Ķ���Ԫ��

	//cin >> s1;//ʹ��cin�����ַ���ʱ�������հ׾�ֹͣ��ȡ
	getline(cin, s1);//����s1�����ݣ���ȡһ����

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;
	cout << s7 << endl;
	cout << s8 << endl;
	cout << "s7 size = " << s7.size() << endl; //�ַ������ȣ�������������
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
��1��vector�������һ�����ʾ�����ṩ���Զ��ڴ�����ܣ����Զ�̬�ظı�vector����ĳ��ȣ�������Ԫ�ص���Ӻ�ɾ����������С��
	���ṩ�˶�Ԫ�ص�������ʣ���β����Ӻ�ɾ��Ԫ�ص�ʱ���ǹ̶��ģ�����ͷ�����м�����ɾ��Ԫ�صĸ��Ӷ�Ϊ����ʱ�䡣
��2����Ȼvertor������Զ�̬����������Ҳ����һ�㸱���ã���֪��һ�����ƾ��ǲ����ٷ�Χforѭ������vector�������Ԫ�أ���ʹend������ʧЧ��
	����һ�����ƾ����κ�һ�ֿ��ܸı�vector���������Ĳ���������push_back������ʹ�õ�����ʧЧ��
	���⣬Ϊ���������ڴ�ռ��ʱ���Ϊ�����Ķ�����һЩ�ռ䡣
��3��push_back��Ԫ�ز�������ĩβ��insert��Ԫ�ز����κ�ָ����λ�á�����push_back�ٶ�һ���insert�졣�������push_back��������push_back��
��4��ֻ�ܶ��Ѵ��ڵ�Ԫ�ؽ��и�ֵ�����޸Ĳ����������Ҫ������Ԫ�أ����ʹ��push_back��push_back�����������������߱�����Ϊ��Ԫ�ؿ��ٿռ䡢����Ԫ�ش����¿ռ��
	����vector<int> vec; vec[0] = 1;//����
*/
int vector_test()
{
	vector<string> v1 = { "hi ", "C++ ", "Primer ", "learning " };
	v1.resize(3); //���µ���vector������С
	showvector(v1);

	vector<int> v2 = { 1, 2, 3, 4, 5 }; //�б��ʼ��,ע��ʹ�õ��ǻ�����
	cout << v2.front() << endl;       //���ʵ�һ��Ԫ��
	cout << v2.back() << endl;        //�������һ��Ԫ��

	showvector(v2);
	v2.pop_back(); //ɾ�����һ��Ԫ��
	showvector(v2);
	v2.push_back(6); //����һ��Ԫ�ز������������
	showvector(v2);
	v2.insert(v2.begin() + 1, 9); //�ڵڶ���λ�ò�����Ԫ��
	showvector(v2);
	v2.erase(v2.begin() + 3); //ɾ�����ĸ�Ԫ��
	showvector(v2);
	v2.insert(v2.begin() + 1, 7, 8); //��������7��8
	showvector(v2);
	v2.clear(); //�����������
	showvector(v2);

	return 0;
}
/*
deque
��1��dequeģ���� double-ended queue(˫�˶���) ��֧��������ʣ���deque����Ŀ�ʼλ�ò����ɾ��Ԫ�ص�ʱ���ǹ̶��ģ�������vector������ʱ�䡣
��2�����Զ��������Ƿ��������е���ʼ�ͽ�β������Ӧ�ÿ���deque��Ϊʵ����deque����ִ�в����ɾ��������ʱ��Ϊ�̶�����һĿ�ģ�deque�������Ʊ�vector�����Ϊ���ӡ�
��3����ˣ��������߶��ṩ��Ԫ�ص�������ʺ��������в�ִ������ʱ��Ĳ����ɾ������������vector����ִ����Щ����ʱ�ٶȻ�Ҫ��Щ��
��4��queueģ������Ʊ�deque���࣬������������������ʶ���Ԫ�أ�����������������С�
	����ʹ�������ڶ�����еĻ��������ϣ����Խ�Ԫ����ӵ���β���Ӷ���ɾ��Ԫ�أ��鿴���׺Ͷ�β��ֵ�����Ԫ����Ŀ�Ͳ��Զ����Ƿ�Ϊ�ա�

stack<value_type> name;
��1���ṩ�˵��͵�ջ�ӿ�,stackģ������Ʊ�vector���ࡣ
	�������������������ջԪ�أ��������������ջ������ʹ�������ڶ���ջ�Ļ��������ϣ������Խ�ѹ���Ƶ�ջ������ջ������Ԫ�أ��鿴ջ����ֵ�����Ԫ����Ŀ�Ͳ���ջ�Ƿ�Ϊ�ա�
��2����queue���ƣ����Ҫʹ��ջ�е�ֵ����������ʹ��top()���������ֵ��Ȼ��ʹ��pop()������ջ��ɾ����

list<value_type> name;
��1��list��˫�����������˵�һ�������һ��Ԫ���⣬ÿ��Ԫ�ض���ǰ���Ԫ�������ӣ�����ζ�ſ���˫���������.
��2��list��vector֮��ؼ��������ڣ�list����������һλ�ý��в����ɾ����ʱ�䶼�ǹ̶��ģ�vectorģ���ṩ�˳���β���������ʱ��Ĳ����ɾ�����ڽ�β�������ṩ�˹̶�ʱ��Ĳ����ɾ������
	��ˣ�vectorǿ������ͨ��������ʿ��ٷ��ʣ���listǿ������Ԫ�صĿ��ٲ����ɾ����
��3��listҲ���Է�ת������list��֧�������ʾ����������ʡ���Ϊ������˫������ʵ�ֵģ�
	���ԣ�����һ�����Ծ������ĵ�������Զ�����Ϊ��Ч��������οռ䲻�����ˣ������������ӡ�ɾ���������������ƻ���������
	list��һ��˫���������������Ӧ����������foward_list��
��4��forward_list����ʵ���˵����������������У�ÿ���ڵ㶼ֻ���ӵ���һ���ڵ㣬��û�����ӵ�ǰһ���ڵ㡣
	���forward_listֻ��Ҫ�����������������Ҫ˫�����������ˣ���ͬ��vector��list��forward_list�ǲ��ɷ�ת��������
	���list��forward_list���򵥣������գ�������Ҳ���١�
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
	lst1.sort();//list�������ܵ���algorithm.h�µ�sort��������������Ϊsort����Ҫ�����������������洢����list������������list���Լ��ĳ�Ա����sort()����ʹ�á�
	showlist(lst1);
	list<int> lst2(5, 10); //��Ԫ�ض���ʼ��Ϊ10
	showlist(lst2);
	list<string> lst3{ "Hello","World" };
	showlist(lst3);
	return 0;
}

/*
set<value_type> name;

��1����ֵ���������ͬ������Ψһ�ġ�����ζ�ż����в����ж����ͬ�ļ���set��vector��࣬����vector��Ψһ������ǣ�set�����Ԫ�����������Ψһ�ġ�
��2��ֻҪ��set�����Ԫ�أ����ͻ��Զ����򣬶��ң������ӵ�Ԫ��set���汾���ʹ��ڣ���ô�����Ӳ����Ͳ�ִ�С�



map<key_type,value_type> name;

��1��map�����˹�ϣ���ַӳ���˼�룬Ҳ����key-value��˼�룬��ʵ�ֵģ��ײ��setһ�������ú����ʵ�֡��ڲ�Ԫ�ذ���key��ϣ����
	���ȸ���map�����Ҳ����õ��÷����ӣ��������ַ�����Ϊkeyȥ��ѯ������Ӧ��value��
��2��ע�⣺�ڲ���һ�������ڵ�key��ʱ��map���Զ��������key�������漰����ΰ�ȫ����ѡ�����Լ�ҵ���߼��Ĺ�������������Ҫ��


set��map��Ҫ��ؼ��ֲ��ظ������򱣴�Ԫ�أ�
multiset��multimap����ؼ����ظ������򱣴�Ԫ�أ�
unorderred_set��unorderred_mapҪ��ؼ��ֲ��ظ������򱣴�Ԫ�أ�
unorderred_multiset��unorderred_multimap����ؼ����ظ������򱣴�Ԫ�ء�
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
	set<int> s1{ 9,6,8,1,0,4,2,1 }; //�Զ����򣬴�С����,�޳���ͬ��
	showset(s1);
	set<string> s2{ "Hello ", "C++ ", "Primer ", "5th " }; //�ֵ�������
	showset(s2);
	s1.insert(9); //�����ֵ�ˣ�do nothing
	showset(s1);
	s2.insert("aaa "); //û������ַ�������Ӳ�������
	showset(s2);

	return 0;
}

void showmap(map<string, int> v)
{
	for (map<string, int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << it->first << "  " << it->second << endl;  //ע���÷���������*it�������ˡ�first��ʾ����key��second�����value
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
	cout << m1["minute"] << endl; //���������key������ʾ0������map�д���û�е�key

	m1.erase("minute");//ͨ���ؼ�����ɾ��

	if (m1.count("year"))//����뿴��ĳ���治����ĳ��key��������count���ж�
		cout << "year is in m1." << endl;
	if (m1.find("month") == m1.end())//find���÷���һ������������������ؼ�����map�У�������ָ��ùؼ��֣�����find����β�������end()��
		cout << "month is not in m1." << endl;
	else
		cout << "month is in m1." << endl;

	showmap(m1);
	m1.insert(pair<string, int>("L0", 9681)); //Ҳ����ͨ��insert������ʵ������Ԫ�ء�һ��pair�����������ݳ�Ա����һ�������ض����͵�ģ�塣
	showmap(m1);
	m1.clear(); //���ȫ��

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