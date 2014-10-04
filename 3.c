#include<stdio.h>
/* Print fucntion*/

void print(int a[][20],int n)
{
     printf("\nPrinting Intervals\n");
     int i;
     for(i=0;i<n;i++)
     printf("[%d %d] \t",a[i][0],a[i][2]);
     printf("\n");
     }

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
			temp[i++][2]=a[l++][2];
			}


                 else
		 {
			temp[i][0]=a[m][0];
			temp[i][1]=a[m][1];		
			temp[i++][2]=a[m++][2];
                 	}

		 }
      
 

        if(l>mid)
        {
        	for(k=m;k<=high;k++)
		{
			temp[i][0]=a[k][0];
			temp[i][1]=a[k][1];
        		temp[i++][2]=a[k][2];
         		}

		}
    
        else
        {
        	for(k=l;k<=mid;k++)
                {
			temp[i][0]=a[k][0];
			temp[i][1]=a[k][1];
			temp[i++][2]=a[k][2];
                        }
		}

   
	for(k=low;k<=high;k++)
        {
		a[k][0]=temp[k][0];
		a[k][1]=temp[k][1];
		a[k][2]=temp[k][2];
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


/*Earliest end time first : Sorts the array based on earliest end time
and searches for the next event which start after the current event ends
For Sorting, T(n) = O(n.log n)
For searching, T(n) = O(n) */  
int func1(int a[][20],int n)
{
	printf("\n\n\nSchedule1:Earliest end time first\n");
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
	int j;

	for(j=1;j<n;j++)
	{
		if(a[j][0]>=e_date)
		{
			b[count][0] = a[j][0];
			b[count][1] = a[j][1];
			b[count][2] = a[j][2];
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


/*Earliest start time first : Sorts the array based on start time
and searches for the next event which start after the current event ends
For Sorting, T(n) = O(n.log n)
For searching, T(n) = O(n) */    
int func2(int a[][20],int n)
{
	printf("\n\n\nSchedule2: Earliest start time first\n");	
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
	int j;

	for(j=1;j<n;j++)
	{
		if(a[j][0]>=e_date)
		{
			b[count][0] = a[j][0];
			b[count][1] = a[j][1];
			b[count][2] = a[j][2];
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

int bsearch(int a[][20],int l,int h,int key)
{
	int mid = (l+h)/2;

	if(l == h)
		return l;

	if(key > a[mid][0])
		return bsearch(a,mid+1,h,key);
	else
		return bsearch(a,l,mid,key);
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
	  store end date in a[i][2] */
	for(i=0;i<n;i++)
	{
		a[i][0] = rand()%1000;
		a[i][1] = rand()%100 + 1;
		a[i][2] = a[i][0] + a[i][1];
		}

	printf("\nn=%d\n\nPrinting the randomly generated intervals :",n);
	printf("\n_____________________________________________\n");
	print(a,n);
	
	int f1,f2;
	f1 = func1(a,n);
	f2 = func2(a,n);
	int ans[4000];
	int util[4000];
	for(i=0;i<n;i++)
		util[i] = -1;
	for(i=0;i<n;i++)
		ans[i] = -1;

	util[n] = 0;
	int u1,u2,x;
	for(i=n-1;i>=0;i--)
        {
		if(i==n-1)
		{
			util[i] = a[i][1];
			ans[i] = n;
			}			
		else
		{
			x = bsearch(a,i+1,n,a[i][2]);

			u2 = util[i+1]; 	
		        u1 = util[x] + a[i][1];

			if(u1 > u2 )		
			{
				ans[i] = x;
				
				util[i] = u1;		
				} 
			else
			{
				ans[i] = -1;
				util[i] = u2;
				}
		}
	}
		
		
	printf("\n\nDynamic Programming,Max Utilisation = %d ",util[0]); 	
	//for(i=0;i<n;i++)
	  //  printf("...%d...",ans[i]);

	int s =0;
	int max = 0;
	/*for(i=0;i<n;i++)
	{
		if(ans[i]>max)
		{	
			printf(" [%d %d] ",a[max][0],a[max][2]);
			s +=  a[max][0] -a[max][2]	;	
			max = ans[i];
			
			}
	}
	printf("...%d",s); */
	return 0;
	}

	


