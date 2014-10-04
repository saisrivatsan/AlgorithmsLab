#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RGB_COMPONENT_COLOR 255
#define C_MAX 1000

//PIXEL STORING RGB VALUE
typedef struct 
{
    int R;
    int B;
    int G;	
} Pixel ;


//NODE for adjacency list
typedef struct _node 
{      
	long int x;
	int cost;                 	
	struct _node *next;	     
} node;
typedef node *graph; 

//Edge containing Index,Neighbour and Cost
typedef struct 
{
	long int Idx;;
	int d;
	long int nbr;
} Heap;

//Heapify Function
void heapify(Heap H[],long int n,long int i,long int visited[])
{
 
    long int l; 
    long int r;      
    long int min;

    while(i<n)
    {

        l = 2*i + 1;
        r = l+1;
        if(l >= n)
             return;
        if(l == n-1) 
              min = l;
        else if ( H[l].d < H[r].d )
              min = l;
        else  
              min = r;
    
        if(H[min].d >= H[i].d) 
             return;  

        /*swap(H.a[min],H.a[i]). While swapping,Change their Index location
          in Visited array */ 
        Heap temp;
        visited[H[min].Idx] = i;
        visited[H[i].Idx] = min;
        temp = H[min];
        H[min] = H[i];
        H[i] = temp;
        i = min;
    }
}

//Computes cost of edge 
int cost(Pixel P[][300],int w,int h,int x,int y,int px,int py)
{
	if((px<0)||(py<0)||(px>=w)||(py>=h))
		return C_MAX;

	return	(fabs(P[x][y].R-P[px][py].R) +
			 fabs(P[x][y].B-P[px][py].B) +
			 fabs(P[x][y].G-P[px][py].G));
}

//Sorting Fucntion.
int sort(Heap H[],int n)
{
	int i,j;
	Heap temp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(H[i].d<H[j].d)
			{
				temp = H[i];
				H[i] = H[j];
				H[j] = temp;
			}	
		}
	}		
}

//DFS Recursive Function
void dfs(graph G,long int visited[],long int v,int col)
{

	visited[v] = col;
	node *ptr;
	ptr = (node*)malloc(sizeof(node));

	ptr = G[v].next;
	while(ptr!=NULL)
	{
		if(visited[ptr->x]==0)
			dfs(G,visited,ptr->x,col);

		ptr = ptr->next;
	}	

	free(ptr);
}

//Fucntion to call DFS and color th Trees
void segment(graph G,long int n,long int visited[],Pixel P1[],Pixel P[][300],int w)
{
	int i;
	int col = 1;

	for(i=0;i<n;i++)
	{
		if(visited[i] == 0)
		{	
			dfs(G,visited,i,col);
			col++;
		}
	}	
}

