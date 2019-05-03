#include <stdio.h>
#include <stdlib.h>

void shell(int *arr, int arr_length)
{
	int i, j, k, t;
	for(k = arr_length / 2; k > 0; k /= 2){
        for(i = k; i < arr_length; i++)
        {
            t = arr[i];
            for(j = i; j >= k; j -= k)
            {
                if(t < arr[j - k]){
                    arr[j] = arr[j - k];
                }
                else{
                    break;
                }
            }
            arr[j] = t;
        }
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
	printf("\n---After sorting Shell---\n\n");
	shell(a,N);
	print(a,N);
  	return 0;
}
