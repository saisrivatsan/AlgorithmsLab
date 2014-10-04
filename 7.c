#include<stdio.h>
#include<stdlib.h>

#define swap(a,b) { int t; t = a; a = b; b =t;}

void countsort(int a[],int n,int k)
{
	int *c;
	int i,e;
	int m = 2*k + 1;
	c = (int *)calloc( m , sizeof(int) );

	/* C is the count array. No of occurences of a number X
		can be found at m+X */
	for(i=0;i<n;i++)
		c[ m/2 + a[i] ] ++;

	
	for(i=1;i<m;i++)
		c[i] += c[i-1];
	for(i=0;i<m;i++)
		c[i]--;
	/* C[m+X] now consists of the index of the of location of last X */

	int j,t,l;
	
	
    i = 0;
	while(i<n)
	{	
		
	  /*  for(j=0;j<n;j++)
			printf("%d  ",a[j]);
		printf("\n");
		for(j=0;j<m;j++)
			printf("%d  ",c[j]); 
		printf("\n\n");

		 */

		/*l is the index(in C array) to check the index of a[i] */
 	    l = m/2 + a[i];

		/* Increment i 
			(i)  if the position to be placed is the current position
			(ii) if the index is negative
			(iii)if the element is already placed and needn't be checked

			otherwise swap it with the element at required location
			*/

		if( (i == c[m/2 + a[i]]) || (c[m/2 + a[i]] < 0) || (i > c[m/2 + a[i]]) )
			i++;

		else	
		{
			t = a[i];
			a[i] = a[c[l]];
			a[c[l]] = t;
			}

		/* Decrement the current elements index in C array.*/
		c[l]--;

		}
		
	printf("\n\n\nThe array after sorting\n");	
	printf("_________________________\n\n");	
	for(i=0;i<n;i++)
			printf("%d\t",a[i]); 
	
	

	printf("\n");
	
	}	


int main()
{
	int *a;
	int n;
	int k;
	int i;
	srand(time(NULL));
	printf("\nN = ");
	scanf("%d",&n);
	printf("\nK = ");
	scanf("%d",&k);
	a = (int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		a[i] = (rand())%(2*k+1) - k;
	printf("\nThe Array Before Sorting\n");
	printf("_________________________\n\n");
	for(i=0;i<n;i++)
		printf("%d\t",a[i]);
	
	countsort(a,n,k);
	return 0;	
	}
