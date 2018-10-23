#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
int n, m;
vector<vector<int>> g;
int timer;
vector<bool>used;
vector<int> lol;
vector<int>mem;
vector<vector<int>> answer;
vector<int> kek;
void dfs(int v, int p = -1) 
{
	used[v] = true;
	lol[v] = mem[v] = timer++;
	int children = 0;
	for (int i = 0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			mem[v] = min(mem[v], lol[to]);
		else {
			dfs(to, v);
			mem[v] = min(mem[v], mem[to]);
			if (mem[to] >= lol[v] && p != -1)
				kek.push_back(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
		kek.push_back(v);
}
int main()
{
	/*ifstream fin("points.in");
	ofstream cout("points.out");*/
	cin >> n >> m;
	used.resize(n);
	lol.resize(n);
	mem.resize(n);
	g.resize(n);
	answer.resize(m);
	for (int i = 0; i < m; i++)
		answer[i].resize(2);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		answer[i][0] = a - 1;
		answer[i][1] = b - 1;
		g[a - 1].push_back(b - 1);
		g[b - 1].push_back(a - 1);
	}
	bool lol = true;
	for (int i = 0; i < n; i++)
	{
		if (used[i] == 0)
		{
			dfs(i);
		}
	}
	sort(kek.begin(), kek.end());
	int last = -1;
	vector<int> cinal;
	for (int i = 0; i < kek.size(); i++)
	{
		if (kek[i] != last)
			cinal.push_back(kek[i] + 1);
		last = kek[i];
	}
	cout << cinal.size()<<endl;
	for (int i = 0; i < cinal.size(); i++)
		cout << cinal[i]<<" ";
	system("pause");
	return 0;
}