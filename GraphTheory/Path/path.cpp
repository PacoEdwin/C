#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#define INF 9000000000000000000
using namespace std;
struct weight
{
	struct data
	{
		int pos;
		long long key = INF;
		string color = "white";
	};
	data* link = new data;
	long long w;
};
vector<vector<weight*>> graph;
vector<weight::data*> v;
vector<weight::data*> q;
void dfs(weight::data* u)
{
	u->color = "grey";
	for (int i = 0; i < graph[u->pos].size(); i++)
	{
		if (graph[u->pos][i]->link->color == "white")
			dfs(graph[u->pos][i]->link);
	}
	u->color = "black";
}
void bellmanford(int s)
{
	v[s]->key = 0;
	for (int k = 0; k < v.size(); k++)
	{
		for (int i = 0; i < v.size(); i++)
		{
			for (int j = 0; j < graph[v[i]->pos].size(); j++)
			{
				if (v[i]->key == INF)
					break;
				if (v[i]->key + graph[v[i]->pos][j]->w < graph[v[i]->pos][j]->link->key)
					graph[v[i]->pos][j]->link->key = v[i]->key + graph[v[i]->pos][j]->w;
			}
		}
	}
	
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < graph[v[i]->pos].size(); j++)
			if ((v[i]->key + graph[v[i]->pos][j]->w < graph[v[i]->pos][j]->link->key)&&v[i]->key!=INF)
				q.push_back(v[i]);
	}
}
int main()
{
	ifstream fin("path.in");
	ofstream fout("path.out");
	int n, m, s;
	cin >> n >> m >> s;
	graph.resize(n);
	v.resize(n);
	for (int i = 0; i < n; i++)
	{
		weight::data* u = new weight::data;
		v[i] = u;
		v[i]->pos = i;
	}
	for (int i = 0; i < m; i++)
	{
		int a,b;
		long long w;
		cin >> a >> b >> w;
		v[a - 1]->pos = a - 1;
		v[b - 1]->pos = b - 1;
		weight* u = new weight;
		u->link = v[b - 1];
		u->w = w;
		graph[a - 1].push_back(u);
	}
	bellmanford(s-1);
	if (q.size() > 0)
	{
		for (int i = 0; i < q.size(); i++)
			if (q[i]->color == "white")
				dfs(q[i]);
	}
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->key == INF)
		{
			cout << "*" << endl;
			continue;
		}
		if (v[i]->color == "black")
		{
			cout << "-" << endl;
			continue;
		}
		cout << v[i]->key<<endl;
	}
	system("pause");
	return 0;
}