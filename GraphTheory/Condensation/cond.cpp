#include<iostream>
#include<vector>
#include<fstream>
#include<stack>
using namespace std;
struct data_
{
	string color;
	int  d;
	int  f;
	long long  component;
	int  pos;
};
int time = 0;
ifstream fin("condense2.in");
ofstream fout("condense2.out");
vector<vector<int>> visited;
vector<vector<data_*>> table;
vector<vector<data_*>> reversed;
vector<data_*> v;
stack<data_*>q;
void reverseddfs(stack<data_*> &q, vector<vector<data_*>> &graph);
void reversed_dfs_visit(data_* u, vector<vector<data_*>> &graph);
void dfs_visit(data_ *u);
int  num = 0;
long long edge = 0;
void dfs()
{
	for (int i = 0; i < v.size(); i++)
		if (v[i]->color == "white")
			dfs_visit(v[i]);
}
void reverseddfs(stack<data_*> &q, vector<vector<data_*>> &graph)
{
	while (q.size() != 0)
	{
		if (q.top()->color == "white")
		{
			num++;
		/*	for (int i = 0; i < graph[q.top()->pos].size(); i++)
				if (graph[q.top()->pos][i]->color == "black")
					edge++;*/
			q.top()->component = num;
			visited.resize(num);
			reversed_dfs_visit(q.top(), graph);
		}
		for (int i = 0; i < graph[q.top()->pos].size(); i++)
			if (graph[q.top()->pos][i]->component != q.top()->component)
			{
				if (graph[q.top()->pos][i]->component > visited[num-1].size())
					visited[num - 1].resize(graph[q.top()->pos][i]->component);
				visited[num - 1][graph[q.top()->pos][i]->component - 1] = 1;
			}
		q.pop();
	}
}
void reversed_dfs_visit(data_* u, vector<vector<data_*>> &graph)
{
	u->color = "gray";
	for (int  i = 0; i < graph[u->pos].size(); i++)
	{
		if (graph[u->pos][i]->color == "white")
		{
			graph[u->pos][i]->component = num;
			reversed_dfs_visit(graph[u->pos][i], graph);
		}
	}
	u->color = "black";
}
void dfs_visit(data_ *u)
{
	time++;
	u->d = time;
	u->color = "gray";
	for (int i = 0; i < table[u->pos].size(); i++)
	{
		if (table[u->pos][i]->color == "white")
			dfs_visit(table[u->pos][i]);
	}
	u->color = "black";
	time++;
	u->f = time;
	q.push(u);
}
int main()
{
	int n, m;
	cin >> n >> m;
	v.resize(n);
	for (int i = 0; i < n; i++)
	{
		v[i] = new data_;
		v[i]->color = "white";
		v[i]->pos = i;
	}
	table.resize(n);
	reversed.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		table[a - 1].push_back(v[b - 1]);
		reversed[b - 1].push_back(v[a - 1]);
		v[a - 1]->pos = a - 1;
		v[b - 1]->pos = b - 1;
	}
	dfs();
	for (int i = 0; i < n; i++)
		v[i]->color = "white";
	reverseddfs(q, reversed);
	cout << num << " ";
	for (int i = 0; i < visited.size(); i++)
		for (int j = 0; j < visited[i].size(); j++)
			edge += visited[i][j];
	cout << edge;
	system("pause");
	return 0;
}