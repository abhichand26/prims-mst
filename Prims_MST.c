#include<stdio.h>
#include<stdlib.h>
#define N 10
#define inf 32000

/*
** Program to find minimum spanning tree using Prims Algorithm with Adjacency List 
** Made by - Abhishek Chand
*/

typedef struct NODE
{
	int v;
	int w;
	struct NODE* next;
}node;

typedef struct HeapNode
{
	int v;
	int key;
}Hnode;

void decreaseKey(Hnode *H, int i, int newKey, int s, int *pos) {
	int p = pos[i], v; //printf("\ndecKey: %d", p);
	Hnode x = H[p];
	x.key = newKey;
	//printf("\nKey values: %d %d\n", x.key, H[p/2].key);
	while(p > 1 && x.key < H[p/2].key) {
		H[p] = H[p/2];
		v = H[p].v;
		pos[v] = p;
		p = p/2;
	}
	H[p] = x;
	pos[i] = p;
	//printf("\ndecKey: %d", p);
}

void minHeapify(Hnode *H, int i, int s, int *pos) {
	Hnode x = H[i];
	int l, r, min, v;
	while((l = 2*i) <= s) {
		r = l+1;
		if(r <= s && H[r].key < H[l].key)
			min = r;
		else
			min = l;
		if(H[min].key < x.key) {
			H[i] = H[min];
			v = H[i].v;
			pos[v] = i;
			i = min;
			
		}
		else
			break;
	}
	H[i] = x;
	v = H[i].v;
	pos[v] = i;
}

int extractMin(Hnode *H, int *s, int *pos) {
	int u = H[1].v;
	H[1] = H[*s];
	pos[H[1].v] = 1;
	*s = *s-1;
	minHeapify(H, 1, *s, pos);
	return u;
}

void primsMST(node *L[], int n) {
	int *key,*pre,*vis, pos[n+1], i, v, w, cost = 0;
	key = (int *)malloc((n+1)*sizeof(int));
	pre = (int *)malloc((n+1)*sizeof(int));
	vis = (int *)malloc((n+1)*sizeof(int));
	
	int Hsize = n;
	Hnode *H = (Hnode *)malloc((Hsize+1)*sizeof(Hnode));
	for(i = 1; i <= Hsize; i++)
	{
		pre[i] = -1;
		vis[i] = 0;
		key[i] = H[i].key = inf;
		H[i].v = i;
		pos[i] = i;
	}
	key[1] = H[1].key = 0;
	
	
	while(Hsize) {
		int u = extractMin(H, &Hsize, pos);
		vis[u] = 1;
		//printf("\nExt vertex: %d\n", u);
		if(u!=1)
		{
			printf("\n(%d,%d):%d",pre[u],u,key[u]);
		}
		cost += key[u];
		node *q = L[u];
		while(q) {
			v = q->v;
			w = q->w; 
			if(vis[v] == 0 && w < key[v]){
				key[v] = w;
				pre[v] = u;
				decreaseKey(H, v, w, Hsize, pos);
			}
			//printf("Adj vertex: %d ", v);
			q = q->next;
		//	printf("Address: %d\n", q);
		}
	}
	printf("\n------------------\nCost of MST = %d\n", cost);
	
}

int main()
{
	int i,j,k,w,n,e;
	
	printf("\nNo. of vertices:");
	scanf("%d",&n);
	printf("\nNo. of edges:");
	scanf("%d",&e);
	node *List[N]={NULL};
	
	for(k=0;k<e;k++)
	{
		node *t = (node *)malloc(sizeof(node));
		printf("\nEnter an edge(i j w):");
		scanf("%d %d %d", &i, &j, &w);
		t->v=j;
		t->w=w;
		t->next = List[i];
		List[i] = t;
		
		t = (node *)malloc(sizeof(node));
		t->v=i;
		t->w=w;
		t->next=List[j];
		List[j]=t;
	}
	
	printf("\nInput Graph:\n");
	for(i=1;i<n+1;i++)
	{
		printf("\n\n%d",i);
		node *p=List[i];
		while(p!=NULL)
		{
			printf("->%d:%d",p->v,p->w);
			p=p->next;
		}
	}
	
	primsMST(List, n);
	return 0;
}
