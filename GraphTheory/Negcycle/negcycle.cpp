#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
ifstream fin("negcycle.in");
ofstream fout("negcycle.out");
struct edge 
{
	long long a, b, cost;
};

long long n, m, v;
vector<edge*> e;
const long long INF = LLONG_MAX;

void solve()
{
	vector<long long> d(n, INF);
	vector<long long> p(n, -1);
	d[0] = 0;
	for (long long i = 0; i<n-1; ++i)
		for (long long j = 0; j<e.size(); ++j)
			if (d[e[j]->a] < INF)
				d[e[j]->b] = min(d[e[j]->b], d[e[j]->a] + e[j]->cost);

	// вывод d, например, на экран

	long long x;
	for (long long i = 0; i<n; ++i)
	{
		x = -1;
		for (long long j = 0; j<e.size(); ++j)
			if (d[e[j]->b] > d[e[j]->a] + e[j]->cost)
			{
				d[e[j]->b] = max(-INF, d[e[j]->a] + e[j]->cost);
				p[e[j]->b] = e[j]->a;
				x = e[j]->b;
			}
	}

	if (x == -1)
		cout << "NO";
	else {
		long long y = x;
		for (long long i = 0; i<n; ++i)
			y = p[y];

		vector<long long> path;
		for (long long cur = y;; cur = p[cur]) {
			path.push_back(cur);
			if (cur == y && path.size() > 1)  break;
		}
		reverse(path.begin(), path.end());

		cout << "YES"<<endl<<path.size()-1<<endl;
		for (long long i = 1; i<path.size(); ++i)
			cout << path[i]+1 << ' ';
	}
}

int main()
{
	cin >> n;
	for (long long i = 0; i < n; i++)
	{
		for (long long j = 0; j < n; j++)
		{
			long long w;
			cin >> w;
			if (w != LLONG_MAX)
			{
				edge* u = new edge;
				u->a = i;
				u->b = j;
				u->cost = w;
				e.push_back(u);
			}
		}
	}
	solve();
	system("pause");
	return 0;
}