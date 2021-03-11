#include<iostream>
using namespace std;
void counting_sort(int arr[], int len)
{
	int *sorted = new int[len]();//存放排序完成的数组
	int max = arr[0];//确定有多少个不同的数出现
	for (int i = 0; i < len; ++i)
	{
		if (max < arr[i])
			max = arr[i];
	}
	int *count = new int[max + 1]();
	for (int i = 0; i < len; ++i)
		++count[arr[i]];//表示每个数出现的次数，count[n]=m表示数n出现m次
	for (int i = 1; i <= max; ++i)
		count[i] += count[i - 1];//conunt[n]=m表示有m个数小于或等于n
	for (int i = len - 1; i >= 0; --i)//把每个arr[i]放到sorted[]的正确位置上
	{
		sorted[count[arr[i]] - 1] = arr[i];
		--count[arr[i]];
	}
	for (int i = 0; i < len; ++i)//将sorted[]拷贝到arr[]
		arr[i] = sorted[i];
	delete [] sorted;
	delete [] count;
}
int main()
{
	int arr[8] = { 9,6,8,1,0,4,2,1 };
	counting_sort(arr, 8);
	for (int i = 0; i < 8; ++i) cout << arr[i] << " ";
	return 0;
}