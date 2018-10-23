#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
struct data_
{
	int from,to,weight;
};
int main()
{
	ifstream fin("shortpath.in");
	ofstream fout("shortpath.out");
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	vector<data_*> edges;
	vector<int> v(n,INT_MAX);
	v[s - 1] = 0;
	for (int i = 0; i < m; i++)
	{
		data_* u = new data_;
		cin >> u->from>>u->to>>u->weight;
		u->from--;
		u->to--;
		edges.push_back(u);
	}
	for (int i = 0; i < n; i++)
	{
		bool check = false;
		for (int j = 0; j < m; j++)
			if (v[edges[j]->from] < INT_MAX && v[edges[j]->from] + edges[j]->weight < v[edges[j]->to])
				v[edges[j]->to] = v[edges[j]->from] + edges[j]->weight,check=true;
		if (!check)
			break;
	}
	int answer=v[t-1];
	if (answer!=INT_MAX)
		cout << answer;
	else
		cout << "Unreachable";
	system("pause");
	return 0;
}