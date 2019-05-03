#include <stdio.h>
#include <stdlib.h>

 
void swap(int *x,int *y)
{
    int t;
    t=*x;
    *x=*y;
    *y=t;
}
void heapify(int *arr, int n, int i)
{
	int largest = i;
	int l = 2*i + 1; 
	int r = 2*i + 2; 

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		swap(&arr[i],&arr[largest]);
		heapify(arr, n, largest);
	}
}
void heapSort(int *arr, int n)
{
	int i;
	for (i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	for (i=n-1; i>=0; i--)
	{
		swap(&arr[0],&arr[i]);
		heapify(arr, i, 0);
	}
}

int print(int *arr, int arr_len)	{
        int i;
        for(i = 0; i < arr_len; i++)	{
            printf("a[%d] = %d\n", i, arr[i]);
        }
        return 0;
}

int main()	{
  	int N,i;
  	printf("N = ");
  	scanf("%d",&N);
  	int a[N];
  	for (i = 0; i<N; i++)	{
  		printf("a[%d] = ",i);
    	scanf("%d", &a[i]);
	}
	printf("\n---After heap sorting ---\n\n");
	heapSort(a,N);
	print(a,N);
  	return 0;
}
