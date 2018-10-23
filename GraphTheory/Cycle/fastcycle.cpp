#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
vector<vector<int>> g;
vector<int> cl;
vector<int> p;
int st, endg;
int n, m;
bool dfs_visit(int v);
void dfs()
{
	for (int i = 0; i < n; i++)
		if (dfs_visit(i))
			break;
}
bool dfs_visit(int v)
{
	cl[v]=1;
	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		if (cl[to] == 0)
		{
			p[to] = v;
			if (dfs_visit(to))
				return true;
		}
		else
			if (cl[to] == 1)
			{
				endg = v;
				st = to;
				return true;
			}
	}
	cl[v] = 2;
	return false;
}
int main()
{
	ifstream fin("cycle.in");
	ofstream fout("cycle.out");
	cin>> n>> m;
	p.resize(n);
	cl.resize(n);
	st = -1;
	g.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a - 1].push_back(b - 1);
	}
	dfs();
	string q="";
	if (st == -1)
		cout<<"NO";
	else {
		cout<<"YES"<<endl;
		vector<int> cycle;
		for (int v = endg; v != st; v = p[v])
		{
			cycle.push_back(v);
		}
		cycle.push_back(st);
		for (int i = 0; i<cycle.size(); ++i)
			fout << cycle[cycle.size()-i-1] + 1 << " ";
	}
	return 0;
}