//Main Function
int main()
{
	char input[20];
	Pixel P[400][300];
	int adj[400][300][8];
	int w,h,x,y,s,cnt = 0;
	//OPEN FILE
	FILE* fp;
	fp = fopen("original.ppm","r");
	//EXIT if File Not Present
	if(fp==NULL)
	{	
		printf("ERROR!File Not present\n");
		exit(0);
	}
	//CHECK IF PPM FORMAT IS P3
	fscanf(fp,"%s",input);
	if((input[0]!='P')&&(input[1]!='3'))
	{
		printf("File Not in P3 Format.Exit!\n");
		exit(0);
	}
	//SCAN HEIGHT AND WIDTH
	fscanf(fp,"%d %d",&w,&h);
	if((w>400)||(h>300))
	{
		printf("Max Width/Height Exceeded.Exit!\n");
		exit(0);
	}

	int max;
	fscanf(fp,"%d",&max);
	if(max<255)
	{
		printf("RGB_COMPONENT_COLOR EXCEED MAXIMUM\n");
		exit(0);
	}
	//INPUT SEGMENTS
	printf("Enter the number of segments\n");
	scanf("%d",&s);
	s--;

	for(y=0;y<h;y++)
		for(x=0;x<w;x++)	
			fscanf(fp,"%d %d %d",&P[x][y].R,&P[x][y].G,&P[x][y].B);
	
	for(x=0;x<w;x++)
	{
		for(y=0;y<h;y++)
		{
			adj[x][y][0] = cost(P,w,h,x,y,x,y-1);
			adj[x][y][1] = cost(P,w,h,x,y,x+1,y-1);
			adj[x][y][2] = cost(P,w,h,x,y,x+1,y);
			adj[x][y][3] = cost(P,w,h,x,y,x+1,y+1);
			adj[x][y][4] = cost(P,w,h,x,y,x,y+1);
			adj[x][y][5] = cost(P,w,h,x,y,x-1,y+1);
			adj[x][y][6] = cost(P,w,h,x,y,x-1,y);
			adj[x][y][7] = cost(P,w,h,x,y,x-1,y-1);
		}	
	}	

	Heap *H;
	H = (Heap*)malloc(sizeof(Heap)*w*h);
	long int i,k;
	long int *visited = (long int*)malloc(sizeof(long int)*w*h);
	long int n = w*h;
	for(i=0;i<n;i++)
		visited[i] = i;

	for(i=0;i<n;i++)
	{
		H[i].Idx = i;
		H[i].d = C_MAX;
		H[i].nbr = 0;
	}
	//A visited
	visited[0] = -1;
	visited[n-1] = 0;
	Heap temp1 = H[0]; 
	H[0] = H[n-1];
	H[n-1] = temp1;
	n--;
	H[1].d = adj[0][0][2];
	H[w].d = adj[0][0][4];
	H[w+1].d = adj[0][0][3];
	for(i=n/2;i>=0;i--)
		heapify(H,n,i,visited);

	graph G;
	G = (node *)malloc(w*h * sizeof(node));

	int fi,fj;
	for (i=0; i<w*h; ++i)
	{
		G[i].x = i;
		G[i].cost = 0;		
		G[i].next = NULL;
	}

	i = 0;
	long int p,j=0,Idx,x1,y1,Nbr;
	Heap temp;
	node* ptr,*a,*b;
	ptr = (node *)malloc(sizeof(node));

	
	Heap *ce = (Heap*)malloc(s*sizeof(Heap));
	//MST using Prims Algorithm
	while(n>0)
	{	
		Idx = H[0].Idx;
		y = Idx/w;
		x = Idx%w;
		Nbr = H[0].nbr;
		y1 = Nbr/w;
		x1 = Nbr%w;
		a = (node*)malloc(sizeof(node));
		b = (node*)malloc(sizeof(node));

		a->x = H[0].Idx;
		a->cost = cost(P,w,h,x1,y1,x,y);
		a->next = NULL;

		b->x = H[0].nbr;
		b->cost = a->cost;
		b->next = NULL;

		if(cnt<s)
		{
			ce[cnt] = H[0];
			cnt++;
			if(cnt==s)
				sort(ce,cnt);
		}
		else
		{
			for(fi=0;fi<cnt;fi++)
				if(a->cost > ce[fi].d)
					break;

			if(fi < cnt)
			{	
				for(fj = cnt-1;fj>fi;fj--)
					ce[fj] = ce[fj-1];
				ce[fi] = H[0];
			}
		}	
					
		ptr = G[H[0].nbr].next;
		if(ptr==NULL)
			G[H[0].nbr].next = a;
		else 
		{
			while(ptr->next!=NULL)
				ptr = ptr->next;

			ptr->next = a;
		}	

		ptr = G[H[0].Idx].next;
		if(ptr==NULL)
			G[H[0].Idx].next = b;
		else 
		{
			while(ptr->next!=NULL)
				ptr = ptr->next;

			ptr->next = b;
		}

		//Delete it
		visited[H[0].Idx] = -1;
		visited[H[n-1].Idx] = 0;

		temp = H[0];
		H[0] = H[n-1];
		H[n-1] = temp;
		n--;
		heapify(H,n,0,visited);

		if((y-1>=0)&&(visited[Idx-w]!=-1)&&(adj[x][y][0]<H[visited[Idx-w]].d))
		{
			//printf("Update %ld\n",Idx-w );		
			i = visited[Idx - w];
			H[i].d = adj[x][y][0];
			H[i].nbr = Idx; 
			
			while(i>0)
			{
				p = (i-1)/2;
				if(H[p].d>H[i].d)
				{
					visited[H[p].Idx] = i;
       				visited[H[i].Idx] = p;
       				temp = H[p];
       				H[p] = H[i];
       				H[i] = temp;
       				i = p;
				}	

				else
					break;

			}						
		}

		if((x+1<w)&&(y-1>=0)&&(visited[Idx-w+1]!=-1)&&(adj[x][y][1]<=H[visited[Idx-w+1]].d))
		{
			//printf("Update %ld\n",Idx-w +1);			
			i = visited[Idx - w + 1];
			H[i].d = adj[x][y][1]; 
			H[i].nbr = Idx; 

			while(i>0)
			{
				p = (i-1)/2;
				if(H[p].d>H[i].d)
				{
					visited[H[p].Idx] = i;
       				visited[H[i].Idx] = p;
       				temp = H[p];
       				H[p] = H[i];
       				H[i] = temp;
       				i = p;
				}

				else
					break;	
			}						
		}

		if((x+1<w)&&(visited[Idx+1]!=-1)&&(adj[x][y][2]<=H[visited[Idx+1]].d))
		{
			//printf("Update %ld\n",Idx+1 );			
			i = visited[Idx + 1];
			H[i].d = adj[x][y][2]; 
			H[i].nbr = Idx; 

			while(i>0)
			{
				p = (i-1)/2;
				if(H[p].d>H[i].d)
				{
					visited[H[p].Idx] = i;
       				visited[H[i].Idx] = p;
       				temp = H[p];
       				H[p] = H[i];
       				H[i] = temp;
       				i = p;
				}

				else
					break;	
			}						
		}

		//printf("%d %d\n",adj[x][y][3],H[10].d);
		if((x+1<w)&&(y+1<h)&&(visited[Idx+1+w]!=-1)&&(adj[x][y][3]<=H[visited[Idx+1+w]].d))
		{
			//printf("Update %ld\n",Idx+1+w );			
			i = visited[Idx + 1 + w];
			H[i].d = adj[x][y][3]; 
			H[i].nbr = Idx; 

			while(i>0)
			{
				p = (i-1)/2;
				if(H[p].d>H[i].d)
				{
					visited[H[p].Idx] = i;
       				visited[H[i].Idx] = p;
       				temp = H[p];
       				H[p] = H[i];
       				H[i] = temp;
       				i = p;
				}

				else
					break;	
			}						
		}

		if((y+1<h)&&(visited[Idx+w]!=-1)&&(adj[x][y][4]<=H[visited[Idx+w]].d))
		{
			//printf("Update %ld\n",Idx+w );			
			i = visited[Idx + w];
			H[i].d = adj[x][y][4]; 
			H[i].nbr = Idx; 

			while(i>0)
			{
				p = (i-1)/2;
				if(H[p].d>H[i].d)
				{
					visited[H[p].Idx] = i;
       				visited[H[i].Idx] = p;
       				temp = H[p];
       				H[p] = H[i];
       				H[i] = temp;
       				i = p;
				}

				else
					break;	
			}						
		}

		if((x-1>=0)&&(y+1<h)&&(visited[Idx+w-1]!=-1)&&(adj[x][y][5]<=H[visited[Idx+w-1]].d))
		{
				
			//printf("Update %ld\n",Idx-1+w );		
			i = visited[Idx + w -1];
			H[i].d = adj[x][y][5]; 
			H[i].nbr = Idx; 

			while(i>0)
			{
				p = (i-1)/2;
				if(H[p].d>H[i].d)
				{
					visited[H[p].Idx] = i;
       				visited[H[i].Idx] = p;
       				temp = H[p];
       				H[p] = H[i];
       				H[i] = temp;
       				i = p;
				}

				else
					break;	
			}						
		}

		if((x-1>=0)&&(visited[Idx-1]!=-1)&&(adj[x][y][6]<=H[visited[Idx-1]].d))
		{
			//printf("Update %ld\n",Idx-1 );			
			i = visited[Idx - 1];
			H[i].d = adj[x][y][6]; 
			H[i].nbr = Idx; 

			while(i>0)
			{
				p = (i-1)/2;
				if(H[p].d>H[i].d)
				{
					visited[H[p].Idx] = i;
       				visited[H[i].Idx] = p;
       				temp = H[p];
       				H[p] = H[i];
       				H[i] = temp;
       				i = p;
				}

				else
					break;	
			}						
		}

		if((x-1>=0)&&(y-1>=0)&&(visited[Idx-w-1]!=-1)&&(adj[x][y][7]<=H[visited[Idx-w-1]].d))
		{
			//printf("Update %ld\n",Idx-w-1 );			
			i = visited[Idx -w - 1];
			H[i].d = adj[x][y][7]; 
			H[i].nbr = Idx; 

			while(i>0)
			{
				p = (i-1)/2;
				if(H[p].d>H[i].d)
				{
					visited[H[p].Idx] = i;
       				visited[H[i].Idx] = p;
       				temp = H[p];
       				H[p] = H[i];
       				H[i] = temp;
       				i = p;
				}

				else
					break;	
			}						
		}

		    
		//getchar();
	}

	node* p1;
	p1 = (node *)malloc(sizeof(node));

	for(i=0;i<s;i++)
	{
		//printf("%ld %ld %d\n",ce[i].Idx,ce[i].nbr,ce[i].d);
		Idx = ce[i].Idx;
		Nbr = ce[i].nbr;

		ptr = G[Idx].next;
		p1 = NULL;
		while(ptr->x!=Nbr)
		{
			p1 = ptr;
			ptr = ptr->next; 
		}	
		if(p1 == NULL)
			G[Idx].next = ptr->next;
		else
			p1->next = ptr->next;

		ptr = G[Nbr].next;
		p1 = NULL;
		while(ptr->x!=Idx)
		{
			p1 = ptr;
			ptr = ptr->next; 
		}		
		if(p1 == NULL)
			G[Nbr].next = ptr->next;
		else
			p1->next = ptr->next;	
	}	

	for(i=0;i<w*h;i++)
		visited[i] = 0;

	Pixel P1[27];
	segment(G,w*h,visited,P1,P,w);

	for(i=0;i<27;i++)
	{
		j = 27-i;
		P1[i].R = (j%3)*255/2;
		j = j/3;
		P1[i].G = (j%3)*255/2;
		j= j/3;
		P1[i].B = (j%3)*255/2;
	}	

	for(i=0;i<w*h;i++)
		P[i%w][i/w] = P1[visited[i]];
	

	FILE* fp1;
	fp1= fopen("out.ppm","w");

	fprintf(fp1,"%s\n",input);
	fprintf(fp1,"%d %d\n",w,h);
	fprintf(fp1,"%d\n",max);

	for(y=0;y<h;y++)
		for(x=0;x<w;x++)	
			fprintf(fp1,"%d %d %d\n",P[x][y].R,P[x][y].G,P[x][y].B);


	free(H);
	free(ce);
	free(visited);
	free(G);
	return 0;
}
