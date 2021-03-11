#include<iostream>
using namespace std;
void counting_sort(int arr[], int len)
{
	int *sorted = new int[len]();//���������ɵ�����
	int max = arr[0];//ȷ���ж��ٸ���ͬ��������
	for (int i = 0; i < len; ++i)
	{
		if (max < arr[i])
			max = arr[i];
	}
	int *count = new int[max + 1]();
	for (int i = 0; i < len; ++i)
		++count[arr[i]];//��ʾÿ�������ֵĴ�����count[n]=m��ʾ��n����m��
	for (int i = 1; i <= max; ++i)
		count[i] += count[i - 1];//conunt[n]=m��ʾ��m����С�ڻ����n
	for (int i = len - 1; i >= 0; --i)//��ÿ��arr[i]�ŵ�sorted[]����ȷλ����
	{
		sorted[count[arr[i]] - 1] = arr[i];
		--count[arr[i]];
	}
	for (int i = 0; i < len; ++i)//��sorted[]������arr[]
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