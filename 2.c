#include<stdio.h>
#include<stdlib.h>


/* Merge Sort */
void merge(int a[][20],int low,int mid,int high,int x)
{

	int i,m,k,l,temp[4000][20];

	l=low;
	i=low;
	m=mid+1;

        while((l<=mid)&&(m<=high))
	{

	         if(a[l][x]<=a[m][x])
		 {
			temp[i][0]=a[l][0];
			temp[i][1]=a[l][1];
			temp[i][2]=a[l][2];
			temp[i++][3]=a[l++][3];
			}


                 else
		 {
			temp[i][0]=a[m][0];
			temp[i][1]=a[m][1];
			temp[i][2]=a[m][2];			
			temp[i++][3]=a[m++][3];
                 	}

		 }
      
 

        if(l>mid)
        {
        	for(k=m;k<=high;k++)
		{
			temp[i][0]=a[k][0];
			temp[i][1]=a[k][1];
			temp[i][2]=a[k][2];
        		temp[i++][3]=a[k][3];
         		}

		}
    
        else
        {
        	for(k=l;k<=mid;k++)
                {
			temp[i][0]=a[k][0];
			temp[i][1]=a[k][1];
			temp[i][2]=a[k][2];
			temp[i++][3]=a[k][3];
                        }
		}

   
	for(k=low;k<=high;k++)
        {
		a[k][0]=temp[k][0];
		a[k][1]=temp[k][1];
		a[k][2]=temp[k][2];
		a[k][3]=temp[k][3];
		}

}

void msort(int a[][20],int l,int h,int x)
{

    int mid;
    mid=(l+h)/2;

    if(l<h)
    {
         msort(a,l,mid,x);
         msort(a,mid+1,h,x);
         merge(a,l,mid,h,x);
         }
}

/* Print fucntion*/
void print(int a[][20],int n)
{
     printf("\nPrinting Intervals\n");
     int i;
     for(i=0;i<n;i++)
     printf("[%d %d] (%d)\t",a[i][0],a[i][2],a[i][3]);
     printf("\n");
     }

/*Earliest start time first : Sorts the array based on start time
and searches for the next event which start after the current event ends
For Sorting, T(n) = O(n.log n)
For searching, T(n) = O(n) */    
int func1(int a[][20],int n)
{
	printf("\n\n\nSchedule1: Earliest start time first\n");	
	printf("_____________________________________________\n");
	msort(a,0,n-1,0);
	printf("\n");
	print(a,n);
	int b[4000][20];
	int count = 1;
	int use = a[0][1];
	int s_date = a[0][0];
	int e_date = a[0][2];
	b[0][0] = a[0][0];
	b[0][1] = a[0][1];
	b[0][2] = a[0][2];
	b[0][3] = a[0][3]; 
	int j;

	for(j=1;j<n;j++)
	{
		if(a[j][0]>=e_date)
		{
			b[count][0] = a[j][0];
			b[count][1] = a[j][1];
			b[count][2] = a[j][2];
			b[count][3] = a[j][3];
            count++;
			use += a[j][1];
			s_date = a[j][0];
			e_date = a[j][2];
			
			}
		}

	printf("\nTotal Number of Events : %d\n",count);
    print(b,count);
	printf("\nTotal Utilisation : %d",use);
	return count;
}

/*Earliest start time first : Sorts the array based on earlest end time
and searches for the next event which start after the current event ends
For Sorting, T(n) = O(n.log n)
For searching, T(n) = O(n) */  
int func2(int a[][20],int n)
{
	printf("\n\n\nSchedule2:Earliest end time first\n");
    printf("_____________________________________________\n");	
	msort(a,0,n-1,2);
	printf("\n");
	print(a,n);
	int count = 1;
	int b[4000][20];
	int use = a[0][1];
	int s_date = a[0][0];
	int e_date = a[0][2];
	
	b[0][0] = a[0][0];
	b[0][1] = a[0][1];
	b[0][2] = a[0][2];
	b[0][3] = a[0][3]; 
	int j;

	for(j=1;j<n;j++)
	{
		if(a[j][0]>=e_date)
		{
			b[count][0] = a[j][0];
			b[count][1] = a[j][1];
			b[count][2] = a[j][2];
			b[count][3] = a[j][3];
            count++;
			use += a[j][1];
			s_date = a[j][0];
			e_date = a[j][2];
			
			}
		}

	printf("\nTotal Number of Events : %d\n",count);
    print(b,count);
	printf("\nTotal Utilisation : %d",use);
    return count;
}

