#include<iostream>
using namespace std;
/*
C++��׼�����Ѱ�������������ֻ�����ͷ�ļ�#include<list>
���巽����˫��list<int> list0;
����forwart_list<int> forward_list0;
*/

//����ʵ��һ��˫��������
class node//˫��������ÿ���ڵ���� �ڵ����ݡ�ǰ��ָ�롢���ָ��
{
public:
	int data;
	node *prev;
	node *next;
};

class list
{
private:
	node *root;
	int length;
public:
	list()
	{
		root = new node;
		root->prev = nullptr;
		root->next = nullptr;
		length = 0;
	}
	int insert(list *ptr, unsigned int position, int number);//��position֮ǰ����һ��node
	int erase(list *ptr, unsigned int position);//ɾ������Ϊposition��node
	void display(list *ptr, unsigned int begin, unsigned int end);//��ʾbegin��end�Ľڵ�����
	int get_length(list *ptr);
};

int list::insert(list *ptr, unsigned int position, int number)
{
	node *insert_node = new node;
	insert_node->data = number;
	if (ptr->get_length(ptr) == 0)
	{
		root->next = insert_node;
		insert_node->prev = insert_node;
		insert_node->next = insert_node;
		ptr->length++;
		return 0;
	}
	else
	{
		if (position == 0)
		{
			insert_node->prev = root;
			insert_node->next = root->next;
			root->next->prev = insert_node;
			root->next = insert_node;
			ptr->length++;
			return 0;
		}
		else
		{
			node *current_node = root->next;//�׽ڵ�
			for (unsigned int i = 0; i < position; ++i) current_node = current_node->next;//current�ڵ�����position-1�Σ�insert_node���뵽current֮ǰ
			insert_node->prev = current_node->prev;
			insert_node->next = current_node;
			current_node->prev->next = insert_node;
			current_node->prev = insert_node;
			ptr->length++;
			return 0;
		}
	}
}

int list::erase(list *ptr, unsigned int position)
{
	if (ptr->get_length(ptr) == 0)
	{
		cout << "linked list is empty." << endl;
		return 0;
	}
	else
	{
		if (ptr->get_length(ptr) == 1)
		{
			root->next = nullptr;
			ptr->length--;
			return 0;
		}
		else
		{
			node *delete_node = root->next;
			for (unsigned int i = 0; i < position; ++i) delete_node = delete_node->next;//����position-1�Σ�ɾ��delete_node
			delete_node->prev->next = delete_node->next;
			delete_node->next->prev = delete_node->prev;
			delete delete_node;
			ptr->length--;
			return 0;
		}
	}
}

void list::display(list *ptr, unsigned int begin, unsigned int end)
{
	node *current_node = root->next;
	for (unsigned int i = 0; i < begin; ++i) current_node = current_node->next;
	unsigned int count = end - begin + 1;
	for (unsigned int i = 0; i < count; ++i)
	{
		cout << current_node->data << " ";
		current_node = current_node->next;
	}
}

int list::get_length(list *ptr)
{
	return ptr->length;
}
//����ʵ��һ������������
class forward_node//��������ֻ�нڵ����ݺͺ��ָ��û��ǰ��ָ��
{
public:
	int data;
	forward_node *next;
};

class forward_list
{
private:
	forward_node *root;
	int length;
public:
	forward_list()
	{
		root = new forward_node;
		root->next = nullptr;
		length = 0;
	}
	int insert(forward_list *ptr, unsigned int position, int number);
	int erase(forward_list *ptr, unsigned int position);
	void display(forward_list *ptr, unsigned int begin, unsigned int end);
	int get_length(forward_list *ptr);
};

int forward_list::insert(forward_list *ptr, unsigned int position, int number)
{
	forward_node *insert_node = new forward_node;
	insert_node->data = number;
	if (ptr->get_length(ptr) == 0)
	{
		root->next = insert_node;
		insert_node = insert_node->next;
		ptr->length++;
		return 0;
	}
	else
	{
		if (position == 0)
		{
			insert_node->next = root->next;
			root->next = insert_node;
			ptr->length++;
			return 0;
		}
		else
		{
			forward_node *current_node = root->next;
			for (unsigned int i = 0; i < position - 1; ++i) current_node = current_node->next;
			insert_node->next = current_node->next;
			current_node->next = insert_node;
			ptr->length++;
			return 0;
		}
	}
}

int forward_list::erase(forward_list *ptr, unsigned int position)
{
	if (ptr->get_length(ptr) == 0)
	{
		cout << "linked list is empty." << endl;
		return 0;
	}
	else
	{
		if (ptr->get_length(ptr) == 1)
		{
			root->next = nullptr;
			ptr->length--;
			return 0;
		}
		else
		{
			if (position == 0)
			{
				forward_node *delete_node = root->next;
				root->next = delete_node->next;
				delete delete_node;
				ptr->length--;
				return 0;
			}
			else
			{
				forward_node *delete_node = root->next;
				for (unsigned int i = 0; i < position - 1; ++i) delete_node = delete_node->next;//ɾ��delete_node����һ���ڵ�
				delete_node->next = delete_node->next->next;
				//delete delete_node->next;
				ptr->length--;
				return 0;
			}
		}
	}
}

void forward_list::display(forward_list *ptr, unsigned int begin, unsigned int end)
{
	forward_node *current_node = root->next;
	for (unsigned int i = 0; i < begin; ++i) current_node = current_node->next;
	unsigned int count = end - begin + 1;
	for (unsigned int i = 0; i < count; ++i)
	{
		cout << current_node->data << " ";
		current_node = current_node->next;
	}
}

int forward_list::get_length(forward_list *ptr)
{
	return ptr->length;
}

int main()
{
	list list0;
	for (int i = 0; i < 10; ++i) list0.insert(&list0, i, i);
	list0.insert(&list0, 0, 421);
	list0.erase(&list0, 1);
	list0.display(&list0, 0, 9);
	cout << endl;
	forward_list list1;
	for (int i = 0; i < 10; ++i) list1.insert(&list1, i, i);
	list1.insert(&list1, 0, 9681);
	list1.erase(&list1, 1);
	list1.display(&list1, 0, 9);
	return 0;
}