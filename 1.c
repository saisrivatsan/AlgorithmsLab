/* Sai Srivatsa R
   12EE10059
   Algorithms Lab-1
   */

#include<stdio.h>
#include<stdlib.h>



int func(int k,int a[][200])
{

    if(k==0)
    return 0;
    
    int i,x,y;    
    for(i=1;i<=k;i++)
    {
        for(x=0;x<(1<<(i-1));x++)
        {        
            for(y=0;y<(1<<(i-1));y++) 
            {
                a[x+(1<<(i-1))][y] = a[x][y];
                a[x][y+(1<<(i-1))] = a[x][y];
                a[x+(1<<(i-1))][y+(1<<(i-1))] = -a[x][y];
            }
        }
    }


    return 0;
}

void print(int a[][200],int k)
{
    printf("\n\nPrinting matrix\n");    
    int i,j;    
    for(i=0;i<(1<<k);i++)
    {
        for(j=0;j<(1<<k);j++)
        {
        printf("%3d ",a[i][j]);
        }
    printf("\n");
    }
}

int func2(double v[],int n)
{
    int i;    
    for(i=0;i<n;i++)    
    {
    v[i] = (double)rand()/(double)RAND_MAX;
    
    
    }
    return 0;
}

void print2(double v[],int n)
{
    printf("\n\nPrinting Vector\n");    
    int i;    
    for(i=0;i<n;i++)
    printf("%f   \n",v[i]);
    }

void Mult(int a[][200],double v[],double prod[20],int n)
{
    int i,j;
    for(i=0;i<n;i++)
        prod[i]=0;

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            prod[i] += (double)(v[j]*a[i][j]);

    printf("\nPrinting Product through method 1\n");    
    for(i=0;i<n;i++)
        printf("%f\n",prod[i]);
}

/* Split array into four sub arrays | A A  |
                                    | A -A|
Divide vector into V1 and V2
Compute AV1 and AV2.=> 2 multiplication of matrices half the size of the
earlier matrix.
=> T(n) = T(n/2) + O(n);
*/                                    
                                    
double* M(double* v, int k)
{
          if(k == 0)
              return v;
          
          double *x1 = M(v,k-1);
          double *x2 = M(v+((1<<(k-1))),k-1); 
          
          double * Ans = (double *)malloc(sizeof(double)*(1<<k));
          int m;
          for(m=0;m<(1<<(k-1));m++)
          {
                  
                  Ans[m] = x1[m] + x2[m];
                  Ans[m+(1<<(k-1))] = x1[m] - x2[m];
                   
                  
                  }
               
          return Ans;
          }            

        


int main()
{
    int a[200][200];
    
    a[0][0]=1;
    int k,i;
    double v[20],prod[20],Ans[20];
    printf("Input K\n");
    scanf("%d",&k);

    func(k,a);
    func2(v,(1<<k));
    print(a,k);
    print2(v,(1<<k));
    Mult(a,v,prod,(1<<k));
    
    
   
   
        
   printf("\n");
    double *ptr = M(v,k);
    

   printf("\nPrinting Product through method 2\n");
   for(i=0;i<(1<<(k));i++)
     printf("%f\n",*(ptr+i)); 
    
    
    return 0;
}