/*Checks if the the current event clashed with the events
already stored in the array) */
int check(int b[][20],int count,int s_date,int e_date)
{
	int i,j;	
	for(i=0;i<count;i++)
		if(!( (b[i][0]>=e_date) || (b[i][2] <= s_date) ) ) 
				return 1;
				
	return 0;
	}

/*Shortest first : Sorts the array based on shortest time
and searches for the next element which doesnt conflict with
already stored events.

For Sorting, T(n) = O(n.log n)
For searching, T(n) = O(n^2) */  	
int func3(int a[][20],int n)
{
	printf("\n\n\nSchedule3:Shortest first\n");	
	printf("_____________________________________________\n");
	msort(a,0,n-1,1);
	printf("\n");
	print(a,n);
	int count = 1;
	int use = a[0][1];
	int s_date = a[0][0];
	int e_date = a[0][2];
	int b[4000][20];

	b[0][0] = a[0][0];
	b[0][1] = a[0][1];
	b[0][2] = a[0][2];
	b[0][3] = a[0][3]; 

	int j;
	for(j=1;j<n;j++)
	{
		int s_date = a[j][0];
		int e_date = a[j][2];		
		if(check(b,count,s_date,e_date)==0)
		{
			
			use += a[j][1];
			
			b[count][0] = a[j][0];
			b[count][1] = a[j][1];
			b[count][2] = a[j][2];
			b[count][3] = a[j][3];
			count++; 

			
			
			}
		}

	printf("\nTotal Number of Events : %d\n",count);
    print(b,count);
	printf("\nTotal Utilisation : %d",use);
	return count;
}

/*least conflict first : Sorts the array based on least conflict
and searches for the next element which doesnt conflict with
already stored events.

For Sorting, T(n) = O(n.log n)
For searching, T(n) = O(n^2) */
int func4(int a[][20],int n)
{
	printf("\n\n\nSchedule4:Least conflict first\n");	
	printf("_____________________________________________\n");
    msort(a,0,n-1,3);
	printf("\n");
	print(a,n);
	int count = 1;
	int use = a[0][1];
	int s_date = a[0][0];
	int e_date = a[0][2];
	int b[5000][20];

	b[0][0] = a[0][0];
	b[0][1] = a[0][1];
	b[0][2] = a[0][2];
	b[0][3] = a[0][3]; 

	int j;
	
	for(j=1;j<n;j++)
	{
		int s_date = a[j][0];
		int e_date = a[j][2];		
		if(check(b,count,s_date,e_date)==0)
		{
			
			use += a[j][1];
			
			b[count][0] = a[j][0];
			b[count][1] = a[j][1];
			b[count][2] = a[j][2];
			b[count][3] = a[j][3];
			count++; 

			
			
			}
		}

	printf("\nTotal Number of Events : %d\n",count);
    print(b,count);
	printf("\nTotal Utilisation : %d",use);	

	return count;
}		
int main()
{
	int n;
	int a[4000][20];

	printf("Enter an integer\n");
	scanf("%d",&n);

	srand(time(NULL));
	int i,j;
	/*store start date in a[i][0]
	  store time in a[i][1]
	  store end date in a[i][2]
	  set (no of conflicting events) a[i][3] = 0 */
	for(i=0;i<n;i++)
	{
		a[i][0] = rand()%1000;
		a[i][1] = rand()%100 + 1;
		a[i][2] = a[i][0] + a[i][1];
		a[i][3] = 0;
		}

    /*Stores Conflicting events in a[i][3] */
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(!(a[i][0]>=a[j][2] || a[i][2] <= a[j][0])) 
			{
				a[i][3]++;
				a[j][3]++;
				}
		}
	}
		

	printf("\nn=%d\n\nPrinting the randomly generated intervals :",n);
	printf("\n_____________________________________________\n");
	print(a,n);
	
	int f1,f2,f3,f4;
	f1 = func1(a,n);
	f2 = func2(a,n);
	f3 = func3(a,n);
	f4 = func4(a,n);
	

    printf("\n_____________________________________________\n");
    printf("\nResult:\nAfter running the program for various values of n,it was");
    printf(" found that\nSchedule2: Earliest end time first,\nproduced an optimal solution\n");
    printf("\n_____________________________________________\n");
    
	return 0;
	}

	







