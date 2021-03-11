#include<iostream>
using namespace std;
void bubble_sort(int arr[], int len)//from small to large
{
	for (int i = 0; i < len; ++i)
	{
		for (int j = len - 1; j > 0; --j)
		{
			if (arr[j] < arr[j - 1])
			{
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}
int main()
{
	int arr[8] = { 9,6,8,1,0,4,2,1 };
	bubble_sort(arr, 8);
	for (int i = 0; i < 8; ++i) cout << arr[i] << " ";
	return 0;
}