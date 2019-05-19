#include <iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
struct weight
{
	struct data
	{
		int pos;
		long long key = LLONG_MAX;
		int marked = 0;
		int heap_pos;
	};
	data* link = new data;
	long long w;
};
vector<weight::data*> v;
vector<vector<weight*>> graph;
vector<weight::data*> S;
vector<weight::data*> q;
void siftDown(int i)
{
	while (2 * i + 1 < q.size())
	{
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int j = left;
		if (right < q.size() && q[right]->key < q[left]->key)
		{
			j = right;
		}
		if (q[i]->key <= q[j]->key)
			break;
		/*q[i]->heap_pos = j;
		q[j]->heap_pos = i;*/
		weight::data* tmp = move(q[i]);
		q[i] = move(q[j]);
		q[j] = move(tmp);
		swap(q[i], q[j]);
		i = j;
	}
}

weight::data* extractmin()
{
	weight::data* min = new weight::data;
	if (q.size() == 0)
	{
		min->key = LLONG_MAX;
	}
	else
	{
		q[0]->marked = 1;
		min = q[0];
		q[0] = q[q.size() - 1];
		q[0]->heap_pos = 0;
		q.resize(q.size() - 1);
		siftDown(0);
	}
	return min;
}

void siftUp(int i)
{
	while (q[i]->key < q[(i - 1) / 2]->key)
	{
		/*q[i]->heap_pos = (i - 1) / 2;
		q[(i - 1) / 2]->heap_pos = i;*/
		weight::data* tmp = move(q[i]);
		q[i] = move(q[(i - 1) / 2]);
		q[(i - 1) / 2] = move(tmp);
		/*swap(q[i], q[(i - 1) / 2]);*/
		i = (i - 1) / 2;
	}
}
void insert(weight::data* v)
{
	q.push_back(v);
	v->heap_pos = q.size() - 1;
	siftUp(q.size() - 1);
}

void dijkstra(int s)
{
	v[s]->key = 0;
	v[s]->marked = 1;
	insert(v[s]);
	for (int i = 0; i < v.size(); i++)
	{
		weight::data *u;
		u = extractmin();
		if (u->key == LLONG_MAX)
			break;
		S.push_back(u);
		for (int j = 0; j < graph[u->pos].size(); j++)
		{
			if ((u->key + graph[u->pos][j]->w <= graph[u->pos][j]->link->key)/* && graph[u->pos][j]->link->marked == 0*/ && graph[u->pos][j]->w != LLONG_MAX)
			{
				graph[u->pos][j]->link->key = u->key + graph[u->pos][j]->w;
				if (graph[u->pos][j]->link->marked == 0)
				{
					insert(graph[u->pos][j]->link);
				}
				else
				{
					siftDown(graph[u->pos][j]->link->heap_pos);
				}
			}
		}
	}
}
int main()
{
	ifstream fin("pathmgep.in");
	ofstream fout("pathmgep.out");
	int n, s,f;
	cin >> n >> s >> f;
	v.resize(n);
	graph.resize(n);
	for (int i = 0; i < n; i++)
	{
		weight::data *u = new weight::data;
		v[i] = u;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int w;
			cin >> w;
			if (w > -1)
			{
				v[i]->pos = i;
				v[j]->pos = j;
				weight* u = new weight;
				u->link = v[j];
				u->w = w;
				graph[i].push_back(u);
			}
		}
	dijkstra(s-1);
	if (v[f - 1]->key == LLONG_MAX)
		cout << -1<<endl;
	else
		cout << v[f - 1]->key <<endl;
  system("pause");
	return 0;
}
