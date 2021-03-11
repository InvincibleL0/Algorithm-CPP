#include<iostream>
using namespace std;
void insertion_sort(int arr[], int len)
{
	for (int i = 1; i < len; ++i)
	{
		int key = arr[i];
		int j = i - 1;
		while ((j >= 0) && (arr[j] > key))//from small to large
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}
int main()
{
	int arr[8] = { 9,6,8,1,0,4,2,1 };
	insertion_sort(arr, 8);
	for (int i = 0; i < 8; ++i) cout << arr[i] << " ";
	return 0;
}