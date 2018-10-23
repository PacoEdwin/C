#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
using namespace std;
struct features
{
	string color;
	int d;
	int f;
	int pos;
};
vector<int>answer;
int time = 0;
ifstream fin("hamiltonian.in");
ofstream fout("hamiltonian.out");
vector<vector<features*>> table;
vector<features*> v;
int out = 0;
void dfs_visit(features *u);
void dfs()
{
	for (int i = 0; i < v.size(); i++)
	{
		if (out == 1)
			return;
		if (v[i]->color == "white")
			dfs_visit(v[i]);
	}
}
void dfs_visit(features *u)
{
	time++;
	u->d = time;
	u->color = "gray";
	for (int i = 0; i < table[u->pos].size(); i++)
	{
		if (table[u->pos][i]->color == "white")
			dfs_visit(table[u->pos][i]);
	}
	u -> color = "black";
	time++;
	u -> f = time;
	answer.push_back(u->pos);
	if (answer.size() > 1)
	{
		int check = 0;
		for (int i = 0; i < table[answer[answer.size()-1]].size(); i++)
			if (table[answer[answer.size() - 1]][i]->pos ==answer[answer.size()-2])
				check = 1;
		if (check == 0)
		{
			out = 1;
			return;
		}
	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	v.resize(n);
	if (m > 0)
	{
		for (int i = 0; i < n; i++)
		{
			v[i] = new features;
			v[i]->color = "white";
		}
		table.resize(n);
		for (int i = 0; i < m; i++)
		{
			int a, b;
			cin >> a >> b;
			table[a - 1].push_back(v[b - 1]);
			v[a - 1]->pos = a - 1;
			v[b - 1]->pos = b - 1;
		}
		dfs();
	}
	if (out == 0)
		cout << "YES";
	else
		cout << "NO";
	system("pause");
	return 0;
}