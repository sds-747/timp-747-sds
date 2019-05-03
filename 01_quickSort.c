#include <stdio.h>
#include <stdlib.h>

void qs(int *arr, int left, int right)
{
    int i, j, x, y;
    
    i = left; j = right;
    x = arr[(left+right)/2]; 
    
    do  {
        while ((arr[i] < x) && (i < right)) i++;
        while ((x < arr [j]) && (j > left)) j--;
        
        if (i <= j) {
            y = arr[i];
            arr[i] = arr[j];
            arr[j] = y;
            i++; j--;
        }
    }   while (i <= j);
    
    if (left < j) qs(arr, left, j);
    if (i < right) qs (arr, i, right);
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
	printf("\n---After quick sorting---\n\n");
	qs(a,0,N-1);
	print(a,N);
  	return 0;
}
