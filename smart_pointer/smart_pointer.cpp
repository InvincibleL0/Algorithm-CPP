/*
1������ָ����һ���࣬�����Ĺ��캯���д���һ����ָͨ�룬�����������ͷŴ����ָ�롣����ָ����඼��ջ�ϵĶ������Ե�����������򣩽���ʱ���Զ����ͷš�
2������ָ��������Ƿ�ֹ���ǵ���delete�ͷ��ڴ�ͳ����쳣�Ľ���catch�������ͷ��ڴ档����ָ����ͷ�ʱ��Ҳ�Ƿǳ��п����ģ�����ͷ�ͬһ��ָ�����ɳ����������Щ������ͨ������ָ���������
3������ָ����������һ�ֽ���RAII����Դ��ȡ����ʼ�����ļ�������ͨ��ָ����з�װ����ʹ������ָ��ʵ����һ��������Ϊ���ֵ�ȴ��һ��ָ�롣
*/
#include<iostream>
using namespace std;

/*
��1��shared_ptr���ָ��ָ����ͬ�Ķ���shared_ptrʹ�����ü�����ÿһ��shared_ptr�Ŀ�����ָ����ͬ���ڴ档
	ÿʹ����һ�Σ��ڲ������ü�����1��ÿ����һ�Σ��ڲ������ü�����1����Ϊ0ʱ���Զ�ɾ����ָ��Ķ��ڴ档
��2����ʼ��������ָ���Ǹ�ģ���࣬����ָ�����ͣ�����ָ��ͨ�����캯����ʼ����Ҳ����ʹ��make_shared������ʼ����
	���ܽ�ָ��ֱ�Ӹ�ֵ��һ������ָ�룬һ�����࣬һ����ָ�롣����std::shared_ptr<int> p4 = new int(1);��д���Ǵ����
��3�������͸�ֵ������ʹ�ö�������ü�������1����ֵʹ��ԭ�������ü�����1��������Ϊ0ʱ���Զ��ͷ��ڴ档����ָ��Ķ������ü�����1��ָ������Ķ���
��4��get������ȡԭʼָ�롣
��5��ע�ⲻҪ��һ��ԭʼָ���ʼ�����shared_ptr���������ɶ����ͷ�ͬһ�ڴ档
��6��ע�����ѭ�����ã�shared_ptr��һ������������ѭ�����ã�ѭ����ѭ�����ûᵼ�¶��ڴ��޷���ȷ�ͷţ������ڴ�й©��ѭ��������weak_ptr�н��ܡ�
*/
void shared()
{
	int zxn = 421;
	shared_ptr<int> ptr = make_shared<int>(zxn);
	//auto ptr = make_shared<int>(zxn);				//Ҳ������auto����һ��sharde_ptr<int>����������make_shared�Ľ��
	shared_ptr<int> ptr2(ptr);						//copy��ptr��ptr2��ָ��zxn
	cout << *ptr2 << endl;							//421
	cout << ptr.use_count() << endl;				//2	use_count()������ptr������������ָ������������2��ָ��ָ��zxn

	int L0 = 9681;
	int *pb = &zxn;
	cout << *pb << endl;							//421
	//shared_ptr<int> ptr3 = pb;//���󣬲��ܽ�ָ��ֱ�Ӹ�ֵ��һ������ָ��
	shared_ptr<int> ptr3 = make_shared<int>(L0);
	ptr2 = ptr3;									//����ʹ�ö�������ü�������1����ֵʹ��ԭ�������ü�����1������ptr2��ָ��zxn����ָ��L0
	pb = ptr3.get();								//��ȡԭָ�룬pbҲָ��L0

	cout << ptr.use_count() << endl;				//1
	cout << ptr3.use_count() << endl;				//2
	cout << *pb << endl;							//9681
}

/*
��1��unique_ptr��Ψһ��ӵ������ָ����ͬһʱ��ֻ����һ��unique_ptrָ���������ͨ����ֹ�������塢ֻ���ƶ�������ʵ�֣���
��2��unique_ptrָ�뱾����������ڣ���unique_ptrָ�봴��ʱ��ʼ��ֱ���뿪�������뿪������ʱ������ָ�����������ָ��������(Ĭ��ʹ��delete���������û���ָ����������)��
��3��unique_ptrָ��������ָ����Ĺ�ϵ��������ָ�����������ڣ����Ըı�����ָ����ָ�����紴������ָ��ʱͨ�����캯��ָ����ͨ��reset��������ָ����ͨ��release�����ͷ�����Ȩ��
	ͨ���ƶ�����ת������Ȩ��
*/
void unique()
{
	int L0 = 9681;
	unique_ptr<int> uptr(&L0);						//�󶨶�̬����
	//unique_ptr<int> uptr(new int(9681));			//��һ�ֳ�ʼ����ʽ
	cout << *uptr << endl;							//9681
	//unique_ptr<int> uptr2 = uptr;					//���ܸ�ֵ
	//unique_ptr<int> uptr2(uptr);					//���ܿ���
	unique_ptr<int> uptr2 = move(uptr);				//ת������Ȩ
	cout << *uptr2 << endl;							//9681
	uptr2.release();								//�ͷ�����Ȩ
	//cout << *uptr << endl;						//error
}

/*
��1��weak_ptr��Ϊ�����shared_ptr�������һ������ָ�룬��Ϊ����������ָͨ�����Ϊ��û������operator*��->,���������������Э��shared_ptr���������Թ��������۲���Դ��ʹ�������
��2��weak_ptr���Դ�һ��shared_ptr������һ��weak_ptr�����죬�����Դ�Ĺ۲�Ȩ����weak_ptrû�й�����Դ�����Ĺ��첻������ָ�����ü��������ӡ�
��3��ʹ��weak_ptr�ĳ�Ա����use_count()���Թ۲���Դ�����ü�������һ����Ա����expired()�Ĺ��ܵȼ���use_count()==0,�����죬��ʾ���۲����Դ(Ҳ����shared_ptr�Ĺ������Դ)�Ѿ��������ڡ�
��4��weak_ptr����ʹ��һ���ǳ���Ҫ�ĳ�Ա����lock()�ӱ��۲��shared_ptr���һ�����õ�shared_ptr���� �Ӷ�������Դ������expired()==true��ʱ��lock()����������һ���洢��ָ���shared_ptr��
*/
void weak()
{
	shared_ptr<int> sh_ptr = make_shared<int>(421);
	cout << sh_ptr.use_count() << endl;				//1

	weak_ptr<int> wp(sh_ptr);
	cout << sh_ptr.use_count() << endl;				//1	weak_ptrû�й�����Դ�����Ĺ��첻������ָ�����ü��������ӡ�

	if (!wp.expired())								//ʧЧ��
	{
		shared_ptr<int> sh_ptr2 = wp.lock();		//�����һ�����õ�shared_ptr����
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