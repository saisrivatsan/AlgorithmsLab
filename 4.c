#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//For storing Vertices
typedef struct _node 
{      
	int x;                 
	int col;	
	struct _node *next;
	     
} node;

typedef node *graph; 


//For Storing Edges
typedef struct _node2 
{      
	int Idx;	
	int e1;                 
	int e2;	
	int col;
	struct _node2 *next;
	     
} node2;

typedef node2 *graph2; 


//Stores the values and creates the adjacency List
int ed(graph g,int n,float p,int deg[])
{
	float p1;
	int i,j,e;
	e = 0;
	node *a;
	srand(time(NULL));
	for (i=0; i<n; ++i)
	{
		g[i].x = i;
		g[i].col = 0;		
		g[i].next = NULL;
		deg[i] = 0;
		}

	node *ptr;
	ptr = (node *)malloc(sizeof(node));
	
	for (i=0; i<n; ++i)
	{
	     	for (j=i+1; j<n; ++j)
		{
		     	p1 = (double)rand() / (double)RAND_MAX;
			if (p1>p)
		        {
	              	        /* Insert j as a neighbor of i */
		                a = (node *)malloc(sizeof(node));
		               	a -> x = j;
	                        a -> next = NULL;
				ptr = g[i].next;

				if(ptr == NULL)
					g[i].next = a;
				else
				{
					while(ptr->next!= NULL)
						ptr = ptr->next;
					ptr->next = a;
					}

				/* Updates the degree */	
				deg[i]++;	
      	                        
				/* Insert i as a neighbor of j */
              	                a = (node *)malloc(sizeof(node));
	                        a -> x = i;
	                        a -> next = NULL;
	                        
				ptr = g[j].next;
				if(ptr == NULL)
					g[j].next = a;
				else
				{
					while(ptr->next!= NULL)
						ptr = ptr->next;
					ptr->next = a;
					}
				/* Updates the degree */				
				deg[j]++;

				/*Updates the edges */
				e++;

	                }
                }
       }
	printf("\nGraph Before Vertex Coloring:\n");
	for(i=0;i<n;i++)
	{
		printf("\n%d [%d] :",g[i].x,g[i].col);
		node *ptr = g[i].next;		
		while(ptr!= NULL)
		{
			printf(" %d [%d]",ptr->x,ptr->col);
			ptr = ptr->next;
			}
	}

	

return e;

}

/* Constructs Maximal Independant Sets 
Finds the vertex with smallest degree.Stores it in S
Updates the degree of the vertex and all its neighbouring vertices to max
(Updating degree to max is analogous to deletion of the element as it is not checked again) 
Repeats until all the elements' degree has been updates*/
int max(graph g,int n,int s[],int deg[])
{

	int t[2000],c;
	int cnt = 0,i,j=4,pos;
	for(i=0;i<n;i++)
		t[i] = deg[i];
	int small;
	do
	{		
		

		small = n+1;
		// Finds the node with smalles degree		
		for(i=0;i<n;i++)
		{
			if(t[i]<small)
			{
			 small = t[i];
			 pos = i;
			
				}
			}
		if(small==n+1)
			break;

		s[cnt++] = pos;

		t[pos] = n+1;

		node *ptr = g[pos].next;
		node *ptr2;
		
		while(ptr!= NULL)
		{
			
			c = ptr->x;			
			t[c] = n+1;
			ptr2 = g[c].next;
			while(ptr2!= NULL)
			{
				c = ptr2->x;
				if(t[c]!=n+1)
				{
					t[c]--;
					deg[c]--;
					}
				ptr2 = ptr2->next;
				}				
			ptr = ptr->next;
			}
			
		}while(small!=n+1);
return cnt;
}	

/*Colours the vertices of the graph*/
int vcol(graph g,int n,int s[],int deg[])
{
	int clr = 0,pos,i,cnt = 1;
	while(cnt!=0)
	{	
		cnt = max(g,n,s,deg);
		clr++; 
		for(i=0;i<cnt;i++)
		{
			pos = s[i];
			g[pos].col = clr;
			deg[pos] = n+1;
			}
	
	}

	for(i=0;i<n;i++)
	{
		node *ptr = g[i].next;
		while(ptr!= NULL)
		{
			ptr->col = g[ptr->x].col;
			ptr = ptr->next;
			}
		}	
		
	printf("\n\nNo of colours used: %d\n",clr-1);	
	printf("Graph After Vertex Coloring:\n");
	for(i=0;i<n;i++)
	{
		printf("\n%d [%d] :",g[i].x,g[i].col);
		node *ptr = g[i].next;		
		while(ptr!= NULL)
		{
			printf(" %d [%d]",ptr->x,ptr->col);
			ptr = ptr->next;
			}
	}

return 0;
}

