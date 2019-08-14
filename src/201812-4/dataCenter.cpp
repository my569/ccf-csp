//算法导论 23-3 提到的瓶颈生成树，其实就是这个题的答案
//使用Kruskal
#include <stdio.h>
#include <algorithm>
#include <unordered_set>

using namespace std;

#define N 50010

int** G;
int n,m,root;
//并查集的数据结构，见算法导论21.3 
int* p;
int* ranks;

void make_set(int x){
	p[x] = x;
	ranks[x] = 0;
}
void link_set(int x,int y)
{
	if(ranks[x]>ranks[y])	p[y]=p[x];
	else 			p[x]=p[y];
	if(ranks[x]==ranks[y])
		ranks[y]++;
}
int find_set(int x)
{
	if(x!=p[x])
		p[x]=find_set(p[x]);
	return p[x];
}
void union_set(int x, int y)
{
	link_set(find_set(x), find_set(y));
}


struct CMP{
	bool operator()(int a[3],int b[3]){//a[3] b[3]
		return a[2]<b[2];
	}
}cmp;

bool cmp2(int* a,int* b){//a[3] b[3]
	return a[2]<b[2];
}

int main(int argc,char* argv[])
{
	scanf("%d",&n);
	scanf("%d",&m);
	scanf("%d",&root);
	
	G = (int**)malloc(sizeof(int*) * m);
	for(int i =0; i<m; i++) G[i] = (int*)malloc(sizeof(int) * 3);	

	for(int i=0; i<m; i++)
	{
		scanf("%d%d%d", &G[i][0], &G[i][1], &G[i][2]);
		G[i][0]--,G[i][1]--;
	}

	sort(&G[0],&G[m], cmp2);
	
	p = (int*)malloc(sizeof(int)*n);
	ranks = (int*)malloc(sizeof(int)*n);
	for(int i=0; i<n; i++) make_set(i);
	
	int cnt = 0;
	int k = 0;
	int maxEdge = 0;
	while(cnt<n-1){
		int &u=G[k][0], &v=G[k][1], &w=G[k][2];
		if(find_set(u) != find_set(v)){
			union_set(u,v);
			if(w > maxEdge) maxEdge = w;
			cnt++;
		}
		k++;
	}
	printf("%d\n", maxEdge);	
	
	for(int i=0; i<m; i++)
		free(G[i]);
	free(G);	
	free(p);
	free(ranks);

	return 0;
}
