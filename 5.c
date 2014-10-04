#include <stdio.h>
#include <stdlib.h>

#define swap(a,b) int t = a; a=b; b=t;

#define parent(i) ((i-1)/2)
#define   left(i) (2*i + 1)
#define  right(i) (2*i + 2)

#define m_parent(i) ((n+i+1)/2)
#define   m_left(i) (2*i - n)
#define  m_right(i) (2*i - n - 1)

//Heap
typedef struct
{
    int size_max;
    int size_min;                 
    int* a;                   
} Heap;

//Insertion in the Max-Heap
void max_insert(Heap H,int x,int n)
{    
    H.size_max++;
    int i = H.size_max;
    H.a[H.size_max] = x;
    
    while( (i>0) && (H.a[parent(i)] < H.a[i]) )
    {
    	swap(H.a[i],H.a[parent(i)]);
    	i = parent(i);
    }

}

//Insertion in the Min-Heap
void min_insert(Heap H,int x,int n)
{    
    H.size_min--;
    int i = H.size_min;
    H.a[H.size_min] = x;
    
    while( (i < n-1) && (H.a[m_parent(i)] > H.a[i]) )
    {
        swap(H.a[i],H.a[m_parent(i)]);
        i = m_parent(i);
    }

}

//Heapify into Max-Heap
void max_heapify(Heap H,int n,int i)
{
 

    int l; 
    int r;      
    int max;

    while(i<n)
    {

        l = left(i);
        r = right(i);

        if(l >= n)
             break;

        if( l == n-1) 
              max = l;
        else if ( H.a[l] > H.a[r] )
              max = l;
        else  
              max = r;
    
        if(H.a[max] <= H.a[i]) 
               break;

        swap(H.a[max],H.a[i]);
        i = max;
    
    }
}

//Heapify the Min- Heap
void min_heapify(Heap H,int n,int s,int i)
{
 

    int l; 
    int r;      
    int min;

    while(i>=s)
    {

        l = m_left(i);
        r = m_right(i);

        if(l < s)
             break;

        if( l == s) 
              min = l;
        else if ( H.a[l] < H.a[r] )
              min = l;
        else  
              min = r;
    
        if(H.a[min] >= H.a[i]) 
               break;

        swap(H.a[min],H.a[i]);
        i = min;
    
    }
}

//Deletion in Max -Heap
int delete_max(Heap H,int n)
{
    int del = H.a[0];
    H.a[0] = H.a[H.size_max];
    max_heapify(H,H.size_max,0);
    return del;

    }

//Deletion in Min - Heap
int delete_min(Heap H,int n)
{
    int del = H.a[n-1];
    H.a[n-1] = H.a[H.size_min];
    min_heapify(H,n,H.size_min+1,n-1);
    return del;
    }

//Median Finder
int median(Heap H,int n)
{
    //Returns root of min heap if N2 = N1
    //Returns root of max heap if N2 = N1 + 1
    if(H.size_min!=n-H.size_max-1)
        return H.a[n-1];
    else
        return H.a[0];
}

//Deletion in Median Heap
int del_med(Heap H,int n)
{
   //Returns root of max heap if N2 = N1
   //Returns root of min heap if N2 = N1 + 1
   if(H.size_max == n - H.size_min-1)
        return delete_max(H,n);
    else
        return delete_min(H,n);
}

//Insertion in Median Heap
int insert_med(Heap H,int n,int x)
{
    
    int med = median(H,n);
    int j;
    
    if(x<=med)
    {
        if(H.size_max == n - H.size_min-1)
        {
            //Deletes root from max heap and inserts in the min heap
            //Inserts new element in the max heap

            int del = delete_max(H,n);
            H.size_max--;

            max_insert(H,x,n);
            H.size_max++;

            min_insert(H,del,n);
            H.size_min--;
            return 2;
        }
        else
        {
            //Inserts new element in the max heap
            max_insert(H,x,n);
            H.size_max++;
           
            return 1;
        }    
    }    

    else
    {
        if(H.size_max == n - H.size_min-1)
        {
            //Inserts new element in the min heap
            min_insert(H,x,n);
            H.size_min--;
          
            return 2;
        }
        else
        {
            //Deletes root from min heap and inserts in the max heap
            //Inserts new element in the min heap
            int del = delete_min(H,n);
            H.size_min++;

            max_insert(H,del,n);
            H.size_max++;

            min_insert(H,x,n);
            H.size_min--;
  
            return 1;
        }    
    }    


}

//Median Heap Sort
void med_heapsort(Heap H,int n)
{
    int i,c,j;

    if(n%2==0)
        c = 1;
    else
        c = 0;

    //DELETES MEDIAN FROM MAX IF N2 = N1
    //DELETES MEDIAN FROM MIN HEAP IF N2 = N1 + 1
    // As all elements are deleted one by one, we use a integer c anc check if its odd or even
    // and perform the reqiured operation
    for(i=0;i<n;i++)
    {
        if(c%2)
        {
             j =H.a[H.size_max] = del_med(H,n);
             H.size_max--;
        }
        
        else
        {

            j = H.a[H.size_min] = del_med(H,n);
            H.size_min++;
        }    
    c++;

    }    
}

int main()
{
    int n,i,j,x,num;;
    printf("\nN = ");
    scanf("%d",&n);
    
    Heap H;
    H.a = (int *)malloc(n * sizeof(int));
    H.size_max = -1;
    H.size_min = n;
    printf("\nMedian Heap Initialised\n");
    printf("__________________________________________________________\n");
    printf("\nInserting Element in the median Heap\n\n\n");
    srand(time(NULL));
    //Insert first element, in max heap as N1 = 0 and N2 = 1
    H.a[n-1] = rand()%10000;
    H.size_min--;
    printf("Insert(%d). Done .",H.a[n-1]);
    printf("Current Median : %d\n\n",median(H,n));
    //Insert remaining randomly generated elements
    for(i=1;i<n;i++)
    {
        x = rand()%10000;
        num = insert_med(H,n,x);
        if(num==2)
            H.size_min--;
        else if(num==1)
            H.size_max++;
        printf("Insert(%d). Done .",x);
        printf("Current Median : %d\n",median(H,n));
        printf("\n");
    }    
    //Perform Median sort
    med_heapsort(H,n);
    //Display the elements
    printf("\n__________________________________________________________\n");
    printf("\nHeap Sort Done\n");
    printf("Printing the Elements\n\n");
    for(i=0;i<n;i++)
        printf("%d\t",H.a[i]);
    printf("\n");
    return 0;
 }

