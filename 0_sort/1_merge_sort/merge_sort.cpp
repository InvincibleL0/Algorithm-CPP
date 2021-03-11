#include<iostream>
#include<limits>
using namespace std;
void merge(int arr[], int p, int q, int r)//排序并合并序列
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int *L = new int[n1 + 1]{ 0 };
	int *R = new int[n2 + 1]{ 0 };
	for (int i = 0; i < n1; ++i) L[i] = arr[i + p];
	for (int i = 0; i < n2; ++i) R[i] = arr[i + q + 1];
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;
	for (int i = 0, j = 0, k = p; k < r + 1; ++k)
	{
		if (L[i] <= R[j])
			arr[k] = L[i++];
		else
			arr[k] = R[j++];
	}
	delete [] L;
	delete [] R;
}
void merge_sort(int arr[], int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		merge_sort(arr, p, q);//分解为最小序列
		merge_sort(arr, q + 1, r);
		merge(arr, p, q, r);
	}
}
int main()
{
	int arr[8] = { 9,6,8,1,0,4,2,1 };
	merge_sort(arr, 0, 7);
	for (int i = 0; i < 8; ++i) cout << arr[i] << " ";
	return 0;
}