#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<utility>
using namespace std;
fstream fin("transport.in");
ofstream fout("transport.out");
vector <vector<double>> graph;
vector<bool> used;
struct data_
{
	int pos;
	string color="white";
	int aero = 0;
	int road=1;
};
vector<data_*>v;
vector<vector<data_*>> table;
vector<double> min_e, sel_e;
const double INF = 1000000000;
double answer = 0;
int n;
double distance(int x1, int y1, int x2, int y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
void prim()
{
	used.resize(n);
	min_e.assign(n, INF);
	sel_e.assign(n, -1);
	min_e[0] = 0;
	for (int i = 0; i < n; ++i)
	{
		int u = -1;
		for (int j = 0; j < n; ++j)
			if (!used[j] && (u == -1 || min_e[j] < min_e[u]))
				u = j;
		if (min_e[u] == INF)
		{
			cout << "No MST!";
			exit(0);
		}

		used[u] = true;
		if (sel_e[u] != -1)
			table[v[sel_e[u]]->pos].push_back(v[u]);
		for (int to = 0; to < n; ++to)
			if (graph[u][to] < min_e[to])
			{
				min_e[to] = graph[u][to];
				sel_e[to] = u;
			}
	}
}
int main()
{
	double r, a;
	cin >> n;
	vector<pair<int, int>> coord(n);
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		coord[i].first = x;
	}
	for (int i = 0; i < n; i++)
	{
		int y;
		cin >> y;
		coord[i].second = y;
	}
	cin >> r >> a;
	int ind = 0;
	graph.resize(n);
	for (int i = 0; i < n; i++)
		graph[i].resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			i != j ? graph[i][j] = r*distance(coord[i].first, coord[i].second, coord[j].first, coord[j].second) : graph[i][j] = INF;
	coord.clear();
	table.resize(n);
	v.resize(n);
	for (int i = 0; i < n; i++)
	{
		v[i] = new data_;
		v[i]->pos = i;
	}
	prim();
	int check = 0;
	for (int k = 0; k < n; k++)
	{
		bool any = false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < table[i].size(); j++)
			{
				if (v[i]->aero == 0 && table[i][j]->aero == 0 && 2 * a <= graph[v[i]->pos][table[i][j]->pos])//обновл€ю дл€ соседних городов, если там нет аэропортов
				{
					table[i][j]->aero = 1;
					graph[v[i]->pos][table[i][j]->pos] = 0;
					graph[table[i][j]->pos][v[i]->pos] = 0;
					if (check == 0)//если до этого вообще не было аэропортов
					{
						v[i]->aero = 1;
						check = 1;
					}
					any = true;
					continue;
				}
				//пихать выршины, в которых поставили аэропорт, в очередь вытаскивать и обробатывать
				//нужно сделать так, если table[i][j]->aero==1 , но нам выгоднее обновить v[i]->aero 
				if (check == 1 && a <= graph[v[i]->pos][table[i][j]->pos] && table[i][j]->aero==0)//если есть аэропорт,где-то сзади, то нету смысла ставить сразу 2
				{
					table[i][j]->aero = 1;
					if (v[i]->aero == 1)
					{
						graph[v[i]->pos][table[i][j]->pos] = 0;
						graph[table[i][j]->pos][v[i]->pos] = 0;
					}
					any = true;
					continue;
				}
				if (check == 1 && a <= graph[v[i]->pos][table[i][j]->pos]&&v[i]->aero == 0 && table[i][j]->aero == 1)
				{
					v[i]->aero = 1;
					graph[v[i]->pos][table[i][j]->pos] = 0;
					graph[table[i][j]->pos][v[i]->pos] = 0;
					any = true;
					continue;
				}
			/*	if (v[i]->aero&&v[i]->road == 0 && a <= graph[v[i]->pos][table[i][j]->pos])
				{
					if (v[i]->pos == 6 || table[i][j]->pos == 6)
					{
						;
					}
					table[i][j]->aero = 1;
					any = true;
					continue;
				}*/
				/*if (v[i]->road == 0 || table[i][j]->road == 0)
				{
					v[i]->road = 1;
					table[i][j]->road = 1;
					any = true;
				}*/
			}
		/*if (!any)
			break;*/
	}
	for (int i = 0; i < n; i++)
	{
		if (v[i]->aero == 1)
			answer += a;
		for (int j = 0; j < table[i].size(); j++)
		{
			if (v[i]->aero == 0 || table[i][j]->aero == 0)
				answer += graph[v[i]->pos][table[i][j]->pos];
		}
	}
	cout << answer;
	system("pause");
	return 0;
}