#include<iostream>
using namespace std;
int partition(int arr[], int p, int r)
{
	int x = arr[p];
	int i = p;
	int j = r;
	while (i < j)
	{
		while (i < j && arr[j] >= x)//���������ҵ���һ��С��x����
			--j;
		if (i < j)
			arr[i++] = arr[j];//��һ��С��x�����ŵ������(��������ѱ�����x��)
		while (i < j && arr[i] <= x)//���������ҵ���һ������x����
			++i;
		if (i < j)
			arr[j--] = arr[i];//��һ������x�����ŵ����ұ�(���ұߵ����ѱ����������)
	}
	arr[i] = x;//i����߶�С��x���ұ߶�����x
	return i;
}
void quick_sort(int arr[], int min_index, int max_index)
{
	if (min_index < max_index)
	{
		int q = partition(arr, min_index, max_index);
		quick_sort(arr, min_index, q - 1);
		quick_sort(arr, q + 1, max_index);
	}
}
int main()
{
	int arr[8] = { 9,6,8,1,0,4,2,1 };
	quick_sort(arr, 0, 7);
	for (int i = 0; i < 8; ++i) cout << arr[i] << " ";
	return 0;
}