/* Constructs the graph with edges as elements*/
int line(graph g,graph2 g2,int n,int e,int deg2[])
{
	node * ptr;
	ptr = (node *)malloc(sizeof(node));
	int i,j=0;	
	for(i=0;i<n;i++)
	{
		ptr = g[i].next;
		while( (ptr!=NULL) && (ptr->x < g[i].x) )
			ptr = ptr->next;

		while(ptr!=NULL)
		{
			g2[j].e1 = g[i].x;
			g2[j].e2 = ptr->x;
			j++;
			ptr = ptr->next;
			}

		}

	
	for (i=0; i<e; ++i)
	{

		g2[i].col = 0;		
		g2[i].next = NULL;
		g2[i].Idx = 0;
		deg2[i] = 0;
		}


	node2 * ptr1;
	ptr1 = (node2 *)malloc(sizeof(node2));

	node2 *a;	
	
	for(i=0;i<e;i++)
	{
		for(j=i+1;j<e;j++)
		{       /*Checks for neighbouring edges*/
			if( (g2[j].e1==g2[i].e1)||(g2[j].e2 == g2[i].e1)
				||(g2[j].e1 == g2[i].e2)||(g2[j].e2==g2[i].e2) )
			{
			
				a = (node2 *)malloc(sizeof(node2));
		               	a -> e1 = g2[j].e1;
	                        a -> e2 = g2[j].e2;
				a -> Idx =  j;
				a -> next = NULL; 
				ptr1 = g2[i].next;

				if(ptr1 == NULL)
					g2[i].next = a;
				else
				{
					while(ptr1->next!= NULL)
						ptr1 = ptr1->next;
					ptr1->next = a;
					}

					
				deg2[i]++;	
      	                        
				/* Insert i as a neighbor of j */
              	                a = (node2 *)malloc(sizeof(node2));
		               	a -> e1 = g2[i].e1;
	                        a -> e2 = g2[i].e2;
				a -> next = NULL; 
				a -> Idx = i;
				ptr1 = g2[j].next;

				if(ptr1 == NULL)
					g2[j].next = a;
				else
				{
					while(ptr1->next!= NULL)
						ptr1 = ptr1->next;
					ptr1->next = a;
					}
				deg2[j]++;

				}}}
						
	
	node2 * ptr2;
	ptr2 = (node2 *)malloc(sizeof(node2));
	printf("\n________________________________");
	printf("\n\nGraph Before Edge Coloring:\n");
	for(i=0;i<e;i++)
	{
		printf("\n(%d %d) [%d]:",g2[i].e1,g2[i].e2,g2[i].col);
		node2 *ptr2 = g2[i].next;		
		while(ptr2!= NULL)
		{
			printf(" (%d %d) [%d]",ptr2->e1,ptr2->e2,ptr2->col);
			ptr2 = ptr2->next;
			}
	}

return j;
}
			

/* Constructs Maximal Independant Sets 
Finds the edge with smallest degree.Stores it in S
Updates the degree of the edge and all its neighbouring edges to max
(Updating degree to max is analogous to deletion of the element as it is not checked again) 
Repeats until all the elements' degree has been updates*/
int max2(graph2 g2,int e,int s2[],int deg2[])
{

	int t[2000],c;
	int cnt = 0,i,pos;
	for(i=0;i<e;i++)
		t[i] = deg2[i];
	int small;
	do
	{		
		

		small =e+1;		
		for(i=0;i<e;i++)
		{
			if(t[i]<small)
			{
			 small = t[i];
			 pos = i;
			
				}
			}
		if(small==e+1)
			break;

		s2[cnt++] = pos;

		t[pos] = e+1;

		node2 *ptr = g2[pos].next;
		node2 *ptr2;
		while(ptr!= NULL)
		{
			
			c = ptr->Idx;			
			t[c] = e+1;
			ptr2 = g2[c].next;	
			while(ptr2!= NULL)
			{
				c = ptr2->Idx;
				if(t[c]!=e+1)
				{
					t[c]--;
					deg2[c]--;
					}
				ptr2 = ptr2->next;
				}
			ptr = ptr->next;
			}
			
		}while(small!=e+1);
return cnt;
}	

/*Colours the Edges using max2() and prints the coloured graph*/
int lcol(graph2 g2,int e,int s2[],int deg2[])
{
	int clr = 0,pos,i,cnt = 1;
	while(cnt!=0)
	{	
		cnt = max2(g2,e,s2,deg2);
		clr++; 
		for(i=0;i<cnt;i++)
		{
			pos = s2[i];
			g2[pos].col = clr;
			deg2[pos] = e+1;
			}
	
	}

	for(i=0;i<e;i++)
	{
		node2 *ptr = g2[i].next;
		while(ptr!= NULL)
		{
			ptr->col = g2[ptr->Idx].col;
			ptr = ptr->next;
			}
		}	
		
	printf("\n\nNo of colours used: %d\n",clr-1);	
	printf("Graph After Edge Coloring:\n");
	for(i=0;i<e;i++)
	{
		printf("\n(%d %d) [%d]:",g2[i].e1,g2[i].e2,g2[i].col);
		node2 *ptr = g2[i].next;		
		while(ptr!= NULL)
		{
			printf(" (%d %d) [%d]",ptr->e1,ptr->e2,ptr->col);
			ptr = ptr->next;
			}
	}

return 0;
}



int main()
{
	int n,i;
	float p;
	printf("Enter an integer:\n");
	scanf("%d",&n);
	printf("\nEnter the probablity:\n");
	scanf("%f",&p);
	int deg[2000],deg2[2000];
	int s[2000],s2[2000];
	graph g;
	g = (node *)malloc(n * sizeof(node));
	int e = ed(g,n,p,deg);	
	vcol(g,n,s,deg);
	graph2 g2;
	g2 = (node2 *)malloc(e * sizeof(node2));
	line(g,g2,n,e,deg2);
	lcol(g2,e,s2,deg2);
	printf("\n");		
	return 0;
	
	}



