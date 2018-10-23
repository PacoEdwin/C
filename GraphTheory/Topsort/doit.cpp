#include<iostream>
#include <list>
#include <stack>
#include<fstream>
using namespace std;
ifstream fin("topsort.in");
ofstream fout("topsort.out");
class Graph
{
	int V;
	list<int> *adj;
	void topologicalSortUtil(int v, int visited[], stack<int> &Stack);
public:
	Graph(int V); 
	void addEdge(int v, int w);
	void topologicalSort();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

void Graph::topologicalSortUtil(int v, int visited[], stack<int> &Stack)
{
	visited[v] = 1;
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if (visited[*i]==0)
			topologicalSortUtil(*i, visited, Stack);
		if (visited[*i]==1)
		{
			cout << -1;
			exit(0);
		}
	}
	visited[v] = 2;
	Stack.push(v);
}
void Graph::topologicalSort()
{
	stack<int> Stack;
	int *visited = new int[V];
	for (int i = 0; i < V; i++)
		visited[i] = 0;
	for (int i = 0; i < V; i++)
		if (visited[i] == 0)
			topologicalSortUtil(i, visited, Stack);
	while (Stack.empty() == false)
	{
		cout << Stack.top()+1 << " ";
		Stack.pop();
	}
}

int main()
{
	int n, m;
	cin >> n>>m;
	Graph g(n);
	int x, y;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y;
		g.addEdge(x-1, y-1);
	}
	g.topologicalSort();
  system("pause");
	return 0;
}