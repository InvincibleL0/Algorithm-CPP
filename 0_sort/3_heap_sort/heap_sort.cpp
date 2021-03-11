#include<iostream>
using namespace std;
void max_heap_ify(int arr[], int index, int len)
{
	int l = 2 * index + 1;//index������
	int r = 2 * (index + 1);//index���Һ���
	int largest_index = index;
	if (l < len && arr[l] > arr[index])
		largest_index = l;
	if (r < len && arr[r] > arr[largest_index])
		largest_index = r;
	if (largest_index != index)//���ֵ���Ǹ��ڵ㣬����λ��
	{
		int temp = arr[index];
		arr[index] = arr[largest_index];
		arr[largest_index] = temp;
		max_heap_ify(arr, largest_index, len);//�ݹ�ȷ������Ҳ������
	}
}
void bulid_max_heap(int arr[], int len)
{
	for (int i = len / 2 - 1; i >= 0; --i) //�����һ����Ҷ�ӽڵ㿪ʼ�Ե����Ϲ���
		max_heap_ify(arr, i, len);
}
void heap_sort(int arr[], int len)
{
	bulid_max_heap(arr, len);
	for (int i = len - 1; i > 0; --i)
	{
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		max_heap_ify(arr, 0, i);
	}
}
int main()
{
	int arr[8] = { 0,4,2,1,9,6,8,1 };
	heap_sort(arr, 8);
	for (int i = 0; i < 8; ++i) cout << arr[i] << " ";
	return 0;
}