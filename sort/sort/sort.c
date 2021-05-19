#include"sort.h"

void PrintSort(int* a,int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
void Swap(int *p1,int *p2)
{
	int *temp = p1;
	*p1 = *p2;
    *p2 = *temp;
}
 //插入排序
void InsertSort(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int end=i;
		int temp = a[end + 1];
		while (end >= 0)
		{
			if (temp < a[end])
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				break;
			}
		}
		a[end + 1] = temp;
	}
	printf("插入排序：");
}
// 希尔排序
void ShellSort(int* a, int n)
{
	int gap=n;
	while (gap > 1)
	{
		gap = gap/3+1;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int temp = a[end + gap];
			while (end >= 0)
			{
				if (temp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = temp;
		}
	}
	printf("希尔排序：");
}
//选择排序
void SelectSort(int* a, int n)
{
	assert(a);
	int frist = 0; int end = n - 1;
	while (frist < end)
	{
		int min = frist, max = frist;

		for (int i = frist+1; i <= end; i++)
		{
			if (a[i] > a[max])
			{
				max = i;
			}
			if (a[i] < a[min])
			{
				min = i;
			}
		}
	    Swap(&a[frist], &a[min]);
		//如果max和min重叠，则交换两数下标，之后与end进行交换
		if (frist == max)
			max = min;
		Swap(&a[end], &a[max]);
		frist++;
		end--;
	}
	printf("选择排序：");

}
// 堆排序
void AdjustDown(int* a, int n, int root);
void HeapSort(int* a, int n);
// 冒泡排序
void BubbleSort(int* a, int n)
{
	/*int end = n;
	while (end > 0)*/
	for (int j = 0; j < n; j++)
	{
		//int exchange = 0;
		for (int i = 1; i < n; ++i)
		{
			if (a[i - 1] > a[i])
			{
				Swap(&a[i - 1], &a[i]);
				//exchange = 1;
			}
		}
		// 如果一趟冒泡的过程中没有发生交换，则前部分已经有序，不需要再冒泡
		/*if (exchange == 0)
		{
			break;
		}*/

		//--end;
	}
	printf("冒泡排序：");
}
// 快速排序递归实现
// 快速排序hoare版本
int PartSort1(int* a, int left, int right);
// 快速排序挖坑法
int PartSort2(int* a, int left, int right);
// 快速排序前后指针法
int PartSort3(int* a, int left, int right);
void QuickSort(int* a, int left, int right);
// 快速排序 非递归实现
void QuickSortNonR(int* a, int left, int right);
// 归并排序递归实现
void MergeSort(int* a, int n);
// 归并排序非递归实现
void MergeSortNonR(int* a, int n);
// 计数排序
void CountSort(int* a, int n);

void test1()
{
	int a[] = { 54,2,78,23,34,99,12,33,77,65,1,3,4,5,6,7,8,9,10 };
	int n = sizeof(a) / sizeof(int);
	InsertSort(a, n);
	PrintSort(a, n);
	ShellSort(a, n);
	PrintSort(a, n);
	SelectSort(a, n);
	PrintSort(a, n);
	BubbleSort(a, n);
	PrintSort(a, n);
}
int main()
{
	test1();
	return 0;
}
void TestOP()
{
	srand(time(0));
	const int N = 100000;
	int* a1 = (int*)malloc(sizeof(int) * N);
	int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	int* a5 = (int*)malloc(sizeof(int) * N);
	int* a6 = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
		a6[i] = a1[i];
	}
	int begin1 = clock();
	InsertSort(a1, N);
	int end1 = clock();
	int begin2 = clock();
	ShellSort(a2, N);
	int end2 = clock();
	int begin3 = clock();
	SelectSort(a3, N);
	int end3 = clock();
	int begin4 = clock();
	HeapSort(a4, N);
	int end4 = clock();
	int begin5 = clock();
	QuickSort(a5, 0, N - 1);
	int end5 = clock();
	int begin6 = clock();
	MergeSort(a6, N);
	int end6 = clock();
	printf("InsertSort:%d\n", end1 - begin1);
	printf("ShellSort:%d\n", end2 - begin2);
	printf("SelectSort:%d\n", end3 - begin3);
	printf("HeapSort:%d\n", end4 - begin4);
	printf("QuickSort:%d\n", end5 - begin5);
	printf("MergeSort:%d\n", end6 - begin6);
	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);
	free(a6);
}