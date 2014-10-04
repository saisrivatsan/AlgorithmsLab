#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _treenode
{
    int key;
	int num;
    struct _treenode *L, *R;
} treenode;

typedef treenode *BST;

BST insert( BST T, int a )
{
   treenode *p, *q;

    p = T;
    q = NULL;
    while (p != NULL) 
    {     
        q = p;
        if (a < p -> key) 
            p = p -> L;
        else
            p = p -> R;
   }
   p = (treenode *)malloc(sizeof(treenode));
   p -> L = p -> R = NULL;
   p -> key = a;
   p -> num = 1 + search(T,a);

    if (q == NULL)
        return p;                    
    if (a < q -> key)
        q -> L = p;
    else
        q -> R = p;
   return T;
}

void print(BST T)
{
 
    
    if(T!=NULL)
    {
        print(T->L);
        printf("%d (%d)\t",T->key,T->num);
        print(T->R);
    }
}

int search(BST T, int a)
{
    if(T== NULL)
        return 0;

    if(a == T->key)
        return ( 1 + search(T->R,a) );
    else if(a > T->key)
        return search(T->R,a);
    else
        return search(T->L,a);
    }

BST delete1( BST T, int a)
{
    treenode *p, *q, *r, *x, *y, *d;
    p = T;
    r = p;
    while(p!=NULL)
    {
        if(a == p->key)
            break;
        else if (a > p->key)
        {
            r = p;        
            p = p->R;
        }
        else
        {
            r = p;        
            p = p->L;
        }
    }

    //P points to the first occurence of a
    if(p == NULL)
        return T;

    x = p;
    q = p->R;
    // x is the parent of q
    while(q!=NULL)
    {
        if(q->key == a)
        {
            if(x->L == q)
            {
                x->L = q->R;
                d = q;
                q = q->R;
                free(d);
                }
            else
            {
                x->R = q->R;
                d = q;
                q = q->R;
                free(d);
                }
                
        }    
    
        else if(q->key > a)
        {
            x = q;
            q = q->L;
            }
        else
        {
            x = q;
            q = q->R;    
        }
    }
    
//Now Delete the first occurence
    if(p->L == NULL)
    {
        if(p == T)
        {    
            T = p->R;  
            return T;
            }
        if(r->L == p)
            r->L = p->R;
        else
            r->R = p->R;
	free(p);
    }
    else if(p->R == NULL)
    {
        if(p == T)
        {
            T = T->L;
            return T;
        }    
        if(r->L == p)
            r->L = p->L;
        else
            r->R = p->L;
	free(p);
    }
    //y is the parent of x and x is the pointer used for traversing
    //down the tree
    else
    {
        y = p;        
        x = p->R;
        while(x->L!=NULL)
        {
            y = x;
            x = x->L;
        }
        
        p->key = x->key;
        if(y->R == x)
        {
            y->R = x->R;
            free(x);
        }
        else
        {
            y->L = x->R;
            free(x);    
        }
    }    

return T;
}
    
//Frees the nodes    
BST clean( BST T )
{
   if (T != NULL)
   {
      clean(T -> L); 
      clean(T -> R);
      free(T);
   }
   return NULL;
}  
int main ()
{
    int i,a,n,m;
    BST T;

    srand((unsigned int)time(NULL));
    printf("_____________________________\n");
    T = NULL;
    printf("\nN =");
    scanf("%d",&n);
    printf("\nM =");
    scanf("%d",&m);
    printf("_____________________________\n");
    printf("Inserting the Elements\n");
    for (i=0; i<n; ++i)
    {
        a = rand()%m+1;
        T = insert(T,a);   
    }
    print(T);
    int j;

    printf("\n_____________________________\n");
    for(i=0;i<10;i++)
    {
        a = rand()%m+1;
        printf("\nSearch(%d) : %d",a,search(T,a));
        } 
    printf("\n_____________________________\n");
    for(i=0;i<5;i++)
    {
        a = rand()%m+1;
        printf("\nDelete(%d) :\n",a);
        T = delete1(T,a);
        print(T);
    }
   clean(T);
   printf("\n"); 
   return 0;
        
}




