#include<iostream>
using namespace std;
/*
C++标准库中已包含链表容器，只需包含头文件#include<list>
定义方法：双向list<int> list0;
单向forwart_list<int> forward_list0;
*/

//下面实现一个双向链表类
class node//双向链表中每个节点包含 节点数据、前驱指针、后继指针
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
	int insert(list *ptr, unsigned int position, int number);//在position之前插入一个node
	int erase(list *ptr, unsigned int position);//删除索引为position的node
	void display(list *ptr, unsigned int begin, unsigned int end);//显示begin到end的节点数据
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
			node *current_node = root->next;//首节点
			for (unsigned int i = 0; i < position; ++i) current_node = current_node->next;//current节点右移position-1次，insert_node插入到current之前
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
			for (unsigned int i = 0; i < position; ++i) delete_node = delete_node->next;//右移position-1次，删除delete_node
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
//下面实现一个单向链表类
class forward_node//单向链表只有节点数据和后继指针没有前驱指针
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
				for (unsigned int i = 0; i < position - 1; ++i) delete_node = delete_node->next;//删除delete_node的下一个节点
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