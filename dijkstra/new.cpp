#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<vector>
#include<math.h>

using namespace std;

struct node
{
	int vertex;
	node* next;
	float ewt;
	int vwt;
};

struct heap
{
	float D;
	int mark;
	int prev;
};

node* readgraph(int n, int m, vector< vector<int> > E);
node* newnode(int v);
void Dijkstra(node* G, int n, int s, int t, int flag);
void makeheap(heap* H, int n, int* locator);
void heapify(heap* H, int n, int i, int* locator);

int main()
{
	int n, m, s, t;
	vector< vector<int> > E;
	cout<<"Enter number of vertices\n";
	cin>>n;
	cout<<"\nEnter number of edges\n";
	cin>>m;
	cout<<"\nEnter s and t\n";
	cin>>s>>t;
	cout<<"\nEnter edges\n";
	for(int i = 0; i < m; i++)
	{
		vector<int> edge;
		int a,b;
		cin>>a>>b;
		edge.push_back(a);
		edge.push_back(b);
		E.push_back(edge);
	}
	node* G = readgraph(n, m, E);
	
	for(int i = 0; i < n; i++)
	{
		node* ptr = G[i].next;
		while(ptr != NULL)
		{
			cout<<"Enter ewt("<<i<<","<<ptr->vertex<<")\n";
			cin>>ptr->ewt;
			ptr = ptr->next;
		}
	}

	for(int i = 0; i < n; i++)
	{
		cout<<"Enter vwt("<<i<<")\n";
		cin>>G[i].vwt;
	}

	Dijkstra(G, n, s, t, 0);

	// Reliable Path
	cout<<"\nChanging the edge weights\n";
	for(int i = 0; i < n; i++)
	{
		node* ptr = G[i].next;
		while(ptr != NULL)
		{
			cout<<"Edge weight ("<<i<<","<<ptr->vertex<<" changes from "<<ptr->ewt<<") to "<<log(ptr->ewt)*-1<<endl;
			ptr->ewt = log(ptr->ewt)*-1;
			ptr = ptr->next;
		}
	}
	cout<<"\nRunning Dijkstra on the log-converted graph";
	Dijkstra(G, n, s, t, 0);

	//Vertex weights part
	node* H = new node[2*n];
	for(int i = 0; i < 2*n; i++)
		H[i].next = NULL;
	for(int i = 0; i < 2*n; i += 2)
	{
		H[i].next = newnode(i + 1);
		H[i].next->ewt = G[i/2].vwt;
	}
	for(int i = 0; i < n; i++)
	{
		node* ptr = G[i].next;
		while(ptr != NULL)
		{
			node* temp = H[2*i + 1].next;
			H[2*i + 1].next = newnode(2*(ptr->vertex));
			H[2*i + 1].next->next = temp;
			ptr = ptr->next;
		}
	}
	cout<<"\nConverting vertex weights to edge weights\n";
	for(int i = 0; i < 2*n; i++)
	{
		node* ptr = H[i].next;
		cout<<i<<" -> ";
		while(ptr != NULL)
		{
			cout<<ptr->vertex<<' ';
			ptr = ptr->next;
		}
		cout<<endl;
	}
	cout<<"Running Dijkstra on vertex-weight graph\n";
	Dijkstra(H, 2*n, 2*s, 2*t + 1, 1);

}

node* newnode(int v)
{
	node* n = new node;
	n->vertex = v;
	n->next = NULL;
	return n;
}

node* readgraph(int n, int m, vector< vector<int> > E)
{
	node* list = new node[n];
	for(int i = 0; i < m; i++)
	{
		node* ptr = &list[E[i][0]];
		node* temp = ptr->next;
		ptr->next = newnode(E[i][1]);
		ptr->next->next = temp;
	}
	for(int i = 0; i < n; i++)
	{
		node* ptr = list[i].next;
		cout<<i<<" -> ";
		while(ptr != NULL)
		{
			cout<<ptr->vertex<<' ';
			ptr = ptr->next;
		}
		cout<<endl;
	}
	return list;
}

void heapify(heap* H, int n, int i, int* locator)
{
	while(1)
	{
		int l = 2*i + 1;
		int r = 2*i + 2;
		int m = -1;
		if(l >= n) break;
		if(r >= n) m = l;
		else m = (H[l].D < H[r].D) ? l : r;
		if(H[i].D <= H[m].D) break;
		heap t = H[i];
		H[i] = H[m];
		H[m] = t;
		i = m;
		int temp = locator[i];
		locator[i] = locator[m];
		locator[m] = temp;
	}
}

void makeheap(heap* H, int n, int* locator)
{
	for(int i = n; i >= 0; i--)
		heapify(H, n, i, locator);
}

heap deletemin(heap* H, int n, int* locator)
{
	heap ret = H[0];
	H[0] = H[n-1];
	locator[0] = locator[n-1];
	n--;
	if(n > 0) heapify(H, 0, n, locator);
}

void Dijkstra(node* G, int n, int s, int t, int flag)
{

	heap* H = new heap[n];
	int* locator = new int[n];
	H[0].D = 0;
	H[0].mark = 1;
	H[0].prev = -1;

	for(int i = 1; i < n; i++)
	{
		H[i].D = 9999999.9;
		H[i].prev = -1;
		H[i].mark = 0;
		locator[i] = i;
	}
	makeheap(H, n, locator);
	int w = 0;
	while(w != t)
	{
		node* ptr = G[w].next;
		while(ptr != NULL)
		{
			int ver = ptr->vertex;
			if(H[ver].mark)
			{
				ptr = ptr->next;
				continue;
			}
			if(H[w].D + ptr->ewt < H[ver].D)
			{
				H[ver].D = H[w].D + ptr->ewt;
				H[ver].prev = w;
			}
			ptr = ptr->next;
		}
		float min = 9999999.9;
		for(int i = 0; i < n; i++)
		{
			if(H[i].mark) continue;
			if(H[i].D < min) { min = H[i].D; w = i;}
		}
		H[w].mark = 1;

	}
	cout<<"\nShortest distance = "<<H[t].D<<endl;
	cout<<"Path : ";
	vector< int > path;
	w = t;
	while(w != s)
	{
		path.push_back(w);
		w = H[w].prev;
	}
	path.push_back(s);

	if(flag == 0)
	{
		for(int i = path.size() - 1; i >= 0; i--)
			cout<<path[i]<<' ';
		cout<<endl;
	}
	else
	{
		for(int i = path.size() - 1; i >= 0; i -= 2)
			cout<<path[i]/2<<' ';
		cout<<endl;	
	}
}