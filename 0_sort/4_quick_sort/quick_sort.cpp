#include<iostream>
using namespace std;
int partition(int arr[], int p, int r)
{
	int x = arr[p];
	int i = p;
	int j = r;
	while (i < j)
	{
		while (i < j && arr[j] >= x)//从右向左找到第一个小于x的数
			--j;
		if (i < j)
			arr[i++] = arr[j];//第一个小于x的数放到最左边(最左边数已备份在x中)
		while (i < j && arr[i] <= x)//从左向右找到第一个大于x的数
			++i;
		if (i < j)
			arr[j--] = arr[i];//第一个大于x的数放到最右边(最右边的数已备份在最左边)
	}
	arr[i] = x;//i的左边都小于x，右边都大于x
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