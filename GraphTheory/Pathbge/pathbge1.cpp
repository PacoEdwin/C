#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
using namespace std;
ifstream fin("pathbge1.in");
ofstream fout("pathbge1.out");
struct features
{
	string color;
	int d;
	int pos;
	features* ancestor;
};
void bfs(vector<vector<features*>> &table, vector<features*> &v, features *s)
{
	s->color="gray";
	s->d = 0;
	/*fout << 0<<" ";*/
	queue<features*> q;
	q.push(s);
	while (!q.empty())
	{
		features* u = q.front();
		q.pop();
		for (int i = 0; i < table[u->pos].size(); i++)
		{
			if (table[u->pos][i]->color == "white")
			{
				table[u->pos][i]->color = "gray";
				table[u->pos][i]->d = u->d + 1;
				/*fout << table[u->pos][i]->d<<" ";*/
				table[u->pos][i]->ancestor = u;
				q.push(table[u->pos][i]);
			}
		}
		u->color = "black";
	}
}
int main()
{
	int n, m;
	int start;
	cin >> n >> m;
	vector<vector<features*>> table;
	vector<features*> v(n);
	for (int i = 0; i < n; i++)
	{
		v[i] = new features;
		v[i]->ancestor = NULL;
		v[i]->color = "white";
		v[i]->d = INT_MAX;
	}
	table.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		if (i == 0)
			start = a;
		table[a - 1].push_back(v[b-1]);
		v[b - 1]->pos = b - 1;
		table[b - 1].push_back(v[a - 1]);
		v[a - 1]->pos = a - 1;
	}
	bfs(table, v, v[0]);
	for (int i = 0; i < v.size(); i++)
		cout << v[i]->d<<" ";
	system("pause");
	return 0;